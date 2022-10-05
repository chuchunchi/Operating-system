#include<iostream>
#include<unistd.h>
#include<vector>
#include<string>
#include<cstring>
#include<fcntl.h>
#include<sys/wait.h>

using namespace std;
int main(void)
{
	pid_t pid;
	cout << "Main Process ID : " << getpid() << '\n';
	pid = fork(); //fork 1
	if(pid==0){
		cout << "Fork 1. I'm the child " << getpid() << ", my parent is " << getppid() << "." << '\n';
		pid = fork(); //fork 2
		if(pid==0){
			cout << "Fork 2. I'm the child " << getpid() << ", my parent is " << getppid() << "." << '\n';
			pid = fork(); //fork 3
			if(pid==0){
				cout << "Fork 3. I'm the child " << getpid() << ", my parent is " << getppid() << "." << '\n';
			}
			else{
				wait(NULL);
			}
		}
		else{
			wait(NULL);
		}
}
	else{
		wait(NULL);
	}
	return 0;
}
