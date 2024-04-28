//
// Created by brind on 15/04/2024.
//

#include "Board.h"
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string.h>

#include "Bug.h"
#include "Hopper.h"
#include "Crawler.h"

using namespace std;

Board::Board(vector<Bug*>& bug_vector) {
    this->cells;
    this->bug_vector = bug_vector;
}

Board::~Board() {
    for(Bug* bug: bug_vector) {
        delete bug;
    }
}

string Board::posToString(pair<int, int> & position) {
    int x = position.first;
    int y = position.second;

    return "("+std::to_string(x)+", "+std::to_string(y)+")";
}


void Board::initializeBoard(const string& filename) {
    ifstream fin(filename);

    if(fin) {
        map<std::string, Bug::direction> dirMap = {{"1", Bug::NORTH}, {"2", Bug::EAST}, {"3", Bug::SOUTH}, {"4", Bug::WEST}};

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

            try {
                //https://cplusplus.com/reference/string/stoi/
                id = stoi(strId);
                x = stoi(strX);
                y = stoi(strY);
                size = stoi(strSize);
            }catch (invalid_argument &e) {
                cout << "error converting bug data: " << &e << endl;
            }

            if(bugType == "H") {
                getline(iss, strHopLength);
                hopLength = stoi(strHopLength);

                Bug* ptr = new Hopper(id,pair<int,int>(x,y),dir, size,hopLength);

                bug_vector.push_back(ptr);
            }
            else {
                Bug* ptr = new Crawler(id,pair<int,int>(x,y), dir, size);

                bug_vector.push_back(ptr);
            }
        }
        cout<<"Board initialized"<<endl;
        fin.close();
    }
    else {
        cout<<"Error opening file: "<< strerror(errno) <<endl;
    }
}

string Board::getBugType(Bug *&bug) {
    if(auto crawler = dynamic_cast<Crawler*>(bug)) {
        return"Crawler";
    }

    return "Hopper";

}


void Board::displayAllBugs() {

    if(!bug_vector.empty()) {
        printf("%-3s %-8s %-10s %-5s %-10s %-10s %-10s\n","ID","TYPE","LOCATION","SIZE","DIRECTION","HOPLENGTH","STATUS\n");

        for(const auto& bug: bug_vector) {
            bug->displayBug();
        }
    }
    else {
        cout << "There are currently no bugs on board" << endl;
    }
}

void Board::findBug() {
    cout << "Enter bug ID: " << endl;
    int bugID;
    cin >> bugID;

    for(int i = 0; i < bug_vector.size(); i++) {
        auto* bug = bug_vector[i];

        if(bug->get_id()==bugID) {
            printf("%-3s %-8s %-10s %-5s %-10s %-10s %-10s\n","ID","TYPE","LOCATION","SIZE","DIRECTION","HOPLENGTH","STATUS\n");
            bug->displayBug();
            break;
        }
        if(i+1 == bug_vector.size()) {
            cout << "Bug " << bugID << " not found";
        }
    }
}

void Board::tapBoard() {
    cout<<"You tapped the board"<<endl;
    for(auto* bug : bug_vector) {
        bug->move();
    }
}

void Board::displayHistory() {
    for(Bug* bug : bug_vector) {
        string type = getBugType(bug);

        printf("%d\t%s\tPath: ",bug->get_id(),type.c_str());

        cout<< bug->getLifeHistory() << endl;

    }
}

void Board::exit() {
    ofstream fout("bugs_life_history_date_time.out");
    if(fout.good()) {
        for(Bug* bug: bug_vector) {
            string type = getBugType(bug);
            fout << bug->get_id() << " "<< type <<" "<< bug->getLifeHistory() << endl;
        }
        cout << "File has been written"<<endl;
        fout.close();
    }
    else {
        cout << "Unable to open file: " << strerror(errno);
    }
}








