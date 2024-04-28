//
// Created by brind on 15/04/2024.
//

#include "Board.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <sstream>
#include <string.h>

#include "Bug.h"
#include "Hopper.h"
#include "Crawler.h"

using namespace std;

Board::Board(vector<Bug*>& bug_vector) {
    this->grid;
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
                grid[x][y].bugs.push_back(ptr);
                grid[x][y].isEmpty = false;
            }
            else {
                Bug* ptr = new Crawler(id,pair<int,int>(x,y), dir, size);

                bug_vector.push_back(ptr);
                grid[x][y].bugs.push_back(ptr);
                grid[x][y].isEmpty = false;
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
        if(bug->is_alive()) {
            //moving the bug and updating the grid
            auto [oldX, oldY] = bug->get_position(); //https://en.cppreference.com/w/cpp/language/structured_binding
            bug->move();
            auto [newX, newY] = bug->get_position();

            grid[oldX][oldY].bugs.clear();
            grid[oldX][oldY].isEmpty = true;

            grid[newX][newY].bugs.push_back(bug);
            grid[newX][newY].isEmpty = false;

            // eat functionality

            Bug* biggestBug = grid[newX][newY].bugs[0];

            if(grid[newX][newY].bugs.size() > 1) {
                for(int i = 1; i < grid[newX][newY].bugs.size(); i++ ) {
                    if(grid[newX][newY].bugs[i]->get_size() > biggestBug->get_size()) {
                        biggestBug = grid[newX][newY].bugs[i];
                    }
                    else if(grid[newX][newY].bugs[i]->get_size() == biggestBug->get_size()) {
                        unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
                        mt19937 gen(seed);
                        uniform_int_distribution<> dis(1,2);

                        if(dis(gen) == 1) {
                            biggestBug = grid[newX][newY].bugs[i];
                        }

                    }
                }

                for (auto iter = grid[newX][newY].bugs.begin(); iter != grid[newX][newY].bugs.end();) {
                    auto* otherBug = *iter;

                    if (otherBug != biggestBug) {
                        biggestBug->grow(otherBug->get_size());
                        otherBug->passAway();
                        iter = grid[newX][newY].bugs.erase(iter);
                        //"Returns an iterator pointing to the new location of the element that followed the last element erased by the function call.
                        //This returned iterator will be the end of the container if the operation erased the last element in the sequence."
                        //https://www.shiksha.com/online-courses/articles/erasing-elements-from-a-vector-in-c/#:~:text=to%20by%20last.-,Return%20value%3A,last%20element%20in%20the%20sequence.
                    }
                    else {
                        ++iter;
                    }
                }

                int count = 0;
                Bug* potentialWinner = nullptr;

                //Last Bug Standing
                for(int i = 0; i < 10; i++) {
                    for(int j = 0; j < 10; j++) {
                        if(!grid[i][j].isEmpty) {
                            count++;
                            if(count > 1) {
                                break;
                            }
                                potentialWinner = grid[i][j].bugs.front();
                        }
                        if(count > 1) {
                            potentialWinner = nullptr;
                            break;
                        }
                    }
                }

                if(potentialWinner!= nullptr) {
                    cout << "Last Bug Standing: "<< endl;
                    potentialWinner->displayBug();
                }


            }
        }




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

void Board::displayCells() {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            string occupants;

            if(grid[i][j].isEmpty) {
                occupants = "empty";
            }
            else {
                for(auto& bug : grid[i][j].bugs) {
                    occupants += getBugType(bug) + ' '+ to_string(bug->get_id())+ ", ";
                }
            }

            cout<<"(" << i << "," << j << "): "<< occupants << endl;
        }
    }
}









