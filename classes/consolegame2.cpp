/*
 * Description: Console game where character is allowed to move around using keyboard input and win by moving onto the '#'
 * Input: keyboard input (wasd for non-curses version, wasd or keyboard keys for curses version)
 * Output: Grid with player, obstacles, and goal that acts as game
 */

#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <string>

using namespace std;

#define curses
#define SAVELASTROUND true // if we want to save the last round set to true so it doesn't get autoerased

int GRIDX;
int GRIDY;

const int X = 0;
const int Y = 1;
const int COORDINATE = 2;
const int PLAYERCNT = 25;
const int INT_TO_UPPER_ALPH = 65;   // num to add to 0 to make it represent 'A'
const bool ALIVE = true;
const bool DEAD = false;
const int ROUNDCOUNT = 100;

// uncomment when obstacles are needed
// const int NUM_OF_OBSTACLES = 20; // declaring number of obstacles

/*
 * class_identifier: abstract class with virtual move functions and methods to set and get speed
 * constructors: none
 * public functions:    virtual void moveUp();
 *                      virtual void moveDown();
 *                      virtual void moveLeft();
 *                      virtual void moveRight();
 *                      void setSpeed()
 *                      int getSpeed() const
 * static members: none
 */

class move {
public:
    virtual void moveUp() = 0;
    virtual void moveDown() = 0;
    virtual void moveLeft() = 0;
    virtual void moveRight() = 0;
    void setSpeed(int newSpeed) {speed = newSpeed;}
    int getSpeed() const {return speed;}
private:
    int speed;
};

/*
 * class_identifier: initializes and allows changes to hp
 * constructors: health_t()
 * public functions:    int gethp() const
 *                      void sethp(int myhp)
 * static members: none
 */

class health_t {
public:
    health_t() {hp = 20;}               // default constructor
    int gethp() const {return hp;}      // getter for hp
    void sethp(int myhp) {hp = myhp;}   // setter for hp
private:
    int hp;
};

/*
 * class_identifier: initializes, prints, randomizes coordinates - both current and old x and y
 * constructors: coord_t()
 *               coord_t(int usrx, int usry)
 * public functions:    int getOldx() const
 *                      int getOldy() const
 *                      void setOldx(int usrOldx)
 *                      void setOldy(int usrOldy)
 *                      void print() const
 *                      void randomize()
 * static members: none
 */

class coord_t {
public:
    coord_t();
    coord_t(int usrx, int usry); // initializes x and oldx to usr x; same w/ y
    int getOldx() const {return oldx;}
    int getOldy() const {return oldy;}
    void setOldx(int usrOldx) {oldx = usrOldx;}
    void setOldy(int usrOldy) {oldy = usrOldy;}
    void print() const;
    void randomize();
public:
    int x;
    int y;
private:
    int oldx;
    int oldy;
};

// default constructor, setting vars to 0
coord_t::coord_t() {
    x = y = oldx = oldy = 0;
}

// constructor setting x and y to usr defined values, assuming they are appropriate
coord_t::coord_t(int usrx, int usry) {
    if (usrx <= GRIDX && usry <= GRIDY) {
        x = usrx;
        oldx = usrx;
        y = usry;
        oldy = usry;
    }
}

void coord_t::print() const {
#ifdef curses
    printw("[%i,%i]\n", x, y);
#else
    cout << "[" << x << "," << y << "]" << endl;
#endif
}

/*
 * function_identifier: assingns x and y to random positons within coord system
 * parameters: none
 * return value: none
 */
void coord_t::randomize() {
    oldx = x;
    oldy = y;
    
    x = rand() % GRIDX;    // mod operator to ensure x and y are within coord system
    y = rand() % GRIDY;
}

/*
 * class_identifier: declares and manipulates status, id, creationtime of all entities
 *                   this class is inherited by others frequently
 * constructors: ent_t()
 * public functions:    int getId() const
 *                      bool getStat() const
 *                      void setId(int usrId)
 *                      void setStat(bool usrStat)
 *                      void entprint()
 *                      void printCreationTime()
 * static members: entCnt
 */

