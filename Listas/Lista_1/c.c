#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 256

int main() {
	int return_value;
	char script[MAX_COMMAND_LENGTH], arguments[MAX_COMMAND_LENGTH];
	float real_time, total_time = 0.0;
	struct timespec start, stop;
	
	while (scanf("%s %s", script, arguments) != EOF) {
		fflush(stdout);
		timespec_get(&start, TIME_UTC);
		
		if (!fork()) {
			execl(script, script, arguments, (char*) NULL);
			printf("> Erro: %s\n", strerror(errno));
			return_value = errno;
			fclose(stdin);
			exit(errno);
		} 
		else {
			wait(&return_value);
			timespec_get(&stop, TIME_UTC);
			real_time = (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec) / 1e9;
			printf("> Demorou %.1f segundos, retornou %d\n", real_time, WEXITSTATUS(return_value));
			total_time += real_time;
		}
	}

	printf(">> O tempo total foi de %.1f segundos\n", total_time);
	
	return 0;
}