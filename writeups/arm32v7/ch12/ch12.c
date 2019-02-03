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

important* work;

void func(){
    printf("[*] Working\n");
}

void secret(){
	system("cat flag");
}

void create_worker(){
    work = (important*) malloc(sizeof(important));
    work->func_ptr = func;
    printf("Worker Created in %p\n", work);
}

void start_worker(){
    work->func_ptr();
}

void free_worker(){
    free(work);
}

void send(){
    message* msg = (message*) malloc(sizeof(message));
    printf("Message Created in %p\n", msg);

	printf("Creating message\n");
	printf("Enter message name:");
	fgets(msg->name, BUF_SIZE, stdin);
	printf("Enter message content:");
	gets(msg->content);
	printf("name: \"%s\"\ncontent:\"%s\"\n", msg->name, msg->content);
}

int menu(){
	char buffer[BUF_SIZE] = {0};

	printf("[*] menu\n");
	printf("menu - show this menu\n");
	printf("send - send new message\n");
	printf("create_worker - create worker\n");
	printf("start_worker - run worker\n");
	printf("free_worker - free current worker\n");
	printf("exit - close program\n");

	fgets(buffer, BUF_SIZE, stdin);

	if (strcmp(buffer, "menu\n") == 0){
		return 1;
	}
	else if (strcmp(buffer, "create_worker\n") == 0){
		create_worker();
		return 1;
	}
	else if (strcmp(buffer, "start_worker\n") == 0){
		start_worker();
		return 1;
	}
	else if (strcmp(buffer, "free_worker\n") == 0){
		free_worker();
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
	printf("Welcome to ch12!\n");
	while(1){
		if (!(menu())){
			break;
		}
		printf("\n");
	}
	printf("Exiting...\n");
}
