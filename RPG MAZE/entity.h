#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "utils.h"

class MovableEntity;
class Hollow;

class Entity {

    public:
        // Pointer to the hollow (For each entity)
        Hollow* hollow;
        // Location of the entity (Level, x, y)
        Location loc;

        // General constructor for Entity 
        Entity(Hollow* hollow, const Location& loc) : hollow(hollow), loc(loc) {}
        // Virtual default destructor
        virtual ~Entity() = default;

        // Return a ptr by "new" using the object copy's constructor (new 返同一個object 然後return address)
        virtual Entity* newPtr() const = 0;
        // String repr of the entity (For printing)
        virtual std::string toString() const = 0;
        // Update the current entity when being pushed 
        virtual bool update(MovableEntity* fromEntity, Direction toDir) = 0;

};

#endif