class ent_t {
public:
    ent_t() {createEntity();}
    int getId() const {return id;}
    bool getStat() const {return status;}
    void setId(int usrId) {id = usrId;}
    void setStat(bool usrStat) {status = usrStat;}
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

/*
 * function_identifier: prints entity's infomation in both ncurses and not
 * parameters: none
 * return value: none
 */
void ent_t::entprint() const {
#ifdef curses
    printw("Entity: %i/%i\nStatus: %i\nCreated: ", id, entCnt, status);
    printCreationTime();
#else
    cout << "Entity: " << id << "/" << entCnt << endl << "Status: ";
    if (status == 1) cout << "Alive";
    else if (status == 0) cout << "Dead";
    else cout << "undefined";
    cout << endl << "Created: ";
    printCreationTime();
#endif
}

// prints creation time in both ncurses and not
void ent_t::printCreationTime() const {
#ifdef curses
    printw("%s", ctime(&creationTime));
#else
    cout << ctime(&creationTime);
#endif
}

/*
 * function_identifier: initializes entity values, used for constructor
 * parameters: none
 * return value: none
 */
void ent_t::createEntity() {
    id = ++entCnt;
    entCnt += 1;
    creationTime = time(NULL); // current time
    status = ALIVE;
}

int ent_t::entCnt = 0;

// used in part II
class world_t {
private:
    ent_t *ent;
};

/*
 * class_identifier: sets type for obstacle and prints obstacle info
 * constructors: none
 * public functions:    string getId() const
 *                      void setType(string usrType)
 *                      void printObstacle() const
 * static members: none
 */

class obstacle_t : public ent_t {
public:
    string getId() const {return id;} // id getter
    void setType(string usrType) {id = usrType;} // id setter
    void printObstacle() const;
private:
    string id;
};

/*
 * function_identifier: print obstacle information
 * parameters: none
 * return value: none
 */
void obstacle_t::printObstacle() const {
#ifdef curses
    printw("Obstacle id: %s", id.c_str());
#else
    cout << "Obstacle Id: " << id << endl;
#endif
    entprint();
    pos.print();
}

class trigger_t : public ent_t {
public:
    trigger_t();
    trigger_t(string, char);
    string whatIDo() const {return info;}
    void setWhatIDo(string usrin) {info = usrin;} // info setter
    char getId() const {return id;}
    void setId(char usrid) {id = usrid;}          // id setter
private:
    string info;
    char id;
};

// default constructor, initializing info and id
trigger_t::trigger_t() {
    info = "";
    id = '?';
}

// constructor, initializing info and id to usr vars
trigger_t::trigger_t(string usrInfo, char usrid) {
    info = usrInfo;
    id = usrid;
}

int max(int x, int y, int z, int k) {
    int largest = x;
    if (y > largest) largest = y;
    if (z > largest) largest = z;
    if (k > largest) largest = k;
    return largest;
}

/*
 * class_identifier: creates map and adds entities to it
 * constructors: map_t()
 * public functions:    void initGrid()
 *                      void print() const
 *                      void clearScreen() const
 *                      void addObstacle(coord_t&)
 *                      void addPlayer(coord_t&, int)
 *                      void addTrigger(coord_t& c, char ch)
 *                      void updatePosition(ent_t)
 * static members: none
 */

class map_t {
public:
    map_t(int urows = 50, int ucols = 14);
    void initGrid();  // iniitialize grid to blanks
    void print() const;
    void clearScreen() const;
    void addObstacle(coord_t&);
    void addPlayer(coord_t&, int);
    void addTrigger(coord_t& c, char ch);
    void updatePosition(ent_t);
    // for testing purposes
    int getRows() const {return rows;}
    int getCols() const {return cols;}
    void update();  // updates the map with storm
    void calcDiameter();    // calculates and returns diameter
    int diameter;
private:
    coord_t centerCoord;
    char **grid;
    int rows;
    int cols;
    int dXR;    // x dist to the right of center
    int dXL;    // x dist to the left of center
    int dYU;    // y dist up of center
    int dYB;    // y dist down of center
    
};

// defualt paramater, intiializing the grid
// othe
map_t::map_t(int urows, int ucols) {
    this->rows = urows;
    this->cols = ucols;

    // creating 2d pointer array
    grid = new char*[this->rows];  // creates array of pointers
    for (int i = 0; i < rows; i++) {
        grid[i] = new char[this->cols];
    }

    centerCoord.randomize();       // creates a random center
    printw("Center: "); centerCoord.print();

    dXR = GRIDX - centerCoord.x;
    dXL = centerCoord.x;
    dYU = centerCoord.y;
    dYB = GRIDY - centerCoord.y;
    calcDiameter();
    initGrid();
}

void map_t::calcDiameter() {
    this->diameter = max(dXR, dXL, dYU, dYB);
}

//  adds player to coordinates passed into function
void map_t::addPlayer(coord_t& c, int pid) {
    grid[c.y][c.x] = (char)(pid+INT_TO_UPPER_ALPH);     // casting into a character
}

void map_t::addObstacle(coord_t& c) {
    grid[c.y][c.x] = '@';
}

void map_t::addTrigger(coord_t& c, char chr) {
    grid[c.y][c.x] = chr;
}

/*
 * function_identifier: initialize grid to blanks
 * parameters: none
 * return value: none
 */
void map_t::initGrid() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            grid[i][j] = ' ';
        }
    }
}

