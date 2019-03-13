#include<iostream> //cout
#include<stdlib.h> //Malloc/Free
#include<stdio.h>  //printf
#include<string>   //Strings
#include<cstring>   //strcpy

using namespace std;

//Create a class called animal_t with two pointers, name and age (string and int pointers). All members of the class are public.
//Create constructor that allocates memory to name and age and then initializes them to "Default" and 0. Use the new keyword
//Create accessors and mutators for both member variables [ int setAge() , void getAge(int a)  etc... ]
//Create a print function that prints: "Animal> Name: X, Age: Y\n" replace X and Y with name and age variables. ie: "Animal> Name: Default, Age 0"
//Create a Destructor that uses delete and sets age and name pointers to null.
class animal_t {
public:
    int getAge() const {return *age;}
    string getName() const {return *name;}
    void setAge(int uage) {*age = uage;}
    void setName(string uname) {*name = uname;}
    animal_t();
    string *name;
    int *age;
    void print() const;
    ~animal_t();
};

animal_t::animal_t() {
    name = new string("Default");       // equiv to *name = "Default" plus storing address into name;
    age = new int(0);                   // equiv to *age = 0 plus storing address into age;
}

void animal_t::print() const {
    printf("Animal> Name: %s, Age: %i\n", (*name).c_str(), *age);
}

// de-allocating any class member variables and setting them to NULL so they're not dangling
animal_t::~animal_t() {
    delete age;
    delete name;
    age = NULL;
    name = NULL;
}

//Create a class dog_t that publicly inherits animal_t
//Create a public char pointer called breed
//Create getBreed()accessor that returns a char pointer to breed.
//Create a mutator setBreed() that takes a string and converts it to char array and stores it in breed. X
//To do this,  you will need to delete the old breed using free and then allocate a new breed char array.
//Use str.length() to find length needed to allocate it. use strcpy(thestring, breed) to copy the string into the char array.
//This breed pointer will be an array of characters (null terminated) to store the name of the breed.

//Creater 2 constructors. A default constructor that dynamically allocates the breed array with a size of 8 and initalize it with "Unknown"
//After the 2nd n in Unknown. add a null character '\0' That's what we mean with null terminated.
//The second constructor should expect two parameters. the size to dynamically allocate our char array first,
//then the actual breed name to store in the array, passed as a char array. Make sure to make a deep copy.

//For this class you are not allowed to use NEW and DELETE, you must use malloc and free.
//Create a destructor that will free the memory and set pointer to null for breed.
//redefine the print function but this time have it print Dog> infront of the name and age. Also print the Breed after the age:
//For example:  Dog> Name: Default, Age: 0, Breed: Unknown
class dog_t : public animal_t{
public:
    char *breed;
    char getBreed() const {return *breed;}
    void setBreed(string);
    dog_t();
    dog_t(int, char[]);
    ~dog_t();
    void print();
};

void dog_t::setBreed(string ubreed) {
    free(breed);                                                    // deallocated memory from old breed
    breed = (char*)malloc((ubreed.length()+1) * sizeof(char));      // allocating array of chars based on length of passed string
                                                                    // using length+1 to account for null character
    strcpy(breed, ubreed.c_str());
}

dog_t::dog_t() {
    breed = (char*)malloc(8 * sizeof(char));                    // allocates char array and stores address into breed pointer var
                                                                // allocating 8 spaces to account for \0 char
    strcpy(breed, "Unknown\0");                                 // initilizes with default
}

dog_t::dog_t(int size, char breedName[]) {
    breed = (char*)malloc(size * sizeof(char));
    for (int i = 0; i < size+1; i++)
        breed[i] = breedName[i];                                // creating deep copy by copying each item individually
}

void dog_t::print() {
    printf("Dog> Name: %s, Age: %i, Breed: %s\n", (*name).c_str(), *age, breed);
}

dog_t::~dog_t() {
    free(breed);
}

class bird_t : public animal_t{ //bird_t that publicly inherits animal_t, don't edit me.
    static int id;
public:
    void print(){cout << "Bird>" << ++id << endl;}
}; int bird_t::id = 0;

//Create a struct called house_t that has 1 dogs and 1 birds pointer
struct house_t{
    string name; //Don't touch this.
    //Your Code Here
    dog_t *dogs;
    bird_t *birds;
};

