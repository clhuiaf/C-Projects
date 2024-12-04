#include "hollow.h"

using namespace std; 

// ==== Complete your tasks after this line ====

Hollow::Hollow(int level, int height, int width) : levels(level), height(height), width(width){

    // Allocate memory for the grid
    grid = new BlockEntity***[levels]; 
    for (int z = 0; z < levels; z++) {
        grid[z] = new BlockEntity**[height]; 
        for (int y = 0; y < height; y++) {
            grid[z][y] = new BlockEntity*[width]; 
        }
    }

    // Loop through all layers to do initialization
    for (int z = 0; z < levels; z++){
        for (int y = 0; y < height; y++){
            for (int x = 0; x < width; x++){
                // Create new location object for the object
                Location new_loc(z,x,y);
                // Create new Empty object for the current entry
                grid[z][y][x] = new Empty(this,new_loc); 
            }
        }
    }

}

Hollow::~Hollow(){


    for (int z = 0; z < levels; z++){
        for (int y = 0; y < height; y++){
            for (int x = 0; x < width; x++){
                // Delete MovabeEntity (If any)
                if (grid[z][y][x]->mentity != nullptr){
                    delete grid[z][y][x]->mentity;
                }
                // Delete BlockEntity
                delete grid[z][y][x];
            }
            // Delete BlockEntity*
            delete [] grid[z][y];
        }
        // Delete BlockEntity**
        delete [] grid[z];
    }
    // Delete BlockEntity***
    delete [] grid;

    // BlockEntity**** ptr will be dellocate by the Stack
    
}


BlockEntity* Hollow::registerBlockEntity(const BlockEntity& bentity){

    // Free the original object
    if (grid[bentity.loc.level][bentity.loc.y][bentity.loc.x] != nullptr){
        delete grid[bentity.loc.level][bentity.loc.y][bentity.loc.x];
    }
    // Copy the original object
    grid[bentity.loc.level][bentity.loc.y][bentity.loc.x] = bentity.newPtr();
    return grid[bentity.loc.level][bentity.loc.y][bentity.loc.x];

}

MovableEntity* Hollow::registerMovableEntity(const MovableEntity& mentity){

    // Free the original object
    if (grid[mentity.loc.level][mentity.loc.y][mentity.loc.x]->mentity != nullptr){
        delete grid[mentity.loc.level][mentity.loc.y][mentity.loc.x]->mentity;
    }

    // Assign the MovableEntity to BlockEntity's pointer to MovableEntity
    grid[mentity.loc.level][mentity.loc.y][mentity.loc.x]->mentity = mentity.newPtr();
    return grid[mentity.loc.level][mentity.loc.y][mentity.loc.x]->mentity;

}


BangBoo* Hollow::registerBangBoo(const BangBoo& bangboo){

    // Does nothing for any subsequent calls
    if (this->bangboo != nullptr)
        return nullptr;

    // Assign Bangboo to the grid
    this->bangboo = bangboo.newPtr();
    grid[bangboo.loc.level][bangboo.loc.y][bangboo.loc.x]->mentity = this->bangboo;
    return this->bangboo;

}

bool Hollow::locInHollow(const Location& loc) const {

    return ((loc.level >= 0 && loc.level < levels) && (loc.x >= 0 && loc.x < width) && (loc.y >= 0 && loc.y < height)) ? true : false;

}

void Hollow::print() const {

    for (int j = 0; j < height*2+1; j++){
            
            if (j % 2 == 0){
                
                for (int i = 0; i < width*2+1; i++){
                    if (i % 2 == 0)
                        cout << '+';
                    else
                        cout << " - ";
                }
                
                cout << endl;
                
            }
            
            else{
        
                for (int i = 0; i < width*2+1; i++){
                    if (i % 2 == 0)
                        cout << '|';
                    else
                        // cout << " x ";
                        cout << ' ' << grid[bangboo->loc.level][(j-1)/2][(i-1)/2]->toString() << ' ';
                }
                
                cout << endl;
            
            }
            
        }

}