#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/stat.h>

#define LOG_PRIO(_LEVEL)	(LOG_USER | _LEVEL)
#define BUFF_MAX_LEN		4000000
int mySocketFD, peerSocketFD;
FILE *file;
struct sockaddr peeradd;

void signal_handler(int signal){
	if(signal == SIGINT){
		printf("Caught signal SIGINT!\n");
		printf("Terminating...\n");
		close(mySocketFD);
		close(peerSocketFD);			
		remove("/var/tmp/aesdsocketdata");
		shutdown(mySocketFD, SHUT_RDWR);
		exit(0);
	}
	else if(signal == SIGTERM){
		printf("Caught signal SIGTERM!\n");
		printf("Terminating...\n");
		close(mySocketFD);
		close(peerSocketFD);			
		remove("/var/tmp/aesdsocketdata");
		shutdown(mySocketFD, SHUT_RDWR);
		exit(0);
	}
	else if(signal == SIGKILL){
		printf("Caught signal SIGKILL!\n");
		printf("Terminating...\n");
		close(mySocketFD);
		close(peerSocketFD);			
		remove("/var/tmp/aesdsocketdata");
		shutdown(mySocketFD, SHUT_RDWR);
		exit(0);
	}
	else{ /* Do Nothing */}
}

int initiate_connection(void){
	int yes = 1;
	struct addrinfo ad_info;
	struct addrinfo *servinfo;
	mySocketFD = socket(PF_INET, SOCK_STREAM, 0);
	memset(&ad_info, 0, sizeof(ad_info));
	ad_info.ai_flags = AI_PASSIVE;
	ad_info.ai_family = AF_INET;
	ad_info.ai_socktype = SOCK_STREAM;
	ad_info.ai_protocol = 0;
	if(getaddrinfo(NULL, "9000", &ad_info, &servinfo) != 0){
		perror("getaddrinfo");
		return -1;
	}
	else{ /* Do Nothing */}

	if(setsockopt(mySocketFD, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1){
		perror("setsockopt");
		return -1;
	}
	else{ /* Do Nothing */}

	if(bind(mySocketFD, servinfo->ai_addr, sizeof(struct addrinfo)) != 0){
		perror("bind");
		freeaddrinfo(servinfo);
		return -1;
	}
	else{ /* Do Nothing */}

	freeaddrinfo(servinfo);

	if(listen(mySocketFD, 1) != 0){
		perror("listen");
		return -1;
	}
	else{ /* Do Nothing */}

	return 0;
}


void receive_data(void){
	char my_buffer[BUFF_MAX_LEN];
	socklen_t len = sizeof(struct sockaddr);
	peerSocketFD = accept(mySocketFD, &peeradd, &len);
	if(peerSocketFD == -1){
		perror("accept");
	}
	printf("Accepted connection from %u:%u:%u:%u\n", peeradd.sa_data[2], peeradd.sa_data[3], peeradd.sa_data[4], peeradd.sa_data[5]);
	syslog(LOG_PRIO(LOG_DEBUG), "Accepted connection from %u:%u:%u:%u\n", peeradd.sa_data[2], peeradd.sa_data[3], peeradd.sa_data[4], peeradd.sa_data[5]);
	int index = 0;
	int buffer_len = 0;

	while(1){
		recv(peerSocketFD, &(my_buffer[index]), 1, MSG_WAITALL);
		buffer_len++;
		if(my_buffer[index] == '\n'){
			break;
		}
		index++;
	}
	file = fopen("/var/tmp/aesdsocketdata", "a");
	fwrite(my_buffer, sizeof(char), buffer_len, file);
	fclose(file);
}

void send_data(void){
	char str_buffer[BUFF_MAX_LEN];
	file = fopen("/var/tmp/aesdsocketdata", "r");
	while(fgets(str_buffer, BUFF_MAX_LEN, file)){
		send(peerSocketFD, str_buffer, strlen(str_buffer), MSG_WAITALL);
	}
	fclose(file);
	printf("Closed connection from %u:%u:%u:%u\n", peeradd.sa_data[2], peeradd.sa_data[3], peeradd.sa_data[4], peeradd.sa_data[5]);
	syslog(LOG_PRIO(LOG_DEBUG), "Closed connection from %u:%u:%u:%u\n", peeradd.sa_data[2], peeradd.sa_data[3], peeradd.sa_data[4], peeradd.sa_data[5]);
}

int main(int argc, char *argv[]){
	int daemon_flag = (argc > 1) ? ((strcmp(argv[1], "-d") == 0) ? 1 : 0) : 0;
	if(argc > 1){
		if(strcmp(argv[1], "-d") == 0){
			pid_t pid = fork();
			if(pid == -1){
				perror("fork");
				return -1;
			}
			else if(pid != 0){
				exit(0);
			}
			else{ /* Do Nothing */}
			if(setsid() == -1){
				perror("setsid");
				return -1;
			}
			else{ /* Do Nothing */}
			freopen("/dev/null", "r", stdin);
			freopen("/dev/null", "w", stdout);
			freopen("/dev/null", "w", stderr);
		}
	}
	/* Set signal handler */
	signal(SIGINT, signal_handler);

	if(initiate_connection() != 0){
		return -1;
	}

	/* Truncate file */
	file = fopen("/var/tmp/aesdsocketdata", "w");
	fclose(file);

	while(1){
		receive_data();
		send_data();
	}
	
	
	printf("%d\n", daemon_flag);
	return 0;
}
