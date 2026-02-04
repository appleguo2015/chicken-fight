#ifndef _DRAWER
#define _DRAWER
#include <cstdio>
class drawer{
public:
    drawer(){};
    ~drawer(){};
    
    // Draw game scene
    // T1: Chicken type, T2: Bullet type
    template<typename T1, typename T2>
    void draw(T1* ch, T2* b){
        int lens[3];
        // Set character length occupied by chicken for each row based on state
        // Length used to calculate relative position when bullet and chicken are on same row
        if (ch->state) { // Ducking (Down)
            lens[0] = 0; // Head row empty
            lens[1] = 3; // Body row length
            lens[2] = 2; // Leg row length
        } else { // Standing (Up)
            lens[0] = 3; // Head row length
            lens[1] = 2; // Body row length
            lens[2] = 2; // Leg row length
        }

        for(int i = 0; i < 3; i++){
            // Draw collision effect (if collision occurs)
            // Condition: Bullet within chicken range, on first row (head), and chicken not ducking
            if(b->x >= ch->x && b->x < ch->x + 2 && i == 0 && !ch->state){
                drawspace(ch->x);
                printf("\033[31m**\033[0m\n"); // Red collision mark
                continue;
            }

            // Draw bullet on first row
            if (i == 0) {
                int ch_x = ch->x;
                int b_x = b->x;
                int ch_len = lens[i];

                if (ch_len == 0) {
                    // Chicken ducking, no chicken on first row, draw bullet directly
                    drawspace(b_x);
                    printf("*\n");
                } else {
                    // Standing state, handle relative position of bullet and chicken
                    if (b_x > ch_x + ch_len) {
                        // Bullet to the right of chicken
                        drawspace(ch_x);
                        printf("%s", ch->c[i]);
                        drawspace(b_x - (ch_x + ch_len));
                        printf("*\n");
                    } else if (b_x < ch_x) {
                        // Bullet to the left of chicken
                        drawspace(b_x);
                        printf("*");
                        drawspace(ch_x - b_x - 1);
                        printf("%s\n", ch->c[i]);
                    } else {
                        // Overlap (usually covered by collision effect above, but as fallback)
                        drawspace(ch_x);
                        printf("%s\n", ch->c[i]);
                    }
                }
            } else {
                // Draw only chicken on other rows
                drawspace(ch->x);
                printf("%s\n", ch->c[i]);
            }
        }
    }

    // Draw specified number of spaces
    void drawspace(int max_){
        for(int i = 0; i < max_; i++){
            printf(" ");
        }
    }
};
#endif
