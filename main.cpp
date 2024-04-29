#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <sstream>
#include <string.h>

#include "Board.h"
#include "Bug.h"
#include "Crawler.h"
#include "Hopper.h"

using namespace std;

void loadBugs(vector<Bug*>&);
void displayBugs(const vector<Bug*>&);
void findBug(const vector<Bug*>&);

int main() {
    vector<Bug*> bug_vector;
    Board board(bug_vector);
    int choice;

    cout<<"Welcome to A Bug's Life"<<endl;

    do {
        cout<<"\nPlease select a command:\n"<<endl;

        cout<<"1.Initialize Bug Board (load data from file)"<<endl;
        cout<<"2.Display all Bugs"<<endl;
        cout<<"3.Find a Bug (given an id)"<<endl;
        cout<<"4.Tap the Bug Board (causes move all, then fight/eat)"<<endl;
        cout<<"5.Display Life History of all Bugs (path taken)"<<endl;
        cout<<"6.Display all Cells listing their Bugs"<<endl;
        cout<<"7.Run simulation (generates a Tap every second)"<<endl;
        cout<<"8.Exit (write Life History of all Bugs to file)"<<endl;

        cin >> choice;

        switch (choice) {
            case 1:
                //loadBugs(bug_vector);
                board.initializeBoard("bugs.txt");
            break;
            case 2:
                //displayBugs(bug_vector);
                board.displayAllBugs();
                break;
            case 3:
                board.findBug();
                break;
            case 4:
                board.tapBoard();
                break;
            case 5:
                board.displayHistory();
                break;
            case 6:
                board.displayCells();
                break;
            case 7:
                board.runSimulation();
                break;
            case 8:
                board.exit();
                break;
            default:
                cout << "Invalid command"<<endl;
            break;

        }
    }while(choice != 8);


    return 0;
}


