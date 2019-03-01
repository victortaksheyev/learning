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
#define GRIDX 50
#define GRIDY 14
#define ROUNDCNT 100
#define ALIVE true // Nickname for true
#define DEAD false // and false
#define SAVELASTROUND true // if we want to save the last round set to true so it doesn't get autoerased

const int X = 0;
const int Y = 1;
const int COORDINATE = 2;

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
    
    x = rand() % 50;    // mod operator to ensure x and y are within coord system
    y = rand() % 14;
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
    map_t();
    void initGrid();  // iniitialize grid to blanks
    void print() const;
    void clearScreen() const;
    void addObstacle(coord_t&);
    void addPlayer(coord_t&, int);
    void addTrigger(coord_t& c, char ch);
    void updatePosition(ent_t);
private:
    char grid[GRIDY][GRIDX];
};

// defualt paramater, intiializing the grid
map_t::map_t() {
    initGrid();
}

//  adds player to coordinates passed into function
void map_t::addPlayer(coord_t& c, int pid) {
    grid[c.y][c.x] = 'A';
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
    for (int i = 0; i < GRIDY; i++) {
        for (int j = 0; j < GRIDX; j++) {
            grid[i][j] = ' ';
        }
    }
}

/*
 * function_identifier: print map for both ncurses and not ncurses
 * parameters: none
 * return value: none
 */
void map_t::print() const {
    for (int i = 0; i < GRIDY; i++) {
        for (int j = 0; j < GRIDX; j++) {
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
    printw("Welcome! Use arrow keys or WASD to move. Get to the # to win, press 'q' to quit\n");
#else
    for (int i = 0; i < GRIDY + 1; i++){
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
public:
    weapon_t wep;
private:
    string name;
    int pid;
    static int pCnt;
};

int player_t::pCnt = 0;

// defualt constructor setting pid and name
player_t::player_t() {
    pid = pCnt++;
    string spid = to_string(pid); // pid as string
    name = "Player " + spid;
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

// initializes curses lib and prints out initial statements/instructions
void initCurses() {
#ifdef curses
    initscr();
    keypad(stdscr, TRUE); // accepts arrow keys
    noecho();
    raw(); //prevents exiting with commands
    printw("Welcome! Use arrow keys or WASD to move. Get to the # to win, press 'q' to quit\n");
#else
    cout << "Welcome! Use WASD to move. Get to the # to win, press 'q' to quit" << endl;
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

int main() {
    srand(time(NULL)); // creates random seed rand() function
    const int NUM_OF_OBSTACLES = 100; // declaring number of obstacles
    
    // create objects
    player_t p;
    map_t map;
    coord_t c;
    trigger_t exit;
    obstacle_t obs[NUM_OF_OBSTACLES];
    
    initCurses();
    
    for (int i = 0; i < NUM_OF_OBSTACLES; i++) {    // spawns 200 random objects
        obs[i].pos.randomize();
        map.addObstacle(obs[i].pos);
    }
    
    p.pos.randomize();              // sets player to random position
    map.addPlayer(p.pos, 1);        // adds player to map
    
    exit.pos.randomize();           // randomizes exit pos
    map.addTrigger(exit.pos, '#');  // defines exit as '#' and adds to map

#ifdef curses
    int input = 0;
#else
    char input = '0';               // stores arrow keys
#endif
    
    map.print();                    // prints initial map
    
    // game loop until player reaches exit trigger or presses q
    while(!(winRnd(p, exit)) && (input != 'q')) {
#ifdef curses
        input = getch();
#else
        cin.clear();
        cin >> input;
        cin.ignore(100, '\n');      // prevent cin from rereading in case user entered more than 1 char
#endif
        makemove(map, p, input);    // updates map and player obj based on usr input
        map.clearScreen();          // resets to show updated screen
        map.print();
    }

    map.clearScreen();              // clears screen post-victory
#ifdef curses
    printw("Congrats! You won (or quit)! \nBelow is a demo of the methods in my classes:\n");
#else
    cout << "Congrats! You won (or quit)! \nBelow is a demo of the methods in my classes:" << endl;
#endif

    
    // ----------- DEMO of functions in other classes -------------
    
    // coord_t class ----------------------------------------------
#ifdef curses
    printw("\ncoord_t class --------\n");
#else
    cout <<"\ncoord_t class --------" << endl;
#endif
    
    coord_t defaultCoord;
    defaultCoord.print();           // should print [0, 0]
    coord_t paramCoord(5, 10);
    paramCoord.print();             // should print [5, 10]
    paramCoord.setOldx(200);
#ifdef curses
    printw("old x: %i\n", paramCoord.getOldx()); // should print "old x: 200"
#else
    cout << "old x: " << paramCoord.getOldx() << endl;
#endif

    // ent_t class -------------------------------------------------
#ifdef curses
    printw("\nent_t class --------\n");
#else
    cout << "\nent_t class --------" << endl;
#endif
    
    ent_t testEnt;
    testEnt.setId(123);
#ifdef curses
    printw("id: %i\n", testEnt.getId()); // should print "id: 100"
#else
    cout << "id: " << testEnt.getId() << endl;
#endif
    testEnt.entprint();
    
    // health_t class  ---------------------------------------------
#ifdef curses
    printw("\nhealth_t class --------\n");
#else
    cout << "\nhealth_t class --------" << endl;
#endif
    
    health_t testh;
    testh.sethp(100);
#ifdef curses
    printw("health: %i\n", testh.gethp()); // should print "health: 100"
#else
    cout << "health: " << testh.gethp() << endl;
#endif
    
    // weapon_t class ----------------------------------------------
#ifdef curses
    printw("\nweapon_t class --------");
#else
    cout << "\nweapon_t class --------" << endl;
#endif
    
    weapon_t revolver;              // creating an object w/ default parameter
    
    revolver.print();               // should print default params:
    
    revolver.setDmg(1000);
    revolver.setMagAmmo(20);
    revolver.setModel("best pistol");
    revolver.print();               // changes should reflect
    revolver.reload();              // should print out 54321 to show it takes 5 seconds to reload
    

    // player_t class ----------------------------------------------
#ifdef curses
    printw("\n\nplayer_t class --------\n");
#else
    cout << "\n\nplayer_t class --------" << endl;
#endif
    
    player_t testPlayer;
    testPlayer.setPid(9);           // pid should be 9
    testPlayer.print();
    
    // trigger_t() class -------------------------------------------
#ifdef curses
    printw("\ntrigger class --------\n");
#else
    cout << "\ntrigger class -------" << endl;
#endif
    
    trigger_t testTrig;
    testTrig.setWhatIDo("win the game");
#ifdef curses
    printw("What I do: %s", testTrig.whatIDo().c_str());    // should print out "win the game"
#else
    cout << "What I do: " << testTrig.whatIDo() << endl;
#endif

     // obstacle_t() class -------------------------------------------
#ifdef curses
    printw("\n\nobstacle_t class --------\n");
#else
    cout << "\nobstacle_t class --------" << endl;
#endif
    obs[10].printObstacle();
    
#ifdef curses
    printw("\n\nPress Any Key to Exit\n");
#endif

    // ----------- DEMO of functions in other classes ---------------
    endCurses();
    return 0;
}
