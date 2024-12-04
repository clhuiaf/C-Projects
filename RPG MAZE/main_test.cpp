#include <iostream>
#include <cassert>

#ifdef _WIN32
#include <windows.h>
#endif

#include "fairy.h"

using namespace std;

// To avoid encoding issues on Windows, while Mac/Linux is fine with this issue
void setupWindows() {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif 
}

int main() {

    setupWindows();

    cout << "Please input test case number: ";
    int testid;
    cin >> testid;
    cout << endl;

    switch(testid) {
        case 1:
        {
            cout << "Try to initalize an empty hollow" << endl;
            Hollow *hollow = new Hollow(3, 5, 5);
            assert(hollow->getHollowLevels() == 3);
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 5; j++) {
                    for (int k = 0; k < 5; k++) {
                        assert(hollow->getBlockEntityFromLoc(Location(i, j, k))->toString() == " ");
                    }
                }
            }
            cout << "Test 1 done" << endl;
            delete hollow;
            break;
        }
        case 2:
        {
            Hollow *hollow = new Hollow(2, 3, 3);
            cout << "Try to register block entities to the hollow" << endl;
            cout << "Register Wall at (0, 0, 0)" << endl;
            hollow->registerBlockEntity(Wall(hollow, Location(0, 0, 0)));
            cout << "Register Door at (0, 1, 1)" << endl;
            hollow->registerBlockEntity(Door(hollow, Location(0, 1, 1)));
            cout << "Register Portal (Move up) at (0, 0, 2)" << endl;
            hollow->registerBlockEntity(Portal(hollow, Location(0, 0, 2), false));
            cout << "Register Goal at (1, 2, 0)" << endl;
            hollow->registerBlockEntity(Goal(hollow, Location(1, 2, 0)));
            cout << "Register Lever at (1, 2, 1)" << endl;
            hollow->registerBlockEntity(Lever(hollow, Location(1, 2, 1)));
            cout << "Register Portal (Move down) at (1, 0, 2)" << endl;
            hollow->registerBlockEntity(Portal(hollow, Location(1, 0, 2), true));
            cout << "The block entity at (0, 0, 0) is: " << hollow->getBlockEntityFromLoc(Location(0, 0, 0))->toString() << endl;
            cout << "The block entity at (0, 1, 1) is: " << hollow->getBlockEntityFromLoc(Location(0, 1, 1))->toString() << endl;
            cout << "The block entity at (0, 0, 2) is: " << hollow->getBlockEntityFromLoc(Location(0, 0, 2))->toString() << endl;
            cout << "The block entity at (1, 2, 0) is: " << hollow->getBlockEntityFromLoc(Location(1, 2, 0))->toString() << endl;
            cout << "The block entity at (1, 2, 1) is: " << hollow->getBlockEntityFromLoc(Location(1, 2, 1))->toString() << endl;
            cout << "The block entity at (1, 0, 2) is: " << hollow->getBlockEntityFromLoc(Location(1, 0, 2))->toString() << endl;
            cout << "Test 2 done" << endl;
            delete hollow;
            break;
        }
        case 3:
        {
            Hollow *hollow = new Hollow(1, 2, 2);
            cout << "Try to register movable entities to the hollow" << endl;
            cout << "Register Box at (0, 0, 0)" << endl;
            hollow->registerMovableEntity(Box(hollow, Location(0, 0, 0)));
            cout << "Register Box at (0, 0, 1)" << endl;
            hollow->registerMovableEntity(Box(hollow, Location(0, 0, 1)));
            cout << "Register Stone at (0, 1, 0)" << endl;
            hollow->registerMovableEntity(Stone(hollow, Location(0, 1, 0)));
            cout<< "Register Box at (0, 1, 1)" << endl;
            hollow->registerMovableEntity(Box(hollow, Location(0, 1, 1)));
            cout << "The movable entity at (0, 0, 0) is: " << hollow->getBlockEntityFromLoc(Location(0, 0, 0))->mentity->toString() << endl;
            cout << "The movable entity at (0, 1, 0) is: " << hollow->getBlockEntityFromLoc(Location(0, 1, 0))->mentity->toString() << endl;
            cout << "The movable entity at (0, 0, 1) is: " << hollow->getBlockEntityFromLoc(Location(0, 0, 1))->mentity->toString() << endl;
            cout << "The movable entity at (0, 1, 1) is: " << hollow->getBlockEntityFromLoc(Location(0, 1, 1))->mentity->toString() << endl;
            cout << "Test 3 done" << endl;
            delete hollow;
            break;
        }
        case 4:
        {
            Hollow *hollow = new Hollow(1, 2, 2);
            cout << "Try to register BangBoo to the hollow" << endl;
            hollow->registerBangBoo(BangBoo(hollow, Location(0, 1, 0)));
            hollow->registerBangBoo(BangBoo(hollow, Location(0, 1, 1)));
            hollow->registerBangBoo(BangBoo(hollow, Location(0, 0, 1)));
            hollow->registerBangBoo(BangBoo(hollow, Location(0, 0, 0)));
            cout << "BangBoo at (0, 0, 0): " << boolalpha << (hollow->getBlockEntityFromLoc(Location(0, 0, 0))->mentity ? hollow->getBlockEntityFromLoc(Location(0, 0, 0))->mentity->isBangBoo() : false) << endl;
            cout << "BangBoo at (0, 0, 1): " << boolalpha << (hollow->getBlockEntityFromLoc(Location(0, 0, 1))->mentity ? hollow->getBlockEntityFromLoc(Location(0, 0, 1))->mentity->isBangBoo() : false) << endl;
            cout << "BangBoo at (0, 1, 0): " << boolalpha << (hollow->getBlockEntityFromLoc(Location(0, 1, 0))->mentity ? hollow->getBlockEntityFromLoc(Location(0, 1, 0))->mentity->isBangBoo() : false) << endl;
            cout << "BangBoo at (0, 1, 1): " << boolalpha << (hollow->getBlockEntityFromLoc(Location(0, 1, 1))->mentity ? hollow->getBlockEntityFromLoc(Location(0, 1, 1))->mentity->isBangBoo() : false) << endl;
            cout << "Test 4 done" << endl;
            delete hollow;
            break;
        }
        case 5:
        {
            Hollow *hollow = new Hollow(3, 5, 4);
            cout << "Create a hollow with 3 levels, each level has width=4 and height=5" << endl;
            cout << "The location (2, 0, 0) is in hollow: " << boolalpha << hollow->locInHollow(Location(2, 0, 0)) << endl;
            cout << "The location (3, 0, 0) is in hollow: " << boolalpha << hollow->locInHollow(Location(3, 0, 0)) << endl;
            cout << "The location (0, 4, 0) is in hollow: " << boolalpha << hollow->locInHollow(Location(0, 4, 0)) << endl;
            cout << "The location (0, 0, 4) is in hollow: " << boolalpha << hollow->locInHollow(Location(0, 0, 4)) << endl;
            cout << "The location (3, 4, 5) is in hollow: " << boolalpha << hollow->locInHollow(Location(3, 4, 5)) << endl;
            cout << "The location (2, 3, 4) is in hollow: " << boolalpha << hollow->locInHollow(Location(2, 3, 4)) << endl;
            cout << "Test 5 done" << endl;
            delete hollow;
            break;
        }
        case 6:
        {
            Hollow *hollow = new Hollow(2, 5, 5);
            cout << "Initialize a hollow..." << endl;
            hollow->registerBlockEntity(Wall(hollow, Location(0, 2, 4)));
            hollow->registerBlockEntity(Lever(hollow, Location(0, 1, 1)));
            hollow->registerBlockEntity(Button(hollow, Location(0, 3, 2)));
            hollow->registerBlockEntity(Door(hollow, Location(0, 4, 3)));
            hollow->registerBlockEntity(Portal(hollow, Location(0, 4, 4), false));
            hollow->registerBlockEntity(Portal(hollow, Location(1, 4, 4), true));
            hollow->registerBlockEntity(Goal(hollow, Location(1, 2, 2)));
            hollow->registerMovableEntity(Box(hollow, Location(1, 1, 0)));
            hollow->registerMovableEntity(Box(hollow, Location(1, 1, 1)));
            hollow->registerMovableEntity(Stone(hollow, Location(1, 1, 2)));
            hollow->registerMovableEntity(Stone(hollow, Location(1, 1, 3)));
            hollow->registerBangBoo(BangBoo(hollow, Location(0, 0, 4)));
            cout << "Print Level 0:" << endl;
            hollow->print();
            hollow->moveMentityFromTo(hollow->getBlockEntityFromLoc(Location(0, 0, 4))->mentity, Location(0, 0, 4), Location(1, 2, 1));
            cout << "Now move BangBoo to (1, 2, 1)" << endl;
            cout << "Print Level 1:" << endl;
            hollow->print();
            cout << "Test 6 done" << endl;
            delete hollow;
            break;
        }
        case 7:
        {
            Hollow *hollow = new Hollow(1, 3, 3);
            cout << "Initialize a hollow..." << endl;
            Door* door1 = dynamic_cast<Door*>(hollow->registerBlockEntity(Door(hollow, Location(0, 1, 1))));
            Door* door2 = dynamic_cast<Door*>(hollow->registerBlockEntity(Door(hollow, Location(0, 0, 2))));
            Door* door3 = dynamic_cast<Door*>(hollow->registerBlockEntity(Door(hollow, Location(0, 1, 2))));
            Door* door4 = dynamic_cast<Door*>(hollow->registerBlockEntity(Door(hollow, Location(0, 2, 2))));
            Lever* lever1 = dynamic_cast<Lever*>(hollow->registerBlockEntity(Lever(hollow, Location(0, 0, 0))));
            Lever* lever2 = dynamic_cast<Lever*>(hollow->registerBlockEntity(Lever(hollow, Location(0, 2, 0))));
            Button* button = dynamic_cast<Button*>(hollow->registerBlockEntity(Button(hollow, Location(0, 1, 0))));
            lever1->addDoorConn(door1);
            lever1->addDoorConn(door3);
            lever2->addDoorConn(door2);
            lever2->addDoorConn(door3);
            button->addDoorConn(door4);
            button->addDoorConn(door2);
            door1->addSwitchConn(lever1);
            door2->addSwitchConn(lever2);
            door2->addSwitchConn(button);
            door3->addSwitchConn(lever1);
            door3->addSwitchConn(lever2);
            door4->addSwitchConn(button);
            BangBoo* bangboo = dynamic_cast<BangBoo*>(hollow->registerBangBoo(BangBoo(hollow, Location(0, 0, 1))));
            // simulated movement: no real movement, just call onStep and onLeave
            lever1->onStep(bangboo);
            cout << "Door 1 connected to lever 1" << endl;
            cout << "Door 2 connected to lever 2 and button" << endl;
            cout << "Door 3 connected to lever 1 and lever 2" << endl;
            cout << "Door 4 connected to button" << endl;
            cout << "BangBoo moves to lever 1" << endl;
            cout << "The status of Door 1 is: " << (door1->toString() == "⬚" ? "unlocked" : "locked") << endl;
            cout << "The status of Door 2 is: " << (door2->toString() == "⬚" ? "unlocked" : "locked") << endl;
            cout << "The status of Door 3 is: " << (door3->toString() == "⬚" ? "unlocked" : "locked") << endl;
            cout << "The status of Door 4 is: " << (door4->toString() == "⬚" ? "unlocked" : "locked") << endl;
            lever2->onStep(bangboo);
            cout << "BangBoo moves to lever 2" << endl;
            cout << "The status of Door 1 is: " << (door1->toString() == "⬚" ? "unlocked" : "locked") << endl;
            cout << "The status of Door 2 is: " << (door2->toString() == "⬚" ? "unlocked" : "locked") << endl;
            cout << "The status of Door 3 is: " << (door3->toString() == "⬚" ? "unlocked" : "locked") << endl;
            cout << "The status of Door 4 is: " << (door4->toString() == "⬚" ? "unlocked" : "locked") << endl;
            button->onStep(bangboo);
            cout << "BangBoo moves to and stays at button" << endl;
            cout << "The status of Door 1 is: " << (door1->toString() == "⬚" ? "unlocked" : "locked") << endl;
            cout << "The status of Door 2 is: " << (door2->toString() == "⬚" ? "unlocked" : "locked") << endl;
            cout << "The status of Door 3 is: " << (door3->toString() == "⬚" ? "unlocked" : "locked") << endl;
            cout << "The status of Door 4 is: " << (door4->toString() == "⬚" ? "unlocked" : "locked") << endl;
            cout << "Test 7 done" << endl;
            delete hollow;
            break;
        }
        case 8:
        {
            Hollow *hollow = new Hollow(1, 3, 3);
            cout << "Initialize a hollow..." << endl;
            Door* door1 = dynamic_cast<Door*>(hollow->registerBlockEntity(Door(hollow, Location(0, 1, 1))));
            Door* door2 = dynamic_cast<Door*>(hollow->registerBlockEntity(Door(hollow, Location(0, 0, 2))));
            Door* door3 = dynamic_cast<Door*>(hollow->registerBlockEntity(Door(hollow, Location(0, 2, 2))));
            Button* button1 = dynamic_cast<Button*>(hollow->registerBlockEntity(Button(hollow, Location(0, 0, 0))));
            Button* button2 = dynamic_cast<Button*>(hollow->registerBlockEntity(Button(hollow, Location(0, 2, 0))));
            button1->addDoorConn(door1);
            button1->addDoorConn(door3);
            button2->addDoorConn(door1);
            button2->addDoorConn(door2);
            door1->addSwitchConn(button1);
            door1->addSwitchConn(button2);
            door2->addSwitchConn(button2);
            door3->addSwitchConn(button1);
            BangBoo* bangboo = dynamic_cast<BangBoo*>(hollow->registerBangBoo(BangBoo(hollow, Location(0, 1, 0))));
            // simulated movement: no real movement, just call onStep and onLeave
            button1->onStep(bangboo);
            cout << "Initial status:" << endl;
            cout << "Hollow size: 1 level, 3 width, 3 height" << endl;
            cout << "Door 1 connected to button 1 and button 2" << endl;
            cout << "Door 2 connected to button 2" << endl;
            cout << "Door 3 connected to button 1" << endl;
            cout << "BangBoo moves to button 1" << endl;
            cout << "The status of Door 1 is: " << (door1->toString() == "⬚" ? "unlocked" : "locked") << endl;
            cout << "The status of Door 2 is: " << (door2->toString() == "⬚" ? "unlocked" : "locked") << endl;
            cout << "The status of Door 3 is: " << (door3->toString() == "⬚" ? "unlocked" : "locked") << endl;
            button1->onLeave(bangboo);
            button2->onStep(bangboo);
            cout << "BangBoo moves to button 2" << endl;
            cout << "The status of Door 1 is: " << (door1->toString() == "⬚" ? "unlocked" : "locked") << endl;
            cout << "The status of Door 2 is: " << (door2->toString() == "⬚" ? "unlocked" : "locked") << endl;
            cout << "The status of Door 3 is: " << (door3->toString() == "⬚" ? "unlocked" : "locked") << endl;
            button2->onLeave(bangboo);
            cout << "BangBoo goes away to somewhere else" << endl;
            cout << "The status of Door 1 is: " << (door1->toString() == "⬚" ? "unlocked" : "locked") << endl;
            cout << "The status of Door 2 is: " << (door2->toString() == "⬚" ? "unlocked" : "locked") << endl;
            cout << "The status of Door 3 is: " << (door3->toString() == "⬚" ? "unlocked" : "locked") << endl;
            cout << "Test 8 done" << endl;
            delete hollow;
            break;
        }
        case 9:
        {
            Hollow *hollow = new Hollow(2, 2, 2);
            Portal* portal1 = static_cast<Portal*>(hollow->registerBlockEntity(Portal(hollow, Location(0, 1, 1), false)));
            Portal* portal2 = static_cast<Portal*>(hollow->registerBlockEntity(Portal(hollow, Location(1, 1, 1), true)));
            BangBoo* bangboo = static_cast<BangBoo*>(hollow->registerBangBoo(BangBoo(hollow, Location(0, 0, 0))));
            Box *box = static_cast<Box*>(hollow->registerMovableEntity(Box(hollow, Location(0, 0, 1))));
                        
            cout << "Initial status:" << endl;
            cout << "Hollow size: 2 level, 2 width, 2 height" << endl;
            cout << "Entrace of portal at location (0, 1, 1)" << endl;
            cout << "Exit of portal at location (1, 1, 1)" << endl;
            cout << "The movable entity at entrance of portal is: " << (hollow->getBlockEntityFromLoc(Location(0, 1, 1))->mentity ? hollow->getBlockEntityFromLoc(Location(0, 1, 1))->mentity->toString() : "empty") << endl;
            cout << "The movable entity at exit of portal is: " << (hollow->getBlockEntityFromLoc(Location(1, 1, 1))->mentity ? hollow->getBlockEntityFromLoc(Location(1, 1, 1))->mentity->toString() : "empty") << endl;
            hollow->moveMentityFromTo(box, Location(0, 0, 1), Location(0, 1, 1));
            portal1->onStep(box);
            cout << "Box has been moved to the portal" << endl;
            cout << "The movable entity at at entrance of portal is: " << (hollow->getBlockEntityFromLoc(Location(0, 1, 1))->mentity ? hollow->getBlockEntityFromLoc(Location(0, 1, 1))->mentity->toString() : "empty") << endl;
            cout << "The movable entity at exit of portal is: " << (hollow->getBlockEntityFromLoc(Location(1, 1, 1))->mentity ? hollow->getBlockEntityFromLoc(Location(1, 1, 1))->mentity->toString() : "empty") << endl;
            hollow->moveMentityFromTo(box, Location(0, 1, 1), Location(0, 0, 1));
            hollow->moveMentityFromTo(bangboo, Location(0, 0, 0), Location(0, 1, 1));
            portal1->onStep(bangboo);
            cout << "BangBoo has been moved to the portal" << endl;
            cout << "The movable entity at entrance of portal is: " << (hollow->getBlockEntityFromLoc(Location(0, 1, 1))->mentity ? hollow->getBlockEntityFromLoc(Location(0, 1, 1))->mentity->toString() : "empty") << endl;
            cout << "The movable entity at exit of portal is: " << (hollow->getBlockEntityFromLoc(Location(1, 1, 1))->mentity ? hollow->getBlockEntityFromLoc(Location(1, 1, 1))->mentity->toString() : "empty") << endl;
            cout << "Test 9 done" << endl;
            delete hollow;
            break;
        }
        case 10:
        {
            Hollow *hollow = new Hollow(1, 2, 2);
            Goal* goal = static_cast<Goal*>(hollow->registerBlockEntity(Goal(hollow, Location(0, 1, 1))));
            Box* box = static_cast<Box*>(hollow->registerMovableEntity(Box(hollow, Location(0, 1, 0))));
            Stone* stone = static_cast<Stone*>(hollow->registerMovableEntity(Stone(hollow, Location(0, 0, 1))));
            BangBoo* bangboo = static_cast<BangBoo*>(hollow->registerBangBoo(BangBoo(hollow, Location(0, 0, 0))));
            // simulated movement: no real movement, just call onStep
            goal->onStep(box);
            cout << "The box has been moved to the goal" << endl;
            cout << "Is game over? " << boolalpha << hollow->checkGameWon() << endl;
            goal->onStep(stone);
            cout << "The stone has been moved to the goal" << endl;
            cout << "Is game over? " << boolalpha << hollow->checkGameWon() << endl;
            goal->onStep(bangboo);
            cout << "The bangboo has been moved to the goal" << endl;
            cout << "Is game over? " << boolalpha << hollow->checkGameWon() << endl;
            cout << "Test 10 done" << endl;
            delete hollow;
            break;
        }
        case 11:
        {
            Hollow *hollow = new Hollow(1, 2, 2);
            BangBoo* bangboo = static_cast<BangBoo*>(hollow->registerBangBoo(BangBoo(hollow, Location(0, 0, 0))));

            cout << "Initial status:" << endl;
            cout << "Hollow size: 1 level, 2 width, 2 height" << endl;
            cout << "BangBoo at (0, 0, 0)" << endl;
            hollow->moveUpdate(Direction::UP);
            cout << "Is BangBoo at (0, 0, 0)? " << boolalpha << (hollow->getBlockEntityFromLoc(Location(0, 0, 0))->mentity ? hollow->getBlockEntityFromLoc(Location(0, 0, 0))->mentity->isBangBoo() : false) << endl;
            hollow->moveUpdate(Direction::DOWN);
            cout << "Is BangBoo at (0, 0, 0)? " << boolalpha << (hollow->getBlockEntityFromLoc(Location(0, 0, 0))->mentity ? hollow->getBlockEntityFromLoc(Location(0, 0, 0))->mentity->isBangBoo() : false) << endl;
            cout << "Is BangBoo at (0, 0, 1)? " << boolalpha << (hollow->getBlockEntityFromLoc(Location(0, 0, 1))->mentity ? hollow->getBlockEntityFromLoc(Location(0, 0, 1))->mentity->isBangBoo() : false) << endl;
            hollow->moveUpdate(Direction::LEFT);
            cout << "Is BangBoo at (0, 0, 1)? " << boolalpha << (hollow->getBlockEntityFromLoc(Location(0, 0, 1))->mentity ? hollow->getBlockEntityFromLoc(Location(0, 0, 1))->mentity->isBangBoo() : false) << endl;
            hollow->moveUpdate(Direction::RIGHT);
            cout << "Is BangBoo at (0, 0, 1)? " << boolalpha << (hollow->getBlockEntityFromLoc(Location(0, 0, 1))->mentity ? hollow->getBlockEntityFromLoc(Location(0, 0, 1))->mentity->isBangBoo() : false) << endl;
            cout << "Is BangBoo at (0, 1, 1)? " << boolalpha << (hollow->getBlockEntityFromLoc(Location(0, 1, 1))->mentity ? hollow->getBlockEntityFromLoc(Location(0, 1, 1))->mentity->isBangBoo() : false) << endl;
            cout << "Test 11 done" << endl;
            delete hollow;
            break;
        }
        case 12:
        {
            Hollow *hollow = new Hollow(1, 3, 3);
            hollow->registerBlockEntity(Wall(hollow, Location(0, 0, 0)));
            hollow->registerBlockEntity(Wall(hollow, Location(0, 0, 1)));
            hollow->registerBlockEntity(Wall(hollow, Location(0, 0, 2)));
            hollow->registerBlockEntity(Wall(hollow, Location(0, 2, 1)));
            hollow->registerBlockEntity(Wall(hollow, Location(0, 2, 0)));
            hollow->registerBlockEntity(Wall(hollow, Location(0, 2, 2)));
            hollow->registerBangBoo(BangBoo(hollow, Location(0, 1, 1)));
            cout << "Initial status:" << endl;
            cout << "Hollow size: 1 level, 3 width, 3 height" << endl;
            cout << "Walls at (0, 0, 0), (0, 0, 1), (0, 0, 2), (0, 2, 0), (0, 2, 1), (0, 2, 2)" << endl;
            cout << "BangBoo at (0, 1, 1)" << endl;
            hollow->moveUpdate(Direction::UP);
            cout << "BangBoo tries to move up" << endl;
            cout << "Is BangBoo at (0, 1, 1)? " << boolalpha << (hollow->getBlockEntityFromLoc(Location(0, 1, 1))->mentity ? hollow->getBlockEntityFromLoc(Location(0, 1, 1))->mentity->isBangBoo() : false) << endl;
            cout << "Is BangBoo at (0, 1, 0)? " << boolalpha << (hollow->getBlockEntityFromLoc(Location(0, 1, 0))->mentity ? hollow->getBlockEntityFromLoc(Location(0, 1, 0))->mentity->isBangBoo() : false) << endl;
            hollow->moveUpdate(Direction::DOWN);
            cout << "BangBoo tries to move down" << endl;
            hollow->moveUpdate(Direction::DOWN);
            cout << "BangBoo tries to move down" << endl;
            cout << "Is BangBoo at (0, 1, 2)? " << boolalpha << (hollow->getBlockEntityFromLoc(Location(0, 1, 2))->mentity ? hollow->getBlockEntityFromLoc(Location(0, 1, 2))->mentity->isBangBoo() : false) << endl;
            hollow->moveUpdate(Direction::LEFT);
            cout << "BangBoo tries to move left" << endl;
            hollow->moveUpdate(Direction::UP);
            cout << "BangBoo tries to move up" << endl;
            cout << "Is BangBoo at (0, 0, 1)? " << boolalpha << (hollow->getBlockEntityFromLoc(Location(0, 0, 1))->mentity ? hollow->getBlockEntityFromLoc(Location(0, 0, 1))->mentity->isBangBoo() : false) << endl;
            cout << "Is BangBoo at (0, 1, 1)? " << boolalpha << (hollow->getBlockEntityFromLoc(Location(0, 1, 1))->mentity ? hollow->getBlockEntityFromLoc(Location(0, 1, 1))->mentity->isBangBoo() : false) << endl;
            hollow->moveUpdate(Direction::UP);
            cout << "BangBoo tries to move up" << endl;
            hollow->moveUpdate(Direction::RIGHT);
            cout << "BangBoo tries to move right" << endl;
            hollow->moveUpdate(Direction::DOWN);
            cout << "BangBoo tries to move down" << endl;
            hollow->moveUpdate(Direction::DOWN);
            cout << "BangBoo tries to move down" << endl;
            cout << "Is BangBoo at (0, 2, 1)? " << boolalpha << (hollow->getBlockEntityFromLoc(Location(0, 2, 1))->mentity ? hollow->getBlockEntityFromLoc(Location(0, 2, 1))->mentity->isBangBoo() : false) << endl;
            cout << "Is BangBoo at (0, 1, 2)? " << boolalpha << (hollow->getBlockEntityFromLoc(Location(0, 1, 2))->mentity ? hollow->getBlockEntityFromLoc(Location(0, 1, 2))->mentity->isBangBoo() : false) << endl;
            cout << "Test 12 done" << endl;
            delete hollow;
            break;
        }
        case 13:
        {            
            Hollow *hollow = new Hollow(1, 3, 3);
            hollow->registerBlockEntity(Wall(hollow, Location(0, 1, 1)));
            hollow->registerBlockEntity(Wall(hollow, Location(0, 1, 2)));
            Lever* lever = dynamic_cast<Lever*>(hollow->registerBlockEntity(Lever(hollow, Location(0, 0, 2))));
            Door* door = dynamic_cast<Door*>(hollow->registerBlockEntity(Door(hollow, Location(0, 2, 1))));
            hollow->registerBangBoo(BangBoo(hollow, Location(0, 0, 0)));
            Box* box = dynamic_cast<Box*>(hollow->registerMovableEntity(Box(hollow, Location(0, 0, 1))));
            lever->addDoorConn(door);
            door->addSwitchConn(lever);
            cout << "Initial status:" << endl;
            cout << "Hollow size: 1 level, 3 width, 3 height" << endl;
            cout << "Walls at (0, 1, 1), (0, 1, 2)" << endl;
            cout << "BangBoo at (0, 0, 0)" << endl;
            cout << "Door at (0, 2, 1)" << endl;
            cout << "Box at (0, 0, 1)" << endl;
            cout << "The door is " << ((door->toString() == "⬚") ? "unlocked" : "locked") << " right now" << endl;
            hollow->moveUpdate(Direction::RIGHT);
            cout << "BangBoo tries to move right" << endl;
            hollow->moveUpdate(Direction::RIGHT);
            cout << "BangBoo tries to move right" << endl;
            hollow->moveUpdate(Direction::DOWN);
            cout << "BangBoo tries to move down" << endl;
            cout << "Is BangBoo at (0, 2, 1)? " << boolalpha << (hollow->getBlockEntityFromLoc(Location(0, 2, 1))->mentity ? hollow->getBlockEntityFromLoc(Location(0, 2, 1))->mentity->isBangBoo() : false) << endl;
            cout << "Is BangBoo at (0, 2, 0)? " << boolalpha << (hollow->getBlockEntityFromLoc(Location(0, 2, 0))->mentity ? hollow->getBlockEntityFromLoc(Location(0, 2, 0))->mentity->isBangBoo() : false) << endl;
            cout << "Secret power move the box to the switch" << endl;
            hollow->moveMentityFromTo(box, Location(0, 0, 1), Location(0, 0, 2));
            lever->onStep(box);
            cout << "The box has been moved to the switch" << endl;
            cout << "The door is " << ((door->toString() == "⬚") ? "unlocked" : "locked") << " right now" << endl;
            hollow->moveUpdate(Direction::DOWN);
            cout << "BangBoo tries to move down" << endl;
            cout << "Is BangBoo at (0, 2, 1)? " << boolalpha << (hollow->getBlockEntityFromLoc(Location(0, 2, 1))->mentity ? hollow->getBlockEntityFromLoc(Location(0, 2, 1))->mentity->isBangBoo() : false) << endl;
            // test
            cout << "Testing\n";
            hollow->moveUpdate(Direction::DOWN);
            cout << "BangBoo tries to move down" << endl;
            cout << "Is BangBoo at (0, 2, 2)? " << boolalpha << (hollow->getBlockEntityFromLoc(Location(0, 2, 2))->mentity ? hollow->getBlockEntityFromLoc(Location(0, 2, 2))->mentity->isBangBoo() : false) << endl;
            cout << "Test 13 done" << endl;
            delete hollow;
            break;
        }
        case 14:
        {
            Hollow *hollow = new Hollow(1, 4, 4);
            hollow->registerMovableEntity(Stone(hollow, Location(0, 0, 1)));
            hollow->registerMovableEntity(Stone(hollow, Location(0, 0, 2)));
            hollow->registerMovableEntity(Stone(hollow, Location(0, 1, 0)));
            hollow->registerMovableEntity(Stone(hollow, Location(0, 1, 1)));
            hollow->registerMovableEntity(Stone(hollow, Location(0, 1, 2)));
            hollow->registerMovableEntity(Stone(hollow, Location(0, 2, 0)));
            hollow->registerMovableEntity(Stone(hollow, Location(0, 2, 1)));
            hollow->registerMovableEntity(Stone(hollow, Location(0, 2, 2)));
            hollow->registerMovableEntity(Stone(hollow, Location(0, 3, 0)));
            hollow->registerBangBoo(BangBoo(hollow, Location(0, 0, 0)));
            cout << "Initial map:" << endl;
            hollow->print();
            hollow->moveUpdate(Direction::RIGHT);
            cout << "BangBoo tries to move right" << endl;
            hollow->moveUpdate(Direction::DOWN);
            cout << "BangBoo tries to move down" << endl;
            hollow->moveUpdate(Direction::RIGHT);
            cout << "BangBoo tries to move right" << endl;
            hollow->moveUpdate(Direction::DOWN);
            cout << "BangBoo tries to move down" << endl;
            cout << "Current map:" << endl;
            hollow->print();
            hollow->moveUpdate(Direction::RIGHT);
            cout << "BangBoo tries to move right" << endl;
            hollow->moveUpdate(Direction::DOWN);
            cout << "BangBoo tries to move down" << endl;
            hollow->moveUpdate(Direction::RIGHT);
            cout << "BangBoo tries to move right" << endl;
            hollow->moveUpdate(Direction::UP);
            cout << "BangBoo tries to move up" << endl;
            cout << "Current map:" << endl;
            hollow->print();
            cout << "Test 14 done" << endl;
            delete hollow;
            break;
        }
        case 15:
        {
            Hollow *hollow = new Hollow(1, 4, 4);
            hollow->registerMovableEntity(Box(hollow, Location(0, 0, 1)));
            hollow->registerMovableEntity(Box(hollow, Location(0, 0, 2)));
            hollow->registerMovableEntity(Box(hollow, Location(0, 0, 3)));
            hollow->registerMovableEntity(Box(hollow, Location(0, 1, 0)));
            hollow->registerMovableEntity(Box(hollow, Location(0, 1, 1)));
            hollow->registerMovableEntity(Box(hollow, Location(0, 1, 2)));
            hollow->registerMovableEntity(Box(hollow, Location(0, 2, 0)));
            hollow->registerMovableEntity(Box(hollow, Location(0, 2, 1)));
            hollow->registerMovableEntity(Box(hollow, Location(0, 2, 2)));
            hollow->registerMovableEntity(Box(hollow, Location(0, 3, 0)));
            hollow->registerMovableEntity(Box(hollow, Location(0, 3, 3)));
            hollow->registerBangBoo(BangBoo(hollow, Location(0, 0, 0)));
            cout << "Initial map:" << endl;
            hollow->print();
            hollow->moveUpdate(Direction::DOWN);
            cout << "BangBoo tries to move down" << endl;
            hollow->moveUpdate(Direction::DOWN);
            cout << "BangBoo tries to move down" << endl;
            hollow->moveUpdate(Direction::RIGHT);
            cout << "BangBoo tries to move right" << endl;
            cout << "Current map:" << endl;
            hollow->print();
            hollow->moveUpdate(Direction::UP);
            cout << "BangBoo tries to move up" << endl;
            hollow->moveUpdate(Direction::RIGHT);
            cout << "BangBoo tries to move right" << endl;
            hollow->moveUpdate(Direction::DOWN);
            cout << "BangBoo tries to move down" << endl;
            hollow->moveUpdate(Direction::RIGHT);
            cout << "BangBoo tries to move right" << endl;
            cout << "Current map:" << endl;
            hollow->print();
            cout << "Test 15 done" << endl;
            delete hollow;
            break;
        }
        case 16:
        {
            Hollow *hollow = new Hollow(1, 4, 4);
            hollow->registerMovableEntity(Stone(hollow, Location(0, 0, 1)));
            hollow->registerMovableEntity(Stone(hollow, Location(0, 0, 2)));
            hollow->registerMovableEntity(Stone(hollow, Location(0, 0, 3)));
            hollow->registerMovableEntity(Box(hollow, Location(0, 1, 0)));
            hollow->registerMovableEntity(Stone(hollow, Location(0, 1, 1)));
            hollow->registerMovableEntity(Box(hollow, Location(0, 1, 2)));
            hollow->registerMovableEntity(Box(hollow, Location(0, 2, 0)));
            hollow->registerMovableEntity(Box(hollow, Location(0, 2, 1)));
            hollow->registerMovableEntity(Stone(hollow, Location(0, 2, 2)));
            hollow->registerMovableEntity(Box(hollow, Location(0, 2, 3)));
            hollow->registerMovableEntity(Box(hollow, Location(0, 3, 0)));
            hollow->registerMovableEntity(Box(hollow, Location(0, 3, 1)));
            hollow->registerMovableEntity(Box(hollow, Location(0, 3, 2)));
            hollow->registerMovableEntity(Stone(hollow, Location(0, 3, 3)));
            hollow->registerBangBoo(BangBoo(hollow, Location(0, 0, 0)));
            cout << "Initial map:" << endl;
            hollow->print();
            hollow->moveUpdate(Direction::DOWN);
            cout << "BangBoo tries to move down" << endl;
            hollow->moveUpdate(Direction::RIGHT);
            cout << "BangBoo tries to move right" << endl;
            hollow->moveUpdate(Direction::DOWN);
            cout << "BangBoo tries to move down" << endl;
            hollow->moveUpdate(Direction::RIGHT);
            cout << "BangBoo tries to move right" << endl;
            cout << "Current map:" << endl;
            hollow->print();
            hollow->moveUpdate(Direction::DOWN);
            cout << "BangBoo tries to move down" << endl;
            hollow->moveUpdate(Direction::RIGHT);
            cout << "BangBoo tries to move right" << endl;
            hollow->moveUpdate(Direction::DOWN);
            cout << "BangBoo tries to move down" << endl;
            hollow->moveUpdate(Direction::DOWN);
            cout << "BangBoo tries to move down" << endl;
            cout << "Current map:" << endl;
            hollow->print();
            cout << "Test 16 done" << endl;
            delete hollow;
            break;
        }
        case 17:
        {
            Fairy fairy;
            fairy.readHollowFromFile("public_cases/additional_test_level.txt");
            string command = "ssddwaaswwddss";
            fairy.startConnection(command);
            break;
        }
        default:
        {
            cout << "Invalid test number!" << endl;
            break;
        }
    }
    return 0;
}