void map_t::update() {
    if(dXR == this->diameter) {
        for (int i = 0; i < this->rows; i++) {
            grid[i][centerCoord.x + dXR] = 's';
        }
        // printw("REMOVE RIGHT");
        // printw("remove right: %i", centerCoord.x + dXR);
        dXR -= 1;
    }
    if (dXL == this->diameter) {
        for (int i = 0; i < this->rows; i++) {
            grid[i][centerCoord.x - dXL] = 's';
        }
        // printw("remove left: %i", centerCoord.x - dXL);
        // printw("REMOVE LEFT");
        dXL -= 1;
    }
    if (dYU == this->diameter) {
        for (int i = 0; i < this->cols; i++) {
            grid[centerCoord.y - dYU][i] = 's';
        }
        // printw("remove up: %i", centerCoord.y - dYU);
        // printw("REMOVE UP");
        dYU -= 1;
    }
    if (dYB == this->diameter) {
        for (int i = 0; i < this->cols; i++) {
            grid[centerCoord.y + dYB][i] = 's';
        }
        // printw("remove down: %i", centerCoord.y + dYB);
        // printw("REMOVE DOWN");
        dYB -= 1;
    }
    this->diameter -= 1;
}

/*
 * function_identifier: print map for both ncurses and not ncurses
 * parameters: none
 * return value: none
 */
void map_t::print() const {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
#ifdef curses
            printw("%c", grid[i][j]);
#else
            cout << grid[i][j];
#endif
        }
#ifdef curses
        printw("\n");
#else
        cout << endl;
#endif
    }
}

/*
 * function_identifier: update position of entity by setting old position to ' ', and the new position to 'A'
 * parameters: none
 * return value: none
 */
void map_t::updatePosition(ent_t myEnt) {
    grid[myEnt.pos.getOldy()][myEnt.pos.getOldx()] = ' ';
    grid[myEnt.pos.y][myEnt.pos.x] = 'A'; // supposing only entity whose position can be updated is the player until part II
    myEnt.pos.setOldx(myEnt.pos.x);
    myEnt.pos.setOldy(myEnt.pos.y);
}

/*
 * function_identifier: erases printed array for both ncurses and not
 * parameters: none
 * return value: none
 */
void map_t::clearScreen() const {
#ifdef curses
    clear();
    printw("Victor's Battle Royale!\n");
#else
    for (int i = 0; i < rows + 1; i++){
        cout << "\33[2K\033[A\r";
    }
    cout << flush;
#endif
}


/*
 * class_identifier: creates, sets, and gets variables used by weapon
 * constructors:    weapon_t()
 *                  weapon_t(int, int, int, int, string)
 * public functions:    int getAmmo() const
 *                      int getDmg() const
 *                      string getModel() const
 *                      int getMagCap() const
 *                      int getMagAmmo() const
 *                      void setAmmo(int usrAmmo)
 *                      void setDmg(int usrDmg)
 *                      void setModel(string usrModel)
 *                      void setMagCap(int usrMC)
 *                      void setMagAmmo(int usrMA)
 *                      void reload()
 *                      bool isReloading()
 *                      void print()
 * static members: pCnt
 */

class weapon_t : public ent_t {
public:
    weapon_t();
    weapon_t(int, int, int, int, string);
    int getAmmo() const {return ammo;}
    int getDmg() const {return dmg;}
    string getModel() const {return model;}
    int getMagCap() const {return magcap;}
    int getMagAmmo() const {return magammo;}
    void setAmmo(int usrAmmo) {ammo = usrAmmo;}
    void setDmg(int usrDmg) {dmg = usrDmg;}
    void setModel(string usrModel) {model = usrModel;}
    void setMagCap(int usrMC) {magcap = usrMC;}
    void setMagAmmo(int usrMA) {magammo = usrMA;}
    void reload();
    void reloadClick() {reloading-=1;} // decreasing value of reloading by 1
    bool isReloading() const;
    void print() const;
private:
    int magcap;     // how much ammo the magazine can hold
    int magammo;    // how much ammo is currently in active magazine
    int reloading;  // counter
    int ammo;       // how much ammo is left
    int dmg;        // damage per hit
    string model;   // name/ type of weapon
};

