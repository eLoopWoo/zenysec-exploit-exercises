//__author__ = '@tomereyz'
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 50

void secret(){
	system("cat flag");
}

void send(){
	struct locals{
		char name[BUF_SIZE];
		char content[BUF_SIZE];
		char value;
	};
	struct locals l = {.value = 0, .content = {0}, .name = {0}};

	printf("Creating message\n");
	printf("Enter message name:");
	fgets(l.name, BUF_SIZE, stdin);
	printf("Enter message content:");
	gets(l.content);

	printf("name: \"%s\"\ncontent:\"%s\"\n", l.name, l.content);
	if(l.value == 0x7){
		secret();
	}
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
	printf("Welcome to ch00!\n");
	while(1){
		if (!(menu())){
			break;
		}
		printf("\n");
	}
	printf("Exiting...\n");
}
