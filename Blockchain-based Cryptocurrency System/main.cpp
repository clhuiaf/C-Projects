#include <iostream>
#include "bitcoin.h"

using namespace std;

void printMenu() {
    cout << "1. Add a user to the system" << endl;
    cout << "2. Add some bitcoins to a user" << endl;
    cout << "3. Add a transaction to the pending transactions" << endl;
    cout << "4. Mine a block with the pending transactions" << endl;
    cout << "5. Print the blockchain" << endl;
    cout << "6. Print the users" << endl;
    cout << "7. Print the pending transactions" << endl;
    cout << "8. Exit" << endl;
}

int main() {
    BitcoinSystem system;

    bool exit = false;
    while (!exit) {
        printMenu();
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: {
                string name;
                cout << "Enter the name of the user: ";
                cin >> name;
                system.addUser(name);
                break;
            }
            case 2: {
                string name;
                int amount;
                cout << "Enter the name of the user: ";
                cin >> name;
                cout << "Enter the amount: ";
                cin >> amount;
                system.addBitcoinToUser(name, amount);
                break;
            }
            case 3: {
                string sender, receiver;
                int amount, fee;
                cout << "Enter the sender: ";
                cin >> sender;
                cout << "Enter the receiver: ";
                cin >> receiver;
                cout << "Enter the amount: ";
                cin >> amount;
                cout << "Enter the fee: ";
                cin >> fee;
                system.transact(sender, receiver, amount, fee);
                break;
            }
            case 4: {
                system.mineBlock();
                break;
            }
            case 5: {
                system.printBlockchain();
                break;
            }
            case 6: {
                system.printUsers();
                break;
            }
            case 7: {
                system.printPendingTransactions();
                break;
            }
            case 8: {
                exit = true;
                break;
            }
            default: {
                cout << "Invalid choice" << endl;
                break;
            }
        }
    }
}
