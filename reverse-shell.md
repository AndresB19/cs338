# Reverse Shell Assignment

## Part 1: Installing a PHP Web Shell

* a. You'd have to find where the web shell is located in the server using a tool like gobuster. After finding where that file is located, you must type it into the webrowser with its location, the the phrase "command?command" so: http://danger.jeffondich.com/uploadedimages/brachoa-webs.php?command=whoami (where brachoa-webs is my web shell file). When I execute the command is the username of the account running on the webserver: www-data.

* b. It orders the output stream of the command so that we see it line by line instead of all in one.

## Part 2: Looking around

* a. Danger's website is located in /var/www as seen in: /var/www/danger.jeffondich.com/uploadedimages

* b. root, jeff, postgres, bullwinkle. I looked for bin/bash users in etc/passwd using cat.

* c. Yes, it contains info about users, their names, user ids, default shell, and other things.

* d. No, permission is denied. This file is only readable by the root user since it contains the hashed passwords of the users

* e. youwontfindthiswithgobuster, my\_ip.php, upload.php, and intrigue.jeffondich.com 

## Part 4: Launching a Reverse Shell

* a. 192.168.122.57, I found out py doing "ip addr" on the kali machine

* b. 192.168.122.1, I found out by using "nmcli device status" to find my virtual bridge device, and then looking at it address with "ip addr"

* e. Yes, and I can execute commands. It says www-data@kali:/var/www/html$

* f. % is the url encoding for special characters (I know this well since it was keeping from running scripts on the previous assignment with the dr moriarty site). In this case it represents mostly spaces

* g. As an attacker i ran nc -l -p 5000 and waited for a connection on the port 5000, my appache server gets the request from my host browser and executes the command, then which then shends its stdin and stdout to a websocket for my listening nc connection. 
