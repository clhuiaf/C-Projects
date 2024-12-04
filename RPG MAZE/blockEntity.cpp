#include "blockEntity.h" // This has string library
#include "hollow.h"

// ==== Complete your tasks after this line ====

// #include <iostream>
// using namespace std;

void Switch::onStep(MovableEntity* mentity){

    // If the location of the MovableEntity matches that of the Switch object -> Set to On status
    isOn = true;
    // Update the status of the Door that is connected to this Switch
    for (int i = 0; i < doorNum; i++){
        lockDoors[i]->updateDoor();
    }
    
}

void Button::onLeave(MovableEntity* mentity){

    // If the location of the MovableEntity no longer matches that of the Switch object -> Set to Off status
    isOn = false;
    // Update the status of the Door that is connected to this Button
    for (int i = 0; i < doorNum; i++){
        lockDoors[i]->updateDoor();
    }

}

void Portal::onStep(MovableEntity* mentity){

    // Leave the function if the MovableEntity is not Bangboo
    if (!mentity->isBangBoo()){
        return;
    }

    std::string direction_str = stringRepr();
    int direction_const = 0;

    // Ascending
    if (direction_str == "↟"){
        direction_const = 1;
    }
    // Descending
    else if (direction_str == "↡"){
        direction_const = -1;
    }

    // Create new Location object
    Location new_loc = mentity->loc.addLevel(direction_const);

    // If the teleport destination already contains a movable entity, destroy that movable entity. (Avoid memory leak)
    if (hollow->getBlockEntityFromLoc(new_loc)->mentity != nullptr){
        delete hollow->getBlockEntityFromLoc(new_loc)->mentity;
    }

    // Move Bangboo to the next level
    mentity->hollow->moveMentityFromTo(mentity, mentity->loc, new_loc);

}

void Goal::onStep(MovableEntity* mentity){

    // Leave the function if the MovableEntity is not Bangboo
    if (!mentity->isBangBoo()){
        return;
    }

    // Set the game status to win
    mentity->hollow->reachedGoal();

}

/*
    1. Check the current BlockEntity first
    2. Check whether the next BlockEntity is occupied by other MovableEntity
        2.1. If not, move Bangboo to the next BlockEntity
        2.2. If yes, try to allocation space
    3. Move to the next Block if possible
    4. Going to the next iteration

*/
bool BlockEntity::update(MovableEntity* fromEntity, Direction toDir){

    // Update using the MovableEntity (Only if nullptr)
    if (fromEntity == nullptr){
        mentity->update(nullptr, toDir);
    }

    // Return true for all steppable BlockEntity
    return true;

}

bool Wall::update(MovableEntity* fromEntity, Direction toDir){
    return false;
}

bool Door::update(MovableEntity* fromEntity, Direction toDir){

    // Update using the MovableEntity
    if (fromEntity == nullptr){
        mentity->update(nullptr, toDir);
    }

    return !locked;
    
}

