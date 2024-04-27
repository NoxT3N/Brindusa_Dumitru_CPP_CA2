#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <sstream>
#include <string.h>

#include "Bug.h"
#include "Crawler.h"
#include "Hopper.h"

using namespace std;

void loadBugs(vector<Bug*>&);
void displayBugs(const vector<Bug*>&);

int main() {
    vector<Bug*> bug_vector;
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
                loadBugs(bug_vector);
            break;
            case 2:
                displayBugs(bug_vector);
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            default:
                cout << "Invalid command"<<endl;
            break;

        }
    }while(choice != 8);


    return 0;
}

void loadBugs(vector<Bug*>& bug_vector) {
    ifstream fin("bugs.txt");

    if(fin) {
        std::map<std::string, Bug::direction> dirMap = {{"1", Bug::NORTH}, {"2", Bug::EAST}, {"3", Bug::SOUTH}, {"4", Bug::WEST}};

        string line;

        while(getline(fin,line)) {
            string bugType,strId, strX, strY, strDir, strSize, strHopLength;
            int id, x, y, size, hopLength;

            istringstream iss(line);

            getline(iss, bugType, ';');
            getline(iss, strId, ';');
            getline(iss, strX, ';');
            getline(iss, strY, ';');
            getline(iss, strDir, ';');
            getline(iss, strSize, ';');

            Bug::direction dir = dirMap[strDir];

            if(bugType == "H") {
                getline(iss, strHopLength, ';');
                int hopLength = stoi(strHopLength);

                Bug* ptr = new Hopper(id,pair<int,int>(x,y),dir, size,hopLength);

                bug_vector.push_back(ptr);
            }
            else {
                Bug* ptr = new Crawler(id,pair<int,int>(x,y), dir, size);

                bug_vector.push_back(ptr);
            }
        }
        cout<<"Board initialized"<<endl;
    }
    else {
        cout<<"Error opening file: "<< strerror(errno) <<endl;
    }
}

void displayBugs(const vector<Bug*>& bug_vector) {
    for(const auto& bug : bug_vector) {
        cout << bug->get_id() << " ";

        if(Crawler* crawler = dynamic_cast<Crawler*>(bug)) {
            cout << "Crawler ";
        }
        else {
            cout << "Hopper ";
        }
        cout << bug->printPosition() << " ";
        cout << bug->printDirection() << " ";
        cout << bug->is_alive() << " ";
        cout << bug->get_size() << " "<<endl;

        if(Hopper* hopper = dynamic_cast<Hopper*>(bug)) {
            cout << hopper->get_hop_length();
        }

    }
}


