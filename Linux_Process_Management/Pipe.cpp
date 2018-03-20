// Parent writes a string
// Child reads the string and reverses its case (Upper -> Lower; Lower -> Upper)
// Parent reads and prints the reversed case string

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <bits/stdc++.h>


using namespace std;


void reverseCase(char str[]) {
	for (int i = 0; str[i] != '\0'; i++) {
		if (isupper(str[i]))
			str[i] = tolower(str[i]);
		else if (islower(str[i]))
			str[i] = toupper(str[i]);
	}
}


int main() {
	char str[] = "Testing a Parent string";
	int len = strlen(str);
	char reversed[len];

	int fd_Parent[2];
	int fd_Child[2];

	pid_t pid;


	if (pipe(fd_Parent) == -1 || pipe(fd_Child) == -1)
		printf("Pipe failed\n");


	if (pid = fork() > 0) {		// Parent
		close(fd_Parent[0]);
		write(fd_Parent[1], str, len + 1);
		close(fd_Parent[1]);

		wait(NULL);

		close(fd_Child[1]);

		read(fd_Child[0], reversed, len);
		printf("Normal-case:	%s\n", str);
		printf("Reversed-case:	%s\n", reversed);

		close(fd_Child[0]);
	}
	else if (pid == 0) {	// Child
		close(fd_Parent[1]);

		read(fd_Parent[0], reversed, len);
		
		reverseCase(reversed);

		close(fd_Parent[0]);
		close(fd_Child[0]);

		write(fd_Child[1], reversed, len + 1);
		close(fd_Child[1]);

		exit(0);
	}
	else if (pid < 0) {
		printf("Fork failed\n");
	}

	return 0;
}
