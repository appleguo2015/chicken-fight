#ifndef _CHICKEN
#define _CHICKEN
class chicken {
public:
    int x;          // Chicken X coordinate
    int state = 0;  // State: 0=standing, 1=ducking
    const char *c[4] = {}; // Character array storing chicken appearance (includes color codes)

    // Constructor
    chicken(int x_ = 0) {
        check(); // Initialize appearance
        x = x_;
    };

    ~chicken() {};

    // Change X coordinate
    void changeX(int x_) { x = x_; };

    // Update chicken appearance based on state
    void check() {
        // state 0: standing (up) 
        // state 1: ducking (down)
        if (state) {
            // Ducking state:
            // First line (head) is empty
            // Second line shows body
            // Third line shows legs
            c[0] = "";
            c[1] = "\033[37m_\033[30;47m%\033[0m\033[33m-\033[0m";
            c[2] = "\033[37m##\033[0m";
        } else {
            // Standing state:
            // First line shows head
            // Second line shows body
            // Third line shows legs
            c[0] = "\033[37m_\033[30;47m%\033[0m\033[33m-\033[0m";
            c[1] = "\033[37m##\033[0m";
            c[2] = "\033[31m^^\033[0m";
        }
    }

    // Switch to ducking state
    void down() {
        state = 1;
        check();
    }

    // Switch to standing state
    void up() {
        state = 0;
        check();
    }
};
#endif
