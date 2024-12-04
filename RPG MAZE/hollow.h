#ifndef HOLLOW_H
#define HOLLOW_H

#include <iostream>
#include "utils.h"
#include "blockEntity.h"

class Hollow {

    private:
        // Properties of the "grid"
        int levels, height, width;
        // Dynamic 3D array of BlockEntity*
        BlockEntity**** grid;
        // Storing the pointer of bangboo
        BangBoo* bangboo = nullptr;
        // Whether the game is ended (won)
        bool gameWon = false;

    public:

        // TODO: Constructor of the Hollow
        Hollow(int levels, int height, int width);

        // TODO: Destructor of the Hollow
        ~Hollow();

        // I will be good guy since it's hard to implement the copy constructor :)
        Hollow(const Hollow& hollow) = delete;

        // TODO: Register block entity to this hollow
        BlockEntity* registerBlockEntity(const BlockEntity& bentity);

        // TODO: Register movable entity to this hollow (except BangBoo - should use registerBangBoo instead)
        MovableEntity* registerMovableEntity(const MovableEntity& mentity);

        // TODO: Register BangBoo to this hollow
        BangBoo* registerBangBoo(const BangBoo& bangboo);

        // === When the bangboo is instructed a move operation ===
        // This will be the start of the update chain and you don't have to call this function yourself (Fairy will do it)
        void moveUpdate(Direction toDir) {
            getBlockEntityFromLoc(this->bangboo->loc)->update(nullptr, toDir);
        }

        // ======== Util functions: =========
        // * Which may be useful to you
        // ==================================

        // TODO: Return whether the location is in Hollow
        bool locInHollow(const Location& loc) const;

        // TODO: Print function of the Hollow
        void print() const;

        // Get the specified Entity in the grid
        BlockEntity* getBlockEntityFromLoc(const Location& loc) const {return grid[loc.level][loc.y][loc.x];}

        // Set mentity from the `from` location, to the `to` location (Move the MovableEntity)
        void moveMentityFromTo(MovableEntity* mentity, const Location& from, const Location& to) {
            // Avoid removing the latest movable entity if it have been updated by other entities somehow
            if (getBlockEntityFromLoc(from)->mentity == mentity) { 
                getBlockEntityFromLoc(from)->mentity = nullptr; // Remove the MovableEntity at 'from' location 
            }
            getBlockEntityFromLoc(to)->mentity = mentity; // Set the MovableEntity to 'to' location
            mentity->loc = to;
        }

        // Set win 
        void reachedGoal() {gameWon = true;}

        // ======== Other util functions: =========
        // * Which may not be useful to you
        // ========================================

        int getCurLevel() const {return this->bangboo->loc.level;} // Get Bangboo's current level
        int getHollowLevels() const {return this->levels;} // Get the total number of levels
        bool checkGameWon() {return gameWon;} // Check game status

};

#endif