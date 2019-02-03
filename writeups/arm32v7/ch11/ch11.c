//__author__ = '@tomereyz'
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 50

typedef struct{
    char name[BUF_SIZE];
    char content[BUF_SIZE];
} message;

typedef struct{
    char junk01[BUF_SIZE];
    char junk02[BUF_SIZE];
    void (*func_ptr)();
} important;

void secret(){
	system("cat flag");
}

void send(){

    message* msg = (message*) malloc(sizeof(message));
    important* object_01 = (important*) malloc(sizeof(important));

	printf("Creating message\n");
	printf("Enter message name:");
	fgets(msg->name, BUF_SIZE, stdin);
	printf("Enter message content:");
	gets(msg->content);

    if (object_01->func_ptr){
        object_01->func_ptr();
    }

	printf("name: \"%s\"\ncontent:\"%s\"\n", msg->name, msg->content);
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
	printf("Welcome to ch11!\n");
	while(1){
		if (!(menu())){
			break;
		}
		printf("\n");
	}
	printf("Exiting...\n");
}
