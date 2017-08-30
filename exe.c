#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	useconds_t usec = 1000000;
	if(argc == 2)
		usec = strtoull(argv[1], NULL, 10);

	int filedes[2]; // write at 1. read at 0.
	pipe(filedes);
	// 0 standard in. 1 standard out.
	pid_t pid = fork();
	if(!pid){
		close(0);
		if(dup(filedes[0]) != 0)
			return 1; // unsucessful replacement of stdin.

		close(filedes[0]);
		close(filedes[1]);
		close(2);
		execle("/usr/bin/r2", "r2", "-d", "fact", (char*)0, __environ);
	
	
	}
	
	
	close(1);

	dup(filedes[1]);
	close(filedes[0]);
	close(2);
	char navagate_r2[] = "aaaa\ndb sym.main\ndc\nvpp\n";

	/* 
	 * aaaa -> analyze experimental version
	 * db sym.main -> add breakpoint to sym.main
	 * dc -> continue execution
	 * vpp -> visual, print(rotate), print(rotate)
	 *
	 */
	char termsize[] = "e scr.columns=100\n\
			   e scr.rows=50\n";

	struct termios termios_old, termios_new;
	tcgetattr(0, &termios_old);
	memcpy(&termios_new, &termios_old, sizeof(termios_old));
	//unset canonical mode.
	termios_new.c_lflag &= ~ICANON;
	termios_new.c_cc[VMIN] = 0;
	termios_new.c_cc[VTIME] = 0;

	char ch = 0;

	tcsetattr(0, TCSANOW, &termios_new);
	write(filedes[1], termsize, sizeof(termsize));
	write(filedes[1], navagate_r2, sizeof(navagate_r2));
	int quit = 0;
	while(!quit){
		write(filedes[1], "s\n", 2);
		usleep(usec);
		read(0, &ch, 1);
		if(ch == 'q')
			quit = 1;
	}

	kill(pid, SIGTERM);
	tcsetattr(0, TCSANOW, &termios_old);

	return 0;
}
