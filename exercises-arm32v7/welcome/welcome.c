//__author__ = '@tomereyz'
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv){
  uid_t uid = geteuid();
  setresuid(uid,uid,uid);
  system("cat flag");
}
