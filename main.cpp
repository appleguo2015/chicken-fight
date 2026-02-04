#include <cstdio>
#include <cstdlib> 
#include <unistd.h>
#include <ctime>
#include "chicken.h"
#include "game_read.h"
#include "drawer.h"
#include "bullet.h"

chicken* c01; // Chicken object pointer
bullet* b01;  // Bullet object pointer
drawer* d01;  // Drawer object pointer
int nx = 30;  // Current X coordinate of the chicken
int bullet_move_delay = 1; // Bullet movement delay (Higher value = Slower speed; 1 = Fastest)

// Update game state function
// Return value: true means game over (collision occurred), false means game continues
bool update(){
    static int frame_count = 0;
    frame_count++;
    // Use ANSI escape code to clear screen and move cursor to top-left (Faster than system("clear"))
    printf("\033[2J\033[H");

    c01->check(); // Update chicken state (e.g., change appearance based on ducking)
    c01->changeX(nx); // Update chicken position
    
    // Check collision before movement (prevent chicken from walking into bullet)
    bool collision = b01->checkCollision(c01);
    
    // Control bullet speed: move every 'bullet_move_delay' frames
    if (frame_count % bullet_move_delay == 0) {
        b01->move();
    }
    
    // Check collision after movement (prevent bullet from flying into chicken)
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
	gr1.set_nonblocking_mode(true); // Set terminal to non-blocking mode (input without enter)
	c01 = new chicken(nx);
    b01 = new bullet(0);
	char a = 'a';
    
    // Game main loop
	while(a != 'q'){
		if(update()){
            printf("Game Over!\n");
            break;
        }
        usleep(30000); // Control game frame rate, approx 33fps (Lower value = Faster game)
		a = gr1.getKey(); // Get user input
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
