#ifndef UTILS_H
#define UTILS_H

enum Direction {
    LEFT,
    RIGHT,
    DOWN,
    UP
};

struct Location {

    int level, x, y;

    // Create a Location object using given level, x, y
    Location(int level, int x, int y) : level(level), x(x), y(y) {}

    /*  
        Move to certain direction (while staying in the current level) 
        Return a new Location object
    */

    Location addDir(Direction dir) const {
        switch (dir) {
            case LEFT:
                return Location(level, x-1, y);
            case RIGHT:
                return Location(level, x+1, y);
            case UP:
                return Location(level, x, y-1);
            case DOWN:
                return Location(level, x, y+1);
            default:
                return Location(*this); // Pass it to the copy constructor and return the original location object
        }
    };

    /*
        Move to the next level while staying at the original 2D location
        Return a new Location object
    */
   
    Location addLevel(int dl) const {
        return Location(level + dl, x, y);
    }

};

#endif