// Child process exits while Parent sleeps, becoming a Zombie

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int main() {
	pid_t child_pid = fork();

	if (child_pid > 0) {	// Parent
		printf("Parent PID:	%d\n", getpid());
		sleep(5);

		FILE *Z;
		char s[100];

		// system("ps aux | awk '{ print $8 " " $2 }' | grep -w Z");
		Z = popen("ps aux | awk '{ print $8 " " $2 }' | grep -w Z", "r");
		fgets(s, 100, Z);
		printf("Zombie PID:	%s\n", s);
		pclose(Z);

		printf("Parent awakening after 5 s\n");
	}
	else if (child_pid == 0) {	// Child
		printf("Child PID:	%d\n", getpid());
		exit(0);
	}
	else if (child_pid < 0) {
		printf("Fork failed\n");
	}

	return 0;
}
