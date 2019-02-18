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



class move {
public:
    virtual void moveUp() = 0;
    virtual void moveDown() = 0;
    virtual void moveLeft() = 0;
    virtual void moveRight() = 0;
    void setSpeed(int);
    int getSpeed() const;
private:
    int speed;
};

void move::setSpeed(int newSpeed) {
    speed = newSpeed;
}

int move::getSpeed() const {
    return speed;
}

class health_t {
public:
    health_t();
    int gethp() const;
    void sethp(int);
private:
    int hp;
};

health_t::health_t() {
    hp = 20;
}

int health_t::gethp() const{
    return hp;
}

void health_t::sethp(int myhp) {
    hp = myhp;
}

class coord_t {
public:
    coord_t();
    coord_t(int usrx, int usry); // initializes x and oldx to usr x; same w/ y
    int getOldx() const;
    int getOldy() const;
    void setOldx(int);
    void setOldy(int);
    void print() const;
    void randomize();
public:
    int x;
    int y;
private:
    int oldx;
    int oldy;
};

coord_t::coord_t() {
    x = y = oldx = oldy = 0;
}

coord_t::coord_t(int usrx, int usry) {
    x = usrx;
    oldx = usrx;
    y = usry;
    oldy = usry;
}

int coord_t::getOldx() const {
    return oldx;
}

int coord_t::getOldy() const {
    return oldy;
}

void coord_t::setOldx(int usrx) {
    oldx = usrx;
}

void coord_t::setOldy(int usry) {
    oldy = usry;
}

void coord_t::print() const {
    cout << "[" << x << "," << y << "]";
}

void coord_t::randomize() {
    oldx = x;
    oldy = y;
    x = rand() % 50;
    y = rand() % 14;
}

class ent_t {
public:
    ent_t();
    int getId() const;
    bool getStat() const;
    void setId(int);
    void setStat(bool);
    void entprint() const;
    void printCreationTime() const;
    coord_t pos;
private:
    void createEntity();
private:
    int id;
    time_t creationTime;
    bool status;
    static int entCnt;
};

ent_t::ent_t() {
    createEntity();
}

int ent_t::getId() const {
    return id;
}

bool ent_t::getStat() const {
    return status;
}

void ent_t::setId(int usrId) {
    id = usrId;
}

void ent_t::setStat(bool usrStat) {
    status = usrStat;
}

void ent_t::entprint() const {
    cout << "Entity: " << id << "/" << entCnt << endl << "Status: ";
    if (status == 1) cout << "Alive";
    else if (status == 0) cout << "Dead";
    else cout << "undefined";
    cout << endl << "Created: ";
    printCreationTime();
}

void ent_t::printCreationTime() const {
    cout << ctime(&creationTime);
}

void ent_t::createEntity() {
    id = 0; // check if to keep
    entCnt += 1;
    creationTime = time(NULL);
    status = ALIVE;
}

int ent_t::entCnt = 0;

class world_t {
private:
    ent_t *ent;
};

class obstacle_t : public ent_t {
public:
    string getId() const;
    void setType(string);
    void printObstacle() const;
private:
    string id;
};

string obstacle_t::getId() const {
    return id;
}

void obstacle_t::setType(string usrType) {
    id = usrType;
}

void obstacle_t::printObstacle() const {
    //    coord_t obstacleCoord; // composition
    //    cout << "Obstacle Id: " << id << endl;
    //    entprint();
    //    cout << ""obstacleCoord.print();
}

class map_t {
public:
    map_t();
    void initGrid();  // iniitialize grid to blanks
    void print() const;
    void clearScreen() const;
    void addObstacle(coord_t);
    void addPlayer(coord_t, int);
    int obstaclenum();
    void updatePosition(ent_t);
private:
    char grid[GRIDY][GRIDX];
};

map_t::map_t() {
    initGrid();
}

// adds instance initially
void map_t::addPlayer(coord_t c, int pid) {
    c.randomize();
    grid[c.y][c.x] = '1';
}

void map_t::addObstacle(coord_t c) {
    c.randomize();
    grid[c.y][c.x] = '@';
}

void map_t::initGrid() {
    for (int i = 0; i < GRIDY; i++) {
        for (int j = 0; j < GRIDX; j++) {
            grid[i][j] = 'X';
        }
    }
}

// print out the map
void map_t::print() const {
    for (int i = 0; i < GRIDY; i++) {
        for (int j = 0; j < GRIDX; j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
}

void map_t::updatePosition(ent_t myEnt) {
    grid[myEnt.pos.getOldy()][myEnt.pos.getOldx()] = ' ';
    grid[myEnt.pos.y][myEnt.pos.x] = 'A';
    myEnt.pos.setOldx(myEnt.pos.x);
    myEnt.pos.setOldy(myEnt.pos.y);
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

int map_t::obstaclenum() {
    int count = 0;
    for (int i = 0; i < GRIDY; i++) {
        for (int j = 0; j < GRIDX; j++) {
            if (grid[i][j] == '@') {
                count += 1;
            }
        }
    }
    return count;
}

class player_t : public ent_t, public health_t, public move {
public:
    player_t();
    int getPid() const;
    string getPname() const;
    void setPid();
    void setPname();
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void print() const;
public:
    //    weapon_t weapon;
private:
    string name;
    int pid;
    static int pCnt;
};

int player_t::pCnt = 0;

player_t::player_t() {
    pid = pCnt++;
    string spid = to_string(pid); // pid as string
    name = "Player " + spid;
}

void player_t::moveUp() {
    pos.setOldx(pos.x);
    pos.setOldy(pos.y);
    if (pos.y >= 1) pos.y -= 1; // checks that player doesn't move out of map
}

void player_t::moveDown() {
    pos.setOldx(pos.x);
    pos.setOldy(pos.y);
    if (pos.y < 13) pos.y += 1; // ensures player doesn't leave boundaries
}

void player_t::moveRight() {
    pos.setOldx(pos.x);
    pos.setOldy(pos.y);
    if (pos.x <= 49) pos.x += 1;
}

void player_t::moveLeft() {
    pos.setOldx(pos.x);
    pos.setOldy(pos.y);
    if (pos.x >= 1) pos.x -= 1;
}

void player_t::print() const {
    cout << name << endl; // prints player name + id
    entprint(); // prints metadata
    cout << "Player position: "; pos.print(); // prints position
}

void makemove(map_t &map, player_t &p, char direction) {
    if (direction == 'w') {
        p.moveUp();
        map.updatePosition(p);
    } else if (direction == 's') {
        p.moveDown();
        map.updatePosition(p);
    } else if (direction == 'd') {
        p.moveRight();
        map.updatePosition(p);
    } else if (direction == 'a') {
        p.moveLeft();
        map.updatePosition(p);
    }
}

int main () {
    player_t p;
    map_t map;
    char c = '\0';
    while (p.pos.x != 50) {
        
        cout  << "enter a direction to move";
        cin >> c;
        
        map.clearScreen();
        makemove(map, p, c);
        map.print();
    }
    
    
    
    
    //    syntax for adding things
    //    while (mymap.obstaclenum() < 700) {
    //        mymap.addObstacle(newcoord);
    //    }
    
    return 0;
}

// expected output:
// [5, 10]
// [rand, rand]
