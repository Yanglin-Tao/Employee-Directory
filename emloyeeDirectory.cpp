/*
  Employee Directory
 
  Focus: Dynamic arrays and copy control
 */

#include <string>
#include <iostream>
using namespace std;

//
// Position class
//
class Position {
    friend ostream& operator<<(ostream& os, const Position& rhs) {
        os << '[' << rhs.title << ',' << rhs.salary << ']';
        return os;
    }
public:
    Position(const string& aTitle, double aSalary)
        : title(aTitle), salary(aSalary) {}
    const string& getTitle() const { return title; }
    double getSalary() const { return salary; }
    void changeSalaryTo(double d) { salary = d; }
private:
    string title;
    double salary;
}; 


//
// Directory class
//
class Directory {
    //
    // nested Entry class
    //
    class Entry {
    friend ostream& operator<<(ostream& os, const Entry& rhs) {
        os << rhs.name << ' ' << rhs.room
           << ' ' << rhs.phone << ", " << *rhs.pos;
        return os;
    }
    public:
    Entry(const string& name, unsigned room, unsigned phone, Position& position)
        : name(name), room(room), phone(phone), pos(&position) {
    }
    const string& getName() const { return name; }
    unsigned getPhone() const { return phone; }
    private:
    string name;
    unsigned room;
    unsigned phone;
    Position* pos;
    }; // class Entry


    // Overload Directory's output operator
    // ...
    friend ostream& operator <<(ostream& os, const Directory& rhs){
        cout << "Directory: " << rhs.company << endl;
        for(size_t i = 0; i < rhs.size; i++){
            cout << *(rhs.entries[i]) << endl;
        }
        return os;
    }

public:
    // Of course the first function you need to write for this (or
    // any) class is...
    // ???
    // ...
    
    Directory(const string& companyName) : company(companyName), size(0), capacity(0){
    }
    // We'll get you started with the add method, but obviously you
    // have a lot of work to do here.
    
    const string& getCompanyName() const{
        return company;
    }
    
    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
        if (size == capacity)    {
            // something is missing!!!  Add it!
            if(size == 0){
                capacity = 1;
                entries = new Entry*[1];
            }
            else{
                Entry** oldEntry = entries;
                entries = new Entry*[2*capacity];
                for(size_t i = 0; i < size; i++){
                    entries[i] = oldEntry[i];
                }
                delete[] oldEntry;
                capacity *= 2;
            }

        } // if
        entries[size] = new Entry(name, room, ph, pos);
        ++size;
    } // add
    
    // overload Directory's [] operator
    
    unsigned operator[](string name) const{
        for(size_t i = 0; i < size; i++){
            if(entries[i] -> getName() == name){
                return entries[i] -> getPhone();
            }
        }
        return 0;
    }
    
    // destructor
    ~Directory(){
        for(size_t i = 0; i < size; i++){
            delete entries[i];
        }
        delete[] entries;
    }
    
    // copy constructor
    Directory(const Directory& rhs) : company(rhs.company), size(rhs.size), capacity(rhs.capacity){
        entries = new Entry*[capacity];
        for(size_t i = 0; i < rhs.size; i++){
            entries[i] = new Entry(*(rhs.entries[i]));
        }
        
    }
    
    // assignment operator
    Directory& operator=(const Directory& rhs){
        if(this != &rhs){
            delete[] entries;
            entries = new Entry*[capacity];
            size = rhs.size;
            capacity = rhs.capacity;
            company = rhs.company;
            for(size_t i = 0; i < rhs.size; i++){
                entries[i] = new Entry(*(rhs.entries[i]));
            }
        }
        return *this;
    }

private:
    Entry** entries; // Notice the type!!! Pointer to Entry pointers.
    size_t size;
    size_t capacity;
    string company;
}; // class Directory

void doNothing(Directory dir) {
    // You need to overload the Directory output operator before
    // uncommenting the next line.

    cout << dir << endl;
}

int main() {
    
    // Note that the Postion objects are NOT on the heap.
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);
    
    // Create a Directory
    Directory d("HAL");
    d.add("Marilyn", 123, 4567, boss);
    cout << d << endl;

    Directory d2 = d;    // What function is being used??
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << d << endl;

    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";

    // Should display 1592
    cout << d2["Carmack"] << endl;

    
    Directory d3("IBM");
    d3.add("Torvalds", 628, 3185, techie);
    d3.add("Ritchie", 123, 5813, techie);
    

    d2 = d3;
    // Should display 5813
    cout << d2["Ritchie"] << endl;

    cout << d2 << endl;
     
    
} // main

