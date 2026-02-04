#ifndef _GR
#define _GR
#include <unistd.h>
#include <termios.h>
struct gr{
    // Set terminal mode
    // enable = true: Non-blocking mode (input without enter confirmation, no echo)
    // enable = false: Restore standard mode
	void set_nonblocking_mode(bool enable) {
    	static struct termios oldt, newt;
    
    	if (enable) {
        	tcgetattr(STDIN_FILENO, &oldt); // Save current terminal settings
        	newt = oldt;
        	newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode (no enter) and echo
        	newt.c_cc[VMIN] = 0; // Set min read characters to 0 (non-blocking)
        	newt.c_cc[VTIME] = 0; // Set read timeout to 0
        	tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Apply new settings
    	} else {
        	tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore old settings
    	}
	}

    // Get key input
	char getKey() {
    	char ch = 0;
    	read(STDIN_FILENO, &ch, 1); // Read one character
    	return ch;
	}
}gr1;
#endif
