//__author__ = '@tomereyz'
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 50

char command_string[BUF_SIZE] = "whoami\x00";

void secret02(){
	strcpy(command_string, "cat flag\x00");
	printf("secret02 called!\n");
}

void secret01(){
	system(command_string);
    printf("secret01 called!\n");
}

void send(){
	char name[BUF_SIZE] = {0};
	char content[BUF_SIZE] = {0};

	printf("Creating message\n");
	printf("Enter message name:");
	fgets(name, BUF_SIZE, stdin);
	printf("Enter message content:");
	gets(content);

	printf("name: \"%s\"\ncontent:\"%s\"\n", name, content);
}

int menu(){
	char buffer[BUF_SIZE] = {0};

	printf("[*] menu\n");
	printf("menu - show this menu\n");
	printf("send - send new message\n");
	printf("exit - close program\n");
	
	fgets(buffer, BUF_SIZE, stdin);

	if (strcmp(buffer, "menu\n") == 0){
		return 1;
	}
	else if (strcmp(buffer, "send\n") == 0){
		send();
		return 1;
	}
	else if (strcmp(buffer, "exit\n") == 0){
		return 0;
	}
	else{
		printf("Unknown command: %s", buffer);
		return 1;
	}

}

int main(int argc, char **argv){
    setbuf(stdout, NULL);
	uid_t uid = geteuid();
	setresuid(uid,uid,uid);
    printf("Welcome to ch03!\n");
	while(1){
		if (!(menu())){
			break;
		}
		printf("\n");
	}
	printf("Exiting...\n");
}