// Client/Driver Code
int main(){
    int x = 5;
    int y = 10; //will be used for bird array
    string str = "Cavalier Spaniel"; //will be used later
    
    //Your Code Here
    
    //Create a pointer called Name of type string
    string *name;
    
    //dynamically allocate it;
    name = new string;
    
    //Store "Padme" in your new string
    *name = "Padme";
    
    //create an integer pointer ptr;
    int *ptr;
    
    //Make it point to x;
    ptr = &x;
    
    //Store the value of 2 into ptr (should indirectly change x)
    *ptr = 2;
    
    cout << "ptr Address: ";
    //cout the address of ptr
    cout << &ptr;
    
    cout << " : ";
    //cout the value ptr points to. Then cout and endline.
    cout << *ptr << endl;
    
    //Create an integer pointer mptr;
    int *mptr;
    
    //Dynamically allocate it using malloc.
    mptr = (int*)malloc(sizeof(int));
    
    //Copy the value of what ptr is pointing to there (so basically copy the value stored in x, but without using the x variable in code
    *mptr = *ptr;
    
    //Use printf to output the following statement:   "MPTR, Address: $, : Value $\n"  Replace dollar signs with approrpriate syntax
    //to print address and value mptr points to.
    printf("MPIR, Address: %p, Value %i\n", &mptr, *mptr);
    
    //Create an pointer of animal_t type called animal1
    animal_t *animal1;
    
    //dynamically allocate animal1 using new
    animal1 = new animal_t;
    //call animal1.print() . Do not use arrow operator do it using parenthesis and dereference operator. Should print: Animal> Name: Default, Age: 0
    (*animal1).print();
    
    //Create an object of dog_t type called dog1
    dog_t dog1;
    
    //Set the age of dog1 to 2 (get it from mptr)
    dog1.setAge(*mptr);
    
    //Set the name of dog1 to your string Name that has Padme stored in it.)
    dog1.setName(*name);
    
    //call dog1.print(), should print out: Dog> Name: Padme, Age: 2, Breed: Unknown
    dog1.print();
    
    //Set the pointer of animal1 to point to the address of dog1.
    animal1 = &dog1;
    
    //Call animal1.print() This time use arrow operator (makes no difference which you use but wanted you to try both ways)
    animal1->print();
    
    //Let's set the Breed of Dog1 to string str which has "Cavalier Spaniel".
    //To do it call setBreed to the dog1 object
    dog1.setBreed(str);
    
    //Notice that if you tried to do it to the animal1 object you would get an error.
    //animal1->setBreed(str); //Try it by uncommenting this then comment it again after you see the error
    
    //Call animal1.print() (if you accidentally use member access instead of arrow, you will see a nice error try it, see it, then do it the right way.
    animal1->print();
    
    //Call dog1.print();
    dog1.print();
    
    //Create a bird_t pointer called birds
    bird_t *birds;
    
    //Dynamically allocate an array of size y (see top of main)
    birds = new bird_t[y];
    
    //create a new house_t pointer called house, then dynamically allocate it using malloc; (2lines)
    house_t *house;
    house = (house_t*)malloc(sizeof(house_t));
    
    //Lets place Padme into the house struct (1 line of code so don't do anything weird)
    house->dogs = &dog1;
 
    //lets place all our 10 birds into the house (1 line of code so don't do anything weird)
    house->birds = birds;
    
    cout << "\nHouse:" << endl;
    //using house print out all the birds and dogs that live there. You'll need a loop for the birds
    //(remember y tells us how many there are)
    house->dogs->print();
    for (int i = 0; i < y; i++)
        house->birds[i].print();
    
    //Great Job!!!! We have given home to all these beautiful animals. Remember to adopt your next pet and support responsible breeding!
    //
    //...20 years later...
    //
    //All the dogs and birds are death. circle of life, hakuna matata, They lived happy lives. Time to bury/cremate the remains...
    
    //de-allocate the memory of the birds (from the house) (don't worry they will be in our hearts forever!) use delete.
    delete []house->birds;
    
    //set to null after... I know rough!
    house->birds = NULL;

    //We cannot de-allocate the memory of the dog in the house using free or delete as she was not dynamically allocated.
    //If we tried it we would get a core dump, try it:
    //free(house->dogs); //Make sure you uncomment after you try it.
    
    //What we can do is set the dogs pointer to NULL so we don't accidentally try to access it since the dog is stil there (Padme is indestructible!)
    house->dogs = NULL;
    
    //This program went dark real fast! I guess let's just call it a day :\
    //Free up your last pointers and submit this. That includes anything we dynamically allocated. So like the animal1 we did.
    //Oh wait we can't access it because we overwrote it! MEMORY LEAK :( Well at least when program ends it will be back but SHAME ON YOU
    //for not noticing. That's literally like we forgot our animal in the park! Well nothing to do now.
    //Still make sure you de-allocate other pointers like house in general.
    //Note that had we called free(house) before deleting individual objects we would have ended up with memory leaks.
    // Use free or delete for the rest of the pointers. Don't forget to set them to null so we don't have any dangling pointers as well
    free(house);    // de-allocating house pointer
    house = NULL;
    delete name;
    name = NULL;
    free(mptr);
    mptr = NULL;
    ptr = NULL;     // nothing to de-allocate, just setting pointer to null
    
    cout << "F" << endl; //Also don't forget to cout F to pay respects to dogs and birds. RIP
    
    
    return 0;//Disclaimer: No Animals, Dogs, or Birds were harmed in the making of this program. The same cannot be said about memory locations.
}