// default constructor
weapon_t::weapon_t() {
    magcap = 10;
    magammo = 10;
    reloading = 0;
    ammo = 20;
    dmg = 5;
    model = "";
}

// constructor with paramaters, setting member vars to usr values
weapon_t::weapon_t(int usrCap, int usrMA, int usrA, int usrDMG, string usrModel) {
    magcap = usrCap;
    magammo = usrMA;
    reloading = 0;
    ammo = usrA;
    dmg = usrDMG;
    model = usrModel;
}

class player_t : public ent_t, public health_t, public move {
public:
    player_t();
    void print();
    void setPid(int usrPid) {pid = usrPid;}
    void setPname(string usrPname) {name = usrPname;}
    int getPid() const {return pid;}
    string getPname() const {return name;}
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void storeLocation();
    void printLocation();
public:
    weapon_t wep;
private:
    static string playerLocation[PLAYERCNT][2]; // array common to all players to store location
    static bool playerStatus[PLAYERCNT];        // 1d array to store player if player is dead or alive
    string name;
    int pid;
    static int pCnt;
};

int player_t::pCnt = 0;

string player_t::playerLocation[PLAYERCNT][2] = {{""}};     //initialize 2d array to 0s
bool player_t::playerStatus[PLAYERCNT] = {ALIVE};           //initialize all players to be alive

// defualt constructor setting pid and name
player_t::player_t() {
    pid = pCnt++;
    string spid = to_string(pid);   // pid as string
    name = "Player " + spid;
}

/*
 * function_identifier: stores player info into 2d array common to all players
 * parameters: none
 * return value: none
 */
void player_t::storeLocation() {
    playerLocation[pid][0] = pid+INT_TO_UPPER_ALPH;                         // storing the character
    playerLocation[pid][1] = to_string(pos.x) + "," + to_string(pos.y);    // storing coords                   
}

void player_t::printLocation() {
    printw("%s | %s\n", (playerLocation[pid][0]).c_str(), (playerLocation[pid][1]).c_str());
}

/*
 * function_identifier: sets player's old position to current pos
 *                      and updated current position as long as it's within boundaries
 * parameters: none
 * return value: none
 */
void player_t::moveUp() {
    pos.setOldx(pos.x);         // copies current position to old so that updatePos() can make it blank
    pos.setOldy(pos.y);
    if (pos.y >= 1) pos.y -= 1; // checks that player doesn't leave boundaries
}

void player_t::moveDown() {
    pos.setOldx(pos.x);
    pos.setOldy(pos.y);
    if (pos.y < 13) pos.y += 1;
}

void player_t::moveRight() {
    pos.setOldx(pos.x);
    pos.setOldy(pos.y);
    if (pos.x < 49) pos.x += 1;
}

void player_t::moveLeft() {
    pos.setOldx(pos.x);
    pos.setOldy(pos.y);
    if (pos.x >= 1) pos.x -= 1;
}

/*
 * function_identifier: updates + formats player id and name in case it was
 *                      changed by a setter and prints player info
 * parameters: none
 * return value: none
 */
void player_t::print() {
    string spid = to_string(pid);   // in case pid changes after obj is created
    name = "Player " + spid;        // reflect changes to name
#ifdef curses
    printw("%s\n", name.c_str());
    entprint();
    printw("Player position: ");
    pos.print();
#else
    cout << name << endl;           // prints player name + id
    entprint();                     // prints metadata
    cout << "Player position: "; pos.print(); // prints position
#endif
    
}

/*
 * function_identifier: calcs ammo needed to reload, performs reload if enough by adding/subtracting
 *                      from necessary vars. Decrements reloading 5 times to simulate time
 * parameters: none
 * return value: none
 */
