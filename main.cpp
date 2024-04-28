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

// void loadBugs(vector<Bug*>& bug_vector) {
//     ifstream fin("bugs.txt");
//
//     if(fin) {
//         std::map<std::string, Bug::direction> dirMap = {{"1", Bug::NORTH}, {"2", Bug::EAST}, {"3", Bug::SOUTH}, {"4", Bug::WEST}};
//
//         string line;
//
//         while(getline(fin,line)) {
//             string bugType,strId, strX, strY, strDir, strSize, strHopLength;
//             int id, x, y, size, hopLength;
//
//             istringstream iss(line);
//
//             getline(iss, bugType, ';');
//             getline(iss, strId, ';');
//             getline(iss, strX, ';');
//             getline(iss, strY, ';');
//             getline(iss, strDir, ';');
//             getline(iss, strSize, ';');
//
//             Bug::direction dir = dirMap[strDir];
//
//             try {
//                 //https://cplusplus.com/reference/string/stoi/
//                 id = stoi(strId);
//                 x = stoi(strX);
//                 y = stoi(strY);
//                 size = stoi(strSize);
//             }catch (invalid_argument &e) {
//                 cout << "error converting bug data: " << &e << endl;
//             }
//
//             if(bugType == "H") {
//                 getline(iss, strHopLength);
//                 hopLength = stoi(strHopLength);
//
//                 Bug* ptr = new Hopper(id,pair<int,int>(x,y),dir, size,hopLength);
//
//                 bug_vector.push_back(ptr);
//             }
//             else {
//                 Bug* ptr = new Crawler(id,pair<int,int>(x,y), dir, size);
//
//                 bug_vector.push_back(ptr);
//             }
//         }
//         cout<<"Board initialized"<<endl;
//         fin.close();
//     }
//     else {
//         cout<<"Error opening file: "<< strerror(errno) <<endl;
//     }
// }
//
// void displayBugs(const vector<Bug*>& bug_vector) {
//
//     if(!bug_vector.empty()) {
//         printf("%-3s %-8s %-10s %-5s %-10s %-10s %-10s\n","ID","TYPE","LOCATION","SIZE","DIRECTION","HOPLENGTH","STATUS\n");
//
//         for(const auto& bug: bug_vector) {
//             if(auto* hopper = dynamic_cast<Hopper*>(bug)) {
//                 printf("%-4d %-8s %-10s %-5d %-10s %-5d %9s\n",hopper->get_id(),"Hopper",hopper->get_string_position().c_str(),hopper->get_size(),hopper->get_string_direction().c_str(),hopper->get_hop_length(),hopper->get_string_status().c_str());
//             }
//             else {
//                 printf("%-4d %-8s %-10s %-5d %-10s %15s\n",bug->get_id(),"Crawler",bug->get_string_position().c_str(),bug->get_size(),bug->get_string_direction().c_str(),bug->get_string_status().c_str());
//             }
//         }
//     }
//     else {
//         cout << "There are currently no bugs on board" << endl;
//     }
// }

// void findBug(const vector<Bug*>& bug_vector) {
//     cout << "Enter bug ID: " << endl;
//     int bugID;
//     cin >> bugID;
//
//     for(int i = 0; i < bug_vector.size(); i++) {
//         auto* bug = bug_vector[i];
//
//         if(bug->get_id()==bugID) {
//             printf("%-3s %-8s %-10s %-5s %-10s %-10s %-10s\n","ID","TYPE","LOCATION","SIZE","DIRECTION","HOPLENGTH","STATUS\n");
//             if(auto* hopper = dynamic_cast<Hopper*>(bug)) {
//                 printf("%-4d %-8s %-10s %-5d %-10s %-5d %9s\n",hopper->get_id(),"Hopper",hopper->get_string_position().c_str(),hopper->get_size(),hopper->get_string_direction().c_str(),hopper->get_hop_length(),hopper->get_string_status().c_str());
//             }
//             else {
//                 printf("%-4d %-8s %-10s %-5d %-10s %15s\n",bug->get_id(),"Crawler",bug->get_string_position().c_str(),bug->get_size(),bug->get_string_direction().c_str(),bug->get_string_status().c_str());
//             }
//             break;
//         }
//         if(i+1 == bug_vector.size()) {
//             cout << "Bug " << bugID << " not found";
//         }
//     }
//
// }


