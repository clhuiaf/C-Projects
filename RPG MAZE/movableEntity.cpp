#include "movableEntity.h"
#include "hollow.h"
// ==== Complete your tasks after this line ====

// #include <iostream>
// using namespace std;

bool MovableEntity::update(MovableEntity* fromEntity, Direction toDir){

    // Create new Location object
    Location new_loc = loc.addDir(toDir);

    // Check whether the next Location is in the Hollow
    if (hollow->locInHollow(new_loc)){

        // Get blocks
        BlockEntity* current_block = hollow->getBlockEntityFromLoc(loc); // Caller
        BlockEntity* next_block = hollow->getBlockEntityFromLoc(new_loc); 

        // Check whether the next block is occupied by MovableEntity
        if (next_block->mentity == nullptr){
            // Check if next block is steppable (Choose Bangboo as the moving entity to avoid conflict)
            if (next_block->update(current_block->mentity, toDir)){

                    /* Check whether you are leave the Button */
                    if (current_block->stringRepr() == "◈"){
                        current_block->onLeave(current_block->mentity); // If it is not Button, it does nothing
                    }

                    // Empty
                    if (next_block->stringRepr() == " "){
                        hollow->moveMentityFromTo(current_block->mentity, loc, new_loc);
                        return true;
                    }
                    // Goal
                    else if (next_block->stringRepr() == "G"){
                        hollow->moveMentityFromTo(current_block->mentity, loc, new_loc);
                        next_block->onStep(next_block->mentity);
                        return true;
                    }
                    // Portal
                    else if (next_block->stringRepr() == "↟" || next_block->stringRepr() == "↡"){
                        hollow->moveMentityFromTo(current_block->mentity, loc, new_loc);
                        next_block->onStep(next_block->mentity);
                        return true;
                    }
                    // Unlocked Door
                    else if (next_block->stringRepr() == "⬚"){
                        hollow->moveMentityFromTo(current_block->mentity, loc, new_loc);
                        return true;
                    }
                    // Off Switch
                    else if (next_block->stringRepr() == "◇"){
                        hollow->moveMentityFromTo(current_block->mentity, loc, new_loc);
                        next_block->onStep(next_block->mentity);
                        return true;
                    }
                    // On Switch (Liver)
                    else if (next_block->stringRepr() == "◈"){
                        hollow->moveMentityFromTo(current_block->mentity, loc, new_loc);
                        // next_block->onStep(next_block->mentity); (Conflict)
                        return true;
                    }

            }
                
            // Hit Walls or locked Doors
            else{
                return false;
            }
                
        }

        // The next block is occupied by a MovableEntity
        else{

            // Deal with Stones
            if (next_block->toString() == "◍"){
                // Ask whether the next block is available
                // Recursive way to allocate space
                if (next_block->mentity->update(nullptr, toDir)){

                    // Off the Button if leaving from it
                    if (current_block->stringRepr() == "◈"){
                        current_block->onLeave(current_block->mentity);
                    }
                    // Change position
                    hollow->moveMentityFromTo(current_block->mentity, loc, new_loc);
                    // On the Button if it is being stepped
                    if (next_block->stringRepr() == "◇"){
                        next_block->onStep(next_block->mentity);
                    }
                    // Trigger teleport if stepped on Portal
                    else if (next_block->stringRepr() == "↟" || next_block->stringRepr() == "↡"){
                        next_block->onStep(next_block->mentity);
                    }

                    return true;

                }
                    
                else{
                    return false;
                }

            }

            // Deal with Boxes
            if (next_block->toString() == "☒"){
                
                // Steppable
                if (next_block->mentity->update(nullptr, toDir)){

                    // Serial moves
                    if (next_block->mentity == nullptr){

                        // Off the Button if leaving from it
                        if (current_block->stringRepr() == "◈"){
                            current_block->onLeave(current_block->mentity);
                        }
                        // Change position
                        hollow->moveMentityFromTo(current_block->mentity, loc, new_loc);
                        // On the Button if it is being stepped
                        if (next_block->stringRepr() == "◇"){
                            next_block->onStep(next_block->mentity);
                        }
                        // Trigger teleport if stepped on Portal
                        else if (next_block->stringRepr() == "↟" || next_block->stringRepr() == "↡"){
                            next_block->onStep(next_block->mentity);
                        }

                        return true;

                    }
                    
                }
                
                // Not steppable
                else{

                    // Only swap with Bangboo
                    if (current_block->toString() == "☺"){
                        MovableEntity* temp = current_block->mentity;
                        hollow->moveMentityFromTo(next_block->mentity, new_loc, loc);
                        hollow->moveMentityFromTo(temp, loc, new_loc);
                        return true;
                    }

                }
            
            }

        }

    }

    // Out of bound
    else{
        return false;
    }

    // Additional return value
    return false;

}

bool Box::update(MovableEntity* fromEntity, Direction toDir){

    // Create new Location object
    Location new_loc = loc.addDir(toDir);

    // Check whether the next Location is in the Hollow
    if (hollow->locInHollow(new_loc)){

        // Get blocks
        BlockEntity* current_block = hollow->getBlockEntityFromLoc(loc);
        BlockEntity* next_block = hollow->getBlockEntityFromLoc(new_loc);

        // Check whether the next BlockEntity is steppable
        if (next_block->update(current_block->mentity, toDir)){
    
            // Check whether the next block is steppable
            if (next_block->mentity == nullptr){

                // Serial moves (The caller must be Box MovableEntity)
                hollow->moveMentityFromTo(current_block->mentity, loc, new_loc); // Make sure that current_block->mentity = nullptr
                // Implicit turn on the Button 
                if (next_block->stringRepr() == "◇"){
                    next_block->onStep(next_block->mentity);
                }
                return true;

            }

            // If the next box is MovableEntity -> recursion
            else if (next_block->mentity != nullptr){

                // Why block update failed?
                if (next_block->mentity->update(nullptr,toDir)){
                    hollow->moveMentityFromTo(current_block->mentity, loc, new_loc);
                    return true;
                }

                else{
                    return false; 
                }

            }
        
        }

        // The next BlockEntity is Locked Door/ Wall
        else{
            return false;
        }

    }

    // Out of Bound
    else{
        return false;
    }

    // Additional return value
    return false;

}

