#ifndef BASEENTITY_H
#define BASEENTITY_H

#include "movableEntity.h"

class BlockEntity : public Entity {
    public:
        // At most one MovableEntity stepped on itself
        MovableEntity* mentity = nullptr;
        
        // General constuctor
        BlockEntity(Hollow* hollow, const Location& loc) : Entity(hollow, loc) {}

        virtual BlockEntity* newPtr() const override = 0;
        // toString() function override for BlockEntity (Driver)
        virtual std::string toString() const override {return (mentity ? mentity->toString() : stringRepr());}
        // Internal string representation for BlockEntity (裏面嗰層)
        virtual std::string stringRepr() const = 0;
        
        // ======= Extra functions for BlockEntity to override ========
        virtual void onLeave(MovableEntity* mentity) {}
        virtual void onStep(MovableEntity* mentity) {}

        // TODO: The update function for BlockEntity
        virtual bool update(MovableEntity* fromEntity, Direction toDir) override;
        
};



// =====================================
// =========  START: Switch ============
// =====================================

class Door;
class Switch : public BlockEntity {
    protected:
        Door* lockDoors[5] = {}; // On switch is connected to at most five doors
        int doorNum = 0;
        bool isOn = false;
    
    public:
        Switch(Hollow* hollow, const Location& loc) : BlockEntity(hollow, loc) {}
        Switch* newPtr() const override = 0;
        std::string stringRepr() const {return (isOn ? "◈" : "◇");}

        // Used to add connection to Door during initialization of the game
        void addDoorConn(Door* door) {lockDoors[doorNum] = door; doorNum++;}
        // On/Off status getter
        bool getIsOn() const {return isOn;}
        
        // ======= Extra override ======
        // TODO: onStep function for Switch
        void onStep(MovableEntity* mentity) override;
};

class Lever : public Switch {
    public:
        Lever(Hollow* hollow, const Location& loc) : Switch(hollow, loc) {}
        Lever* newPtr() const { return new Lever(*this); }
};

class Button : public Switch {
    public:
        Button(Hollow* hollow, const Location& loc) : Switch(hollow, loc) {}
        Button* newPtr() const { return new Button(*this); }
        
        // ======= Extra override ======
        // TODO: onLeave function for Button
        void onLeave(MovableEntity* mentity) override;
};

// =====================================
// ==========  END: Switch =============
// =====================================




class Door : public BlockEntity {
    private:
        Switch* switches[5] = {}; // One door is connected to at most five switches
        int switchNum = 0;
        bool locked = true;
    
    public:
        Door(Hollow* hollow, const Location& loc) : BlockEntity(hollow, loc) {}
        Door* newPtr() const { return new Door(*this); }
        std::string stringRepr() const {return (locked ? "⌹" : "⬚");}

        // Used to add connection to Switch during initialization of the game
        void addSwitchConn(Switch* sw) {switches[switchNum] = sw; switchNum++;}
        // Update the status of the door, according to the status of the switch connected
        void updateDoor() {
            for (int i = 0; i < switchNum; i++) {
                if (!switches[i]->getIsOn()) { // One off -> All GG -> the door is still locked!!
                    locked = true;
                    return;
                }
            }
            locked = false;
        }

        // ======= Extra override ======
        // TODO: Update function for Door
        bool update(MovableEntity* fromEntity, Direction toDir) override;

};




// =====================================
// =======  START: Misc Blocks =========
// =====================================


class Goal : public BlockEntity {
    public:
        Goal(Hollow* hollow, const Location& loc) : BlockEntity(hollow, loc) {}
        Goal* newPtr() const { return new Goal(*this); }
        std::string stringRepr() const { return "G";}
        
        // ======= Extra override ======
        //TODO: onStep function for Goal
        void onStep(MovableEntity* mentity) override;
};

// Note: Only BangBoo can interact with Portal
class Portal : public BlockEntity {
    private:
        bool directionDown;
    public:
        Portal(Hollow* hollow, const Location& loc, bool directionDown) : BlockEntity(hollow, loc), directionDown(directionDown) {}
        Portal* newPtr() const { return new Portal(*this); }
        std::string stringRepr() const { return (directionDown ? "↡" : "↟");}

        // ======= Extra override ======
        //TODO: onStep function for Portal
        void onStep(MovableEntity* mentity) override;
};

class Wall : public BlockEntity {
    public:
        Wall(Hollow* hollow, const Location& loc) : BlockEntity(hollow, loc) {}
        Wall* newPtr() const { return new Wall(*this); }
        std::string stringRepr() const { return "▦";}
        
        // ======= Extra override ======
        //TODO: update function for Wall
        bool update(MovableEntity* fromEntity, Direction toDir) override;
};

class Empty : public BlockEntity {
    public:
        Empty(Hollow* hollow, const Location& loc) : BlockEntity(hollow, loc) {}
        std::string stringRepr() const { return " ";}
        Empty* newPtr() const { return new Empty(*this); }
};

// =====================================
// ========  END: Misc Blocks ==========
// =====================================



#endif