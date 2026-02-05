#ifndef AI_CONTROLLER_H
#define AI_CONTROLLER_H

#include "../chicken.h"
#include "../bullet.h"

class AIController {
public:
    // Decision function
    // Returns a char representing the key press: ' ' (toggle duck), 'a' (left), 'd' (right), or 0 (no action)
    char decide(chicken* c, bullet* b, int chicken_x) {
        // Calculate distance between bullet and chicken
        // Bullet moves from right (positive) to left (negative)
        // Collision happens when b->x == c->x
        
        int dist = b->x - chicken_x;
        
        // Safety threshold
        // If bullet is within 5 units to the right, or just passing (>-2)
        bool danger = (dist >= -2 && dist <= 6);
        
        if (danger) {
            // If danger and currently standing, duck!
            if (c->state == 0) {
                return ' ';
            }
        } else {
            // If safe and currently ducking, stand up!
            if (c->state == 1) {
                return ' ';
            }
            
            // If safe and standing, maybe center the chicken
            // Target X around 30
            if (chicken_x < 28) return 'd'; // Move right
            if (chicken_x > 32) return 'a'; // Move left
        }
        
        return 0; // No input
    }
};

#endif
