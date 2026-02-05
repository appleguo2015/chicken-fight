#include <cstdio>
#include <cstdlib> 
#include <unistd.h>
#include <ctime>
#include "../chicken.h"
#include "../game_read.h"
#include "../drawer.h"
#include "../bullet.h"
#include "AIController.h"

chicken* c01; // Chicken object pointer
bullet* b01;  // Bullet object pointer
drawer* d01;  // Drawer object pointer
AIController* ai01; // AI Controller
int nx = 30;  // Current X coordinate of the chicken
int bullet_move_delay = 1; // Bullet movement delay (Higher value = Slower speed; 1 = Fastest)

// Update game state function
// Return value: true means game over (collision occurred), false means game continues
bool update(){
    static int frame_count = 0;
    frame_count++;
    // Use ANSI escape code to clear screen and move cursor to top-left
    printf("\033[2J\033[H");

    c01->check(); // Update chicken state
    c01->changeX(nx); // Update chicken position
    
    // Check collision before movement
    bool collision = b01->checkCollision(c01);
    
    // Control bullet speed
    if (frame_count % bullet_move_delay == 0) {
        b01->move();
    }
    
    // Check collision after movement
    if (!collision) {
        collision = b01->checkCollision(c01);
    }
    
    // If bullet moves out of screen left, reset to random position on right
    if (b01->x < 0) {
        // Generate new position randomly between 60 and 100
        b01->x = 60 + rand() % 41;
    }

    d01->draw(c01, b01); // Draw current frame
    return collision;
}

int main(){
    srand(time(NULL)); // Initialize random number seed
    d01 = new drawer();
    ai01 = new AIController();
	gr1.set_nonblocking_mode(true); // Set terminal to non-blocking mode
	c01 = new chicken(nx);
    b01 = new bullet(0);
	char a = 'a';
    
    // Game main loop
	while(a != 'q'){
		if(update()){
            printf("Game Over! AI Failed!\n");
            break;
        }
        usleep(30000); // Control game frame rate, approx 33fps
        
        // Check for manual quit
        char manual_input = gr1.getKey();
        if (manual_input == 'q') {
            break;
        }

        // Get AI decision
		a = ai01->decide(c01, b01, nx);
        
		switch(a){
			case 'h':
			case 'a':
				if(nx > 0)
					nx--; // Move left
				break;
			case 'k':
			case 'd':
				nx++; // Move right
				break;
            case ' ':
                // Space key toggles standing/ducking state
                if(c01->state) {
                    c01->up();
                } else {
                    c01->down();
                }
                break;
			default:
				break;
		}
	}
	gr1.set_nonblocking_mode(false); // Restore terminal settings
	return 0;
}
