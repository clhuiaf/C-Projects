#ifndef MOVEENTITY_H
#define MOVEENTITY_H

#include "entity.h"

class MovableEntity: public Entity {
    public:
        MovableEntity(Hollow* hollow, const Location& loc) : Entity(hollow, loc) {}

        virtual MovableEntity* newPtr() const override = 0;
        // toString() function override for MovableEntity
        virtual std::string toString() const override {return stringRepr();}
        // Internal string representation for MovableEntity
        virtual std::string stringRepr() const = 0;

        // Overrided by BangBoo to return true
        virtual bool isBangBoo() const {return false;}

        // TODO: The update function for MovableEntity
        virtual bool update(MovableEntity* fromEntity, Direction toDir) override;   

};

class BangBoo : public MovableEntity {
    public:
        BangBoo(Hollow* hollow, const Location& loc) : MovableEntity(hollow, loc) {}
        BangBoo* newPtr() const { return new BangBoo(*this); }
        std::string stringRepr() const { return "☺";}

        bool isBangBoo() const override {return true;}
};

class Stone : public MovableEntity {
    public:
        Stone(Hollow* hollow, const Location& loc) : MovableEntity(hollow, loc) {}
        Stone* newPtr() const { return new Stone(*this); }
        std::string stringRepr() const { return "◍";}
};

class Box : public MovableEntity {
    public:
        Box(Hollow* hollow, const Location& loc) : MovableEntity(hollow, loc) {}
        Box* newPtr() const { return new Box(*this); }
        std::string stringRepr() const { return "☒";}

        // TODO: The update function for Box
        bool update(MovableEntity* fromEntity, Direction toDir) override;

};

#endif