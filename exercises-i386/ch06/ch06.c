//__author__ = '@tomereyz'
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/mman.h>

#define BUF_SIZE 50
#define PAGE_SIZE 4096

void runner(){
	char content[PAGE_SIZE];
	char *code;
	
	printf("Enter byte to run:");
	fgets(content, PAGE_SIZE, stdin);

	code = mmap(NULL, PAGE_SIZE, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	memcpy(code, content, PAGE_SIZE);

	mprotect(code, PAGE_SIZE, PROT_READ|PROT_EXEC);

	void (*func)() = (void (*)())code;
	func();

	munmap(code, PAGE_SIZE);
}

void send(){
	char name[BUF_SIZE] = {0};
	char content[BUF_SIZE] = {0};

	printf("Creating message\n");
	printf("Enter message name:");
	fgets(name, BUF_SIZE, stdin);
	printf("Enter message content:");
	fgets(content, BUF_SIZE, stdin);

	printf("name: \"%s\"\ncontent:\"%s\"\n", name, content);
}

int menu(){
	char buffer[BUF_SIZE] = {0};

	printf("[*] menu\n");
	printf("menu - show this menu\n");
	printf("send - send new message\n");
	printf("runner - run bytes\n");
	printf("exit - close program\n");
	
	fgets(buffer, BUF_SIZE, stdin);

	if (strcmp(buffer, "menu\n") == 0){
		return 1;
	}
	else if (strcmp(buffer, "send\n") == 0){
		send();
		return 1;
	}
	else if (strcmp(buffer, "runner\n") == 0){
		runner();
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
	printf("Welcome to ch06!\n");
	while(1){
		if (!(menu())){
			break;
		}
		printf("\n");
	}
	printf("Exiting...\n");
}
