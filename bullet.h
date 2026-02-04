#ifndef _BULLET
#define _BULLET
class bullet{
public:
    int x; // Bullet X coordinate

    bullet(int x_ = 0) {
        x = x_;
    };

    ~bullet() {};

    // Move bullet left
    void move() {
        x--;
    };

    // Collision detection template function
    // T type is usually chicken class
    template<typename T>
    bool checkCollision(T *obj) {
        // If bullet matches object coordinates, and object is not in dodging state (e.g. ducking under high bullet)
        // obj->state 0 means standing, 1 means ducking
        // !obj->state true means standing state, which gets hit
        if (x == obj->x && !obj->state) {
            return true; // Collision occurred
        } else {
            return false; // No collision
        }
    };
};
#endif
