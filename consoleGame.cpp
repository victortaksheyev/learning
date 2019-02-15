#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <string>

using namespace std;

//#define curses
#define GRIDX 50
#define GRIDY 14
#define ROUNDCNT 100
#define ALIVE true // Nickname for true
#define DEAD false // and false
#define SAVELASTROUND true // if we wnat to save the last round set to true so it doesn't get autoerased

const int X = 0;
const int Y = 1;
const int COORDINATE = 2;

class map_t {
public:
    map_t();
    void initGrid();  // iniitialize grid to blanks
    void print() const;
    void clearScreen() const;
    
private:
    char grid[GRIDY][GRIDX];
};

map_t::map_t() {
    initGrid();
}

void map_t::initGrid() {
    for (int i = 0; i < GRIDY; i++) {
        for (int j = 0; j < GRIDX; j++) {
            grid[i][j] = 'X';
        }
    }
}

void map_t::print() const {
    for (int i = 0; i < GRIDY; i++) {
        for (int j = 0; j < GRIDX; j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
}

// erase printed array
void map_t::clearScreen() const {

#ifdef curses
    clear();
#else
    for (int i = 0; i<GRIDY+1; i++){
        cout << "\33[2K\033[A\r";
    }
    cout << flush;
#endif
}


int main () {
    map_t mainmap;
    mainmap.print();
    mainmap.clearScreen();
    return 0;
}
