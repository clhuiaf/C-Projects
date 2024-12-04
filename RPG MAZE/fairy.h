#ifndef FAIRY_H
#define FAIRY_H

#include <fstream>
#include "hollow.h"

using namespace std;

// AI Manager
class Fairy {

    // Pointer to hollow
    private:
        Hollow* hollow = nullptr;

    public:
        // In main.cpp, should use Fairy to create Hollow instead of creating a Hollow yourself
        Hollow* createHollow(int levels, int height, int width) {
            if (!hollow) {
                hollow = new Hollow(levels, height, width);
                return hollow;
            }
            // If hollow ptr != nullptr -> return nullptr
            return nullptr;
        }

        ~Fairy() {
            delete hollow;
        }

        // Read Hollow setup from file
        Hollow* readHollowFromFile(string filename = "level.txt") {
            ifstream ifs;
            ifs.open(filename);
            
            if (ifs.is_open()) {
                int l, w, h, dsconn;
                ifs >> l >> w >> h >> dsconn;
                
                createHollow(l, h, w);
                if (!hollow) {return nullptr;}

                char tmpGrid[l][h][w];
                for (int i = 0; i < l; i++) {
                    for (int j = 0; j < h; j++) {
                        for (int k = 0; k < w; k++) {
                            ifs >> tmpGrid[i][j][k];
                            char curEntry = tmpGrid[i][j][k];
                            Location curLoc = Location(i, k, j);
                            if (curEntry == 'B') {
                                hollow->registerBangBoo(BangBoo(hollow, curLoc));
                            } else if (curEntry == 'X') {
                                hollow->registerMovableEntity(Box(hollow, curLoc));
                            } else if (curEntry == 'S') {
                                hollow->registerMovableEntity(Stone(hollow, curLoc));
                            } else if (curEntry == 'W') {
                                hollow->registerBlockEntity(Wall(hollow, curLoc));
                            } else if (curEntry == 'G') {
                                hollow->registerBlockEntity(Goal(hollow, curLoc));
                            } else if (curEntry == '>') {
                                hollow->registerBlockEntity(Portal(hollow, curLoc, false));
                            } else if (curEntry == '<') {
                                hollow->registerBlockEntity(Portal(hollow, curLoc, true));
                            } else if (curEntry == 'D') {
                                hollow->registerBlockEntity(Door(hollow, curLoc));
                            } else if (curEntry == 'L') {
                                hollow->registerBlockEntity(Lever(hollow, curLoc));
                            } else if (curEntry == 'O') {
                                hollow->registerBlockEntity(Button(hollow, curLoc));
                            }
                        }
                    }
                }

                // ???
                for (int i = 0; i < dsconn; i++) {
                    int al, ax, ay, bl, bx, by;
                    ifs >> al >> ax >> ay >> bl >> bx >> by;

                    if (tmpGrid[al][ay][ax] != 'D' || (tmpGrid[bl][by][bx] != 'L' && tmpGrid[bl][by][bx] != 'O')) {
                        cout << "Door / Switch connection should be on Door & Switch block entity!" << endl;
                        exit(-1);
                    }

                    Door* door = dynamic_cast<Door*>(hollow->getBlockEntityFromLoc(Location(al, ax, ay)));
                    Switch* sw = dynamic_cast<Switch*>(hollow->getBlockEntityFromLoc(Location(bl, bx, by)));

                    door->addSwitchConn(sw);
                    sw->addDoorConn(door);
                }

                return hollow;

            } 
            
            cout << "[ERR] Failed to find " + filename + "!" << endl;
            exit(-1);

        }

        // Start the game
        void startConnection() {
            
            while (true) {
                cout << "\n\n\n\n\n\n\n\n\n";
                hollow->print();

                cout << "=======================================================" << endl;
                cout << "Current level: " << hollow->getCurLevel() + 1 << "/" << hollow->getHollowLevels() << endl << endl;

                if (hollow->checkGameWon()) {
                    cout << "[*] You won! [*]" << endl;
                    break;
                }

                cout << "Input move (w/a/s/d, e to exit): ";
                
                string s;
                cin >> s;
                s = s.substr(0, 1);
                if (s == "w") {
                    hollow->moveUpdate(UP);
                } else if (s == "a") {
                    hollow->moveUpdate(LEFT);
                } else if (s == "s") {
                    hollow->moveUpdate(DOWN);
                } else if (s == "d") {
                    hollow->moveUpdate(RIGHT);
                } else if (s == "e") {
                    break;
                }
            }

        }

        void startConnection(string input_actions) {
            
            int action_steps = input_actions.size();

            for(int i=0; i < action_steps + 1; i++)
            {
                cout << "\n";
                hollow->print();

                cout << "=======================================================" << endl;
                cout << "Current level: " << hollow->getCurLevel() + 1 << "/" << hollow->getHollowLevels() << endl << endl;

                if (hollow->checkGameWon()) {
                    cout << "[*] You won! [*]" << endl;
                    break;
                }

                if(i == action_steps)
                    break;

                cout << "Input move (w/a/s/d, e to exit): ";
                
                string s = input_actions.substr(i, 1);
                cout << s << endl;
                if (s == "w") {
                    hollow->moveUpdate(UP);
                } else if (s == "a") {
                    hollow->moveUpdate(LEFT);
                } else if (s == "s") {
                    hollow->moveUpdate(DOWN);
                } else if (s == "d") {
                    hollow->moveUpdate(RIGHT);
                } else if (s == "e") {
                    break;
                }
            }
        }
};

#endif