#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <random>
#include <string>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200;
const int SZ_COLORS = 25;

int select_goat(const list<Goat> &trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string names[], string colors[]);
void display_trip(const list<Goat> &trip);
int main_menu();
void find_goat_by_name(const list<Goat>& goats);
void sort_goats_by_age(list<Goat>& goats);

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    string names[SZ_NAMES];
    string colors[SZ_COLORS];
    
    // Proper file handling for names
    ifstream fin("names.txt");
    if (!fin) {
        cerr << "Error: Cannot open names.txt\n";
        return 1;
    }
    
    int nameCount = 0;
    while (nameCount < SZ_NAMES && fin >> names[nameCount]) {
        nameCount++;
    }
    fin.close();
    
    if (nameCount == 0) {
        cerr << "Error: No names loaded\n";
        return 1;
    }

    ifstream fin1("colors.txt");
    int i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        trip.push_back(Goat(name, age, color));
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 4) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 5:
                find_goat_by_name(trip);
                break;
            case 6:
                sort_goats_by_age(trip);
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    const int MAX_CHOICE = 12;
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[" << MAX_CHOICE << "] Quit\n";
    
    int choice;
    cout << "Choice --> ";
    cin >> choice;
    while (choice < 1 || choice > MAX_CHOICE) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    trip.push_back(Goat(nm, age, cl));
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(const list<Goat> &trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(const list<Goat> &trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

void find_goat_by_name(const list<Goat>& goats) {
    string name;
    cout << "Enter name to find: ";
    cin >> name;
    
    auto it = find_if(goats.begin(), goats.end(), 
        [&name](const Goat& g) { return g.get_name() == name; });
        
    if (it != goats.end()) {
        cout << "Found: " << it->get_name() << " " 
             << it->get_age() << " " << it->get_color() << endl;
    } else {
        cout << "Goat not found.\n";
    }
}

void sort_goats_by_age(list<Goat>& goats) {
    goats.sort([](const Goat& a, const Goat& b) {
        return a.get_age() < b.get_age();
    });
    cout << "Goats sorted by age.\n";
}
