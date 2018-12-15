//__author__ = '@tomereyz'
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 50

int admin = 0;
char command_string[BUF_SIZE] = "whoami\x00";

void write_anywhere(){
	__asm__("str r0, [r1]");
	printf("write_anywhere!\n");
}

void gadget(){
	__asm__("pop {r0,r1,pc}");
}

void authenticate(){
    uid_t uid = geteuid();
    strcpy(command_string, "cat flag\x00");
    if (admin == 1){
        setresuid(uid,uid,uid);
        system(command_string);
    }
    printf("You are not admin!\n");
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
	else if (strcmp(buffer, "admin\n") == 0){
		authenticate();
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
    printf("Welcome to ch09!\n");
	while(1){
		if (!(menu())){
			break;
		}
		printf("\n");
	}
	printf("Exiting...\n");
}