void weapon_t::reload() {
    int needed = magcap - magammo;  // amount of ammo needed from total ammo
    if ((ammo - needed) >= 0) {     // ensuring there's enough ammo
        reloading = 5;
        ammo -= needed;             // subtract from total
        magammo += needed;          // add to gun ammo
        for (int j = reloading; j > 0; j--) {   // loops 5 times, calling reloadclick() which decrements relaod
#ifdef curses
            printw("%i", reloading);            // printing info to show function works, will remove later
#else
            cout << reloading;
#endif
            reloadClick();
        }
    }
    // in Part II of assingment
}

// checks if weapon is reloading by tapping into reloading member var
bool weapon_t::isReloading() const {
    if (reloading > 0) return true;
    else return false;
}

/*
 * function_identifier: prints out weapon info in both curses and non-curses mode
 * parameters: map obj, player obj, direction (which key is pressed)
 * return value: none
 */
void weapon_t::print() const {
#ifdef curses
    printw("\nWeapon Information: \nmodel: %s\nmagcap: %i\nmagammo: %i\nreloading: %i\nammo: %i\ndmg: %i\n", model.c_str(), magcap, magammo, reloading, ammo, dmg);
#else
    cout << "Weapon Information: " << endl << "model: " << model << endl <<
    "magcap: " << magcap << endl << "magammo: " << magammo << endl <<
    "reloading: " << reloading << endl << "ammo: " << ammo << endl << "dmg: " << dmg << endl;
#endif
}

/*
 * function_identifier: moves player on map, depending on key user has pressed
 * parameters: map obj, player obj, direction (which key is pressed)
 * return value: none
 */
void makemove(map_t &map, player_t &p, int direction) {
#ifdef curses
    if (direction == KEY_UP || direction == 119) {      // checking up or W
        p.moveUp();                                     // change player's position
        map.updatePosition(p);                          // and immediately after, update map with that new position
    } else if (direction == KEY_DOWN || direction == 115) {
        p.moveDown();
        map.updatePosition(p);
    } else if (direction == KEY_RIGHT || direction == 100) {
        p.moveRight();
        map.updatePosition(p);
    } else if (direction == KEY_LEFT || direction == 97) {
        p.moveLeft();
        map.updatePosition(p);
    }
#else
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
#endif
}

// ends curses lib and interface
void endCurses() {
#ifdef curses
    refresh();
    getch();    // asks for one final character
    endwin();   // closes ncurses lib
#endif
}

// initializes curses lib and prints out initial statements/instructions
void initCurses() {
#ifdef curses
    initscr();
    keypad(stdscr, TRUE); // accepts arrow keys
    noecho();
    raw(); //prevents exiting with commands
    printw("Victor's Battle Royale!\n");
#endif
}

/*
 * function_identifier: checks when player steps on trigger
 * parameters: player obj, trigger obj
 * return value: true if player is on object, false otherwise
 */

bool winRnd(player_t p, trigger_t t) {
    // looking to see if player steps on trigger
    if ((p.pos.x == t.pos.x) && (p.pos.y == t.pos.y)) return true;
    else return false;
}

/*
 * function_identifier: "client code" where objects are created and added to the game
 *                       there is also a section to test methods of all the classes
 * parameters: none
 * return value: 0
 */

int main(int argc, char* argv[]) {
    initCurses();
    int round = 0;

    if (argc != 3) {
        printw("ERROR: You must enter 2 arguments");
        endCurses();
        return -1;
    }

    GRIDX = atoi(argv[1]);
    GRIDY = atoi(argv[2]);
    srand(time(NULL)); // creates random seed rand() function

    map_t map(GRIDY, GRIDX);        // map automatically generates a random center within its constructor
    
    printw("Number of rows: %i\n", map.getRows());
    printw("Number of cols: %i\n", map.getCols());

    // create objects
    player_t p[PLAYERCNT];                 // 25 player objects
    for (int i = 0; i < PLAYERCNT; i++) {
        p[i].pos.randomize();              // sets player to random position
        map.addPlayer(p[i].pos, i);        // adds player to map
        p[i].storeLocation();
    }
    char input = ' ';
    map.print();                    // prints initial map
    while (round < ROUNDCOUNT && input != 'q') {
        input = getch();
        if (input == '\n') {
            map.update();
            printw("\n");
            map.clearScreen();
            map.print();
        } else {
            printw("Error! Only Press Enter.");
        }
        round++;
    }
    

    printw("Diamater of map: %i", map.diameter);
    

    
    // ----------- DEMO of functions in other classes ---------------
    // show that print location works

    // for (int i = 0; i< PLAYERCNT; i++) {
    //     p[i].printLocation();
    // }

    endCurses();
    return 0;
}

