#include<iostream>
#include "bitcoin.h"

using namespace std;

int main() {
    cout << "Input test case number: ";
    int testCase;
    cin >> testCase;
    cout << endl;
    switch (testCase) {
        case 1: {
            BitcoinSystem system;

            system.addUser("Alice");

            system.printUsers();
            break;
        }
        case 2: {
            BitcoinSystem system;

            system.addUser("Alice");
            system.addUser("Bob");

            system.printUsers();
            break;
        }
        case 3: {
            BitcoinSystem system;

            system.addUser("Bob");
            system.addBitcoinToUser("Bob", 100);
            system.addBitcoinToUser("Bob", 50);

            system.printUsers();
            break;
        }
        case 4: {
            BitcoinSystem system;

            system.addUser("Bob");
            system.addUser("Alice");
            system.addBitcoinToUser("Bob", 18);
            system.addBitcoinToUser("Alice", 35);
            system.addBitcoinToUser("Bob", 20);
            system.addBitcoinToUser("Cindy", 10);

            system.printUsers();
            break;
        }
        case 5: {
            BitcoinSystem system;

            system.addUser("Alice");
            system.addUser("Bob");
            system.addUser("Desmond");
            system.addBitcoinToUser("Cindy", 100);
            system.addBitcoinToUser("Alice", 50);
            system.addBitcoinToUser("Bob", 30);
            system.addBitcoinToUser("Desmond", 20);

            system.printUsers();
            break;
        }
        case 6: {
            BitcoinSystem system;

            system.addUser("Alice");
            system.addUser("Bob");
            system.addBitcoinToUser("Alice", 100);
            system.transact("Alice", "Bob", 40, 5);

            system.printPendingTransactions();
            system.printUsers();
            break;
        }
        case 7: {
            BitcoinSystem system;

            system.addUser("Alice");
            system.addUser("Bob");
            system.addBitcoinToUser("Alice", 60);
            system.transact("Alice", "Bob", 40, 5);
            system.transact("Bob", "Alice", 20, 10);

            system.printPendingTransactions();
            system.printUsers();
            break;
        }
        case 8: {
            BitcoinSystem system;

            system.addUser("Cindy");
            system.addUser("Desmond");
            system.addBitcoinToUser("Cindy", 50);
            system.addBitcoinToUser("Desmond", 30);
            system.transact("Cindy", "Desmond", 40, 5);
            system.transact("Desmond", "Cindy", 20, 10);
            system.transact("Cindy", "Desmond", 10, 3);

            system.printPendingTransactions();
            system.printUsers();
            break;
        }
        case 9: {
            BitcoinSystem system;

            system.addUser("Alice");
            system.addUser("Bob");
            system.addUser("Cindy");
            system.addBitcoinToUser("Alice", 100);
            system.addBitcoinToUser("Bob", 50);
            system.addBitcoinToUser("Cindy", 30);
            system.transact("Alice", "Bob", 40, 5);
            system.transact("Bob", "Cindy", 20, 10);
            system.transact("Cindy", "Alice", 10, 3);
            system.transact("Alice", "Bob", 10, 4);
            system.transact("Desmond", "Cindy", 5, 6);

            system.printPendingTransactions();
            system.printUsers();
            break;
        }
        case 10: {
            BitcoinSystem system;

            system.addUser("Alice");
            system.addUser("Bob");
            system.addBitcoinToUser("Alice", 80);
            system.transact("Alice", "Bob", 40, 5);
            system.mineBlock();

            system.printBlockchain();
            system.printPendingTransactions();
            system.printUsers();
            break;
        }
        case 11: {
            BitcoinSystem system;

            system.addUser("Alice");
            system.addUser("Bob");
            system.addBitcoinToUser("Alice", 63);
            system.addBitcoinToUser("Bob", 30);
            system.mineBlock();
            system.transact("Alice", "Bob", 40, 5);
            system.mineBlock();

            system.printBlockchain();
            system.printPendingTransactions();
            system.printUsers();
            break;
        }
        case 12: {
            BitcoinSystem system;

            system.addUser("Desmond");
            system.addUser("Cindy");
            system.addBitcoinToUser("Desmond", 50);
            system.addBitcoinToUser("Cindy", 30);
            system.transact("Desmond", "Cindy", 40, 5);
            system.transact("Cindy", "Desmond", 20, 10);
            system.mineBlock();

            system.printBlockchain();
            system.printPendingTransactions();
            system.printUsers();
            break;
        }
        case 13: {
            BitcoinSystem system;

            system.addUser("Alice");
            system.addUser("Bob");
            system.addBitcoinToUser("Alice", 100);
            system.addBitcoinToUser("Bob", 50);

            system.transact("Alice", "Bob", 30, 3);
            system.transact("Bob", "Alice", 20, 2);
            system.printUsers();
            system.printPendingTransactions();
            system.mineBlock();
            system.printBlockchain();
            system.printUsers();
            break;
        }
        case 14: {
            BitcoinSystem system;

            system.addUser("Alice");
            system.addUser("Bob");
            system.addBitcoinToUser("Alice", 30);
            system.addBitcoinToUser("Alice", 20);
            system.addBitcoinToUser("Bob", 20);
            system.addBitcoinToUser("Bob", 50);
            system.transact("Alice", "Bob", 15, 3);
            system.transact("Bob", "Alice", 10, 2);
            system.transact("Alice", "Bob", 5, 1);
            system.transact("Bob", "Alice", 5, 0);
            system.mineBlock();

            system.printBlockchain();
            system.printPendingTransactions();
            system.printUsers();
            break;
        }
        case 15: {
            BitcoinSystem system;

            system.addUser("Alice");
            system.addUser("Bob");
            system.addBitcoinToUser("Alice", 100);
            system.addBitcoinToUser("Alice", 50);
            system.addBitcoinToUser("Alice", 30);
            system.addBitcoinToUser("Bob", 30);

            system.printUsers();
            system.transact("Alice", "Bob", 40, 5);
            system.transact("Bob", "Alice", 20, 10);
            system.transact("Alice", "Bob", 10, 4);
            system.transact("Alice", "Bob", 10, 0);
            system.mineBlock();
            system.printUsers();
            system.transact("Bob", "Alice", 20, 3);
            system.mineBlock();
            system.transact("Alice", "Bob", 10, 8);
            system.printBlockchain();
            system.printUsers();
            break;
        }
        case 16: {
            BitcoinSystem system;

            system.addUser("Alice");
            system.addUser("Bob");
            system.addUser("Cindy");
            system.addUser("Desmond");
            system.addBitcoinToUser("Alice", 100);
            system.addBitcoinToUser("Alice", 50);
            system.addBitcoinToUser("Alice", 30);
            system.addBitcoinToUser("Bob", 30);
            system.addBitcoinToUser("Bob", 20);
            system.addBitcoinToUser("Cindy", 20);
            system.addBitcoinToUser("Cindy", 10);
            system.addBitcoinToUser("Desmond", 10);
            system.addBitcoinToUser("Desmond", 10);
            system.addBitcoinToUser("Desmond", 10);

            system.printUsers();
            system.transact("Alice", "Bob", 40, 5);
            system.transact("Bob", "Alice", 23, 3);
            system.transact("Alice", "Desmond", 7, 1);
            system.transact("Bob", "Cindy", 10, 2);
            system.transact("Cindy", "Desmond", 5, 4);
            system.transact("Desmond", "Alice", 10, 8);
            system.transact("Alice", "Cindy", 30, 10);
            system.mineBlock();
            system.mineBlock();
            system.transact("Alice", "Desmond", 100, 9);
            system.transact("Desmond", "Bob", 27, 6);
            system.mineBlock();
            system.transact("Bob", "Cindy", 13, 2);
            system.transact("Cindy", "Desmond", 5, 1);
            system.transact("Desmond", "Alice", 10, 0);
            system.mineBlock();
            system.transact("Alice", "Cindy", 30, 12);
            system.printBlockchain();
            system.printUsers();
            break;
        }        
        case 17: {
            BitcoinSystem system;
            system.addUser("Brian");
            system.addUser("Desmond");
            system.addBitcoinToUser("Brian", 100);
            system.addBitcoinToUser("Desmond", 50);
            system.mineBlock();
            system.transact("Brian", "Desmond", 100, 50);
            system.mineBlock();
            system.transact("Desmond", "Brian", 50, 50);
            system.mineBlock();
            system.printBlockchain();
            system.printUsers();
            break;
        }
        case 18: {
            BitcoinSystem system;
            system.addUser("Alice");
            system.addUser("Bob");
            system.addBitcoinToUser("Alice", 100);
            system.printUsers();

            system.transact("Alice", "Bob", 50, 10);
            system.printPendingTransactions();
            system.mineBlock();
            system.printPendingTransactions();
            system.printBlockchain();
            system.printUsers();
            break;
        }
        case 19: {
            BitcoinSystem system;
            system.addUser("Alice");
            system.addUser("Bob");
            system.addUser("Cindy");

            system.addBitcoinToUser("Alice", 100);
            system.addBitcoinToUser("Bob", 50);
            system.addBitcoinToUser("Cindy", 30);

            system.transact("Alice", "Bob", 100, 10);
            system.transact("Bob", "Cindy", 50, 5);
            system.transact("Cindy", "Alice", 20, 2);

            system.mineBlock();
            system.printBlockchain();
            system.printUsers();
            break;

        }
        case 20: {
            BitcoinSystem system;
            system.addUser("Alice");
            system.addUser("Bob");
            system.addUser("Cindy");

            system.addBitcoinToUser("Alice", 100);
            system.addBitcoinToUser("Bob", 50);
            system.addBitcoinToUser("Cindy", 30);

            system.transact("Alice", "Bob", 50, 10);
            system.transact("Bob", "Cindy", 20, 5);
            system.transact("Cindy", "Alice", 10, 2);
            system.transact("Alice", "Bob", 20, 3);
            system.transact("Bob", "Cindy", 10, 6);
            system.transact("Cindy", "Alice", 5, 1);
            system.mineBlock();
            system.mineBlock();
            system.transact("Alice", "Bob", 20, 7);
            system.transact("Bob", "Cindy", 10, 8);
            system.transact("Cindy", "Alice", 5, 9);
            system.mineBlock();
            system.printBlockchain();
            system.printUsers();
            break;


        }
        case 21: {
            BitcoinSystem system;
            system.addUser("Alice");
            system.addUser("Bob");
            system.addUser("Cindy");

            system.addBitcoinToUser("Alice", 10);
            system.addBitcoinToUser("Bob", 10);
            system.addBitcoinToUser("Cindy", 10);

            system.transact("Alice", "Bob", 1, 6);
            system.transact("Bob", "Cindy", 1, 5);
            system.transact("Cindy", "Alice", 1, 4);
            system.transact("Alice", "Bob", 1, 9);
            system.mineBlock();
            system.printBlockchain();
            system.printUsers();


            system.transact("Alice", "Bob", 3, 2);
            system.transact("Alice", "Bob", 3, 1);
            system.transact("Cindy", "Alice", 3, 3);
            system.mineBlock();
            system.printBlockchain();
            system.printUsers();
            break;
        }
        case 22: {
            BitcoinSystem system;
            system.addUser("Alice");
            system.addUser("Bob");
            system.addUser("Cindy");

            system.addBitcoinToUser("Alice", 10);
            system.addBitcoinToUser("Bob", 10);
            system.addBitcoinToUser("Cindy", 10);

            system.transact("Alice", "Bob", 3, 1);
            system.transact("Cindy", "Alice", 3, 3);
            system.transact("Alice", "Bob", 1, 6);
            system.transact("Bob", "Cindy", 1, 5);
            system.transact("Cindy", "Alice", 1, 4);
            system.printPendingTransactions();

            system.transact("Alice", "Bob", 1, 9);
            system.transact("Alice", "Bob", 3, 2);
            system.printPendingTransactions();
            system.printUsers();
            break;
        }
        case 23: {
            BitcoinSystem system;
            system.addUser("Alice");
            system.addUser("Bob");

            system.addBitcoinToUser("Alice", 10);
            system.printUsers();
            system.addBitcoinToUser("Alice", 20);
            system.addBitcoinToUser("Alice", 30);
            system.addBitcoinToUser("Bob", 10);
            system.printUsers();

            break;
        }
        case 24: {
            BitcoinSystem system;
            system.transact("Alice", "Bob", 10, 5);
            system.mineBlock();
            system.printBlockchain();
            break;

        }
        case 25: {
            BitcoinSystem system;
            system.addUser("Alice");
            system.transact("Alice", "Bob", 10, 5);
            system.mineBlock();
            system.printBlockchain();
            break;

        }
        case 26: {
            BitcoinSystem system;
            system.addUser("Alice");
            system.addUser("Bob");

            system.addBitcoinToUser("Alice", 6);
            system.transact("Alice", "Bob", 5, 2);
            system.mineBlock();
            system.printBlockchain();
            break;
        }
        case 27: {
            BitcoinSystem system;
            system.addUser("Alice");
            system.addUser("Bob");
            system.addUser("Cindy");
            system.addUser("Desmond");
            system.addUser("Eve");

            system.addBitcoinToUser("Alice", 100);
            system.addBitcoinToUser("Bob", 50);
            system.addBitcoinToUser("Eve", 50);
            system.addBitcoinToUser("Cindy", 30);
            system.addBitcoinToUser("Bob", 20);
            system.addBitcoinToUser("Desmond", 70);
            system.addBitcoinToUser("Desmond", 20);
            system.addBitcoinToUser("Eve", 10);

            system.transact("Alice", "Bob", 40, 4);
            system.transact("Bob", "Eve", 20, 20);
            system.transact("Eve", "Alice", 10, 5);
            system.transact("Desmond", "Cindy", 50, 10);
            system.transact("Cindy", "Alice", 10, 6);
            system.transact("Bob", "Alice", 25, 25);
            system.mineBlock();
            system.transact("Alice", "Bob", 10, 8);
            system.transact("Desmond", "Cindy", 5, 7);
            system.mineBlock();
            system.transact("Eve", "Alice", 5, 9);
            system.mineBlock();
            system.printBlockchain();
            system.printUsers();

            break;
        }
        case 28: {


            BitcoinSystem system;
            system.addUser("Alice");
            system.addUser("Bob");
            system.addUser("Cindy");
            system.addUser("Desmond");
            system.addUser("Eve");

            system.addBitcoinToUser("Alice", 100);
            system.addBitcoinToUser("Bob", 50);
            system.addBitcoinToUser("Eve", 50);
            system.addBitcoinToUser("Cindy", 30);
            system.addBitcoinToUser("Bob", 20);
            system.addBitcoinToUser("Desmond", 70);
            system.addBitcoinToUser("Desmond", 20);
            system.addBitcoinToUser("Eve", 10);

            system.transact("Alice", "Bob", 40, 1);
            system.transact("Bob", "Eve", 20, 20);
            system.transact("Eve", "Alice", 10, 2);
            system.transact("Desmond", "Cindy", 50, 10);
            system.transact("Cindy", "Alice", 10, 3);
            system.transact("Bob", "Alice", 25, 25);
            system.mineBlock();
            system.transact("Alice", "Bob", 10, 4);
            system.transact("Desmond", "Cindy", 5, 5);
            system.transact("Bob", "Cindy", 5, 6);
            system.transact("Bob", "Cindy", 6, 7);
            system.transact("Bob", "Cindy", 6, 8);
            system.mineBlock();
            system.transact("Eve", "Alice", 5, 9);
            system.mineBlock();
            system.printBlockchain();
            system.printUsers();

            break;
        }
        case 29: {
            BitcoinSystem system;
            system.addUser("Alice");
            system.addUser("Bob");
            system.addUser("Cindy");
            system.addUser("Desmond");
            system.addUser("Eve");

            system.addBitcoinToUser("Alice", 100);
            system.addBitcoinToUser("Bob", 50);
            system.addBitcoinToUser("Eve", 50);
            system.addBitcoinToUser("Cindy", 30);
            system.addBitcoinToUser("Bob", 20);
            system.addBitcoinToUser("Desmond", 70);
            system.addBitcoinToUser("Desmond", 20);
            system.addBitcoinToUser("Eve", 10);
            system.printUsers();

            system.transact("Alice", "Bob", 40, 5);
            system.transact("Bob", "Eve", 20, 20);
            system.transact("Eve", "Alice", 10, 1);
            system.transact("Desmond", "Cindy", 50, 10);
            system.transact("Cindy", "Alice", 10, 2);
            system.transact("Bob", "Alice", 25, 25);
            system.printPendingTransactions();
            system.mineBlock();
            system.transact("Alice", "Bob", 10, 3);
            system.transact("Desmond", "Cindy", 5, 4);
            system.transact("Bob", "Cindy", 5, 6);
            system.mineBlock();
            system.printPendingTransactions();
            system.transact("Bob", "Cindy", 6, 7);
            system.transact("Bob", "Cindy", 6, 8);
            system.mineBlock();
            system.transact("Eve", "Alice", 5, 9);
            system.transact("Cindy", "Bob", 10, 11);
            system.mineBlock();
            system.transact("Cindy", "Bob", 10, 12);
            system.printBlockchain();
            system.printUsers();
            system.printPendingTransactions();
            break;
        }
        case 30: {
            BitcoinSystem system;
            system.addUser("Alice");
            system.addUser("Bob");

            system.addBitcoinToUser("Alice", 100);
            system.addBitcoinToUser("Bob", 50);

            system.transact("Alice", "Bob", 30, 3);
            system.transact("Bob", "Alice", 20, 2);
            system.printUsers();
            system.printPendingTransactions();
            system.mineBlock();
            system.printBlockchain();

            system.transact("Alice", "Bob", 10, 1);
            system.transact("Bob", "Alice", 5, 4);
            system.printUsers();
            system.printPendingTransactions();
            system.mineBlock();
            system.printBlockchain();

            system.transact("Alice", "Bob", 3, 5);
            system.transact("Bob", "Alice", 5, 0);
            system.printUsers();
            system.printPendingTransactions();
            system.mineBlock();
            system.printBlockchain();

            system.transact("Alice", "Bob", 5, 10);
            system.transact("Bob", "Alice", 5, 11);
            system.printUsers();
            system.printPendingTransactions();
            system.mineBlock();
            system.printBlockchain();
            
            break;
        }   
        default:
            cout << "Invalid test case number." << endl;
            break;
    }
    return 0;
}