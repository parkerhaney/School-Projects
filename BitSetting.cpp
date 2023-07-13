/* Program Name: BitSet
 * Student Name: Parker Haney
 * Net ID: phaney
 * Student ID: 000-54-2681
 * Program Description: This program uses bitsetting to store true or false return values, and 
 * several commands to return these boolean values, print binary numbers/sets, turn a bit "on" 
 * and "off", as well as quitting the program.
 *
 * Help By: Abrahm Bradley
 * */
#include<iostream>
#include<vector>
#include<sstream>
#include<string>

using namespace std;

class BITSET {
    vector<int> mSets; //Where actual bitset data is stored. This makes the 32-bit sets, m number of sets. No higher than bit 127
public:
    BITSET(); // Resizes the private vector to a size of 1 for newley created sets and others
    bool Test(int index) const; //Boolean, if bit is 1, true. If bit is 0, false (on or off)
    void Set(int index); // Sets the given bit to 1 (turns on), if it already is 1, it has no affect
    void Clear(int index); // The opposite of set(), takes a bit and makes it 0 (turns off), if already 0 then no affect
    int GetNumSets() const; // No parameters, returns number of sets in an integer.
    int GetSet(int index) const; // Takes a set index and will return the entire set as a single 4-byte integer. If not, return 0
};
string ToBinary(int bit_set, int spacing=4);
int main() {
    /* This main function is where the User enters one of 6 commands that accesses
     * the functions that are under the main. */
    BITSET sets;
    string command;
    int which;
    do {
        cout << "> ";
        if (!(cin >> command) || "q" == command) {
            break;
        }
        // Handle the commands here
        if ("t" == command) {
            if (!(cin >> which)) {
                cout << "Invalid index\n";
            }
            else {
                cout << sets.Test(which) << '\n';
            }
        }
        else if ("s" == command) {
            if (!(cin >> which)) {
                cout << "Invalid index\n";
            }
            else {
                sets.Set(which);
            }
        }
        else if ("g" == command) {
            int spacing;
            string line;
            getline(cin, line);
            istringstream sin {line};
            if (!(sin >> which)) {
                cout << "Invalid index\n";
            }
            else {
                if (!(sin >> spacing)) {
                    spacing = 4;
                }
                cout << ToBinary(sets.GetSet(which), spacing) << '\n';
            }
        }
        else if ("c" == command) {
            if (!(cin >> which)) {
                cout << "Invalid index\n";
            }
            else { 
                sets.Clear(which);
            }
        }
        else if ("n" == command) {
            cout << sets.GetNumSets() << endl;
        }
        else {
            cout << "Unknown command '" << command << "'\n";
        }
    } while (true);
    return 0;
}
string ToBinary(int bit_set, int spacing) {
    /* This retunrs the binary string of 1's and 0's. This takes care of the spacing 
     * and formatting of the binary string. */
    string ret;
    for (int i = 31; i >= 0; i--) {
        int mask = bit_set & 1 << i;
        if ((bit_set & mask) != 0) {
            ret += '1';
        }
        else {
            ret += '0';
        }
        if ((i != 0) && (((32 - i) % spacing) == 0)) {  
            ret += ' ';
        }
    }
    return ret;
}
// BITSET Class Members
BITSET::BITSET() :
    mSets(1, 0)
{}

bool BITSET::Test(int index) const {
    /* This tests the given bit at its index in its specific set to see if there is 
     * a 1 or a 0 (Test if its on or off). */
    int which_set = index >> 5; 
    int which_bit = index % 32; 
    int mask = 1 << which_bit;
    if (which_set >= GetNumSets()) {
        return false;
    }
    return (mSets.at(which_set) & mask) != 0;
}

void BITSET::Set(int index) {
    /* This turns "on" the given bit. It returns a 1 in the given index and set. */
    int which_set = index >> 5; 
    int which_bit = index % 32;
    int mask = 1 << which_bit;
    if ((which_set + 1) > GetNumSets()) {
        mSets.resize(which_set + 1);
    }

    mSets.at(which_set) = (mSets.at(which_set) | mask);
}

void BITSET::Clear(int index) {
    /* Opposite to Set, this turns "off" a bit. It returns a 
     * 0 in the given index and set. */
    int which_set = index >> 5; 
    int which_bit = index % 32; 
    if (which_set < GetNumSets()) {
        mSets.at(which_set) = (which_bit & mSets.at(which_set)); 
        for (int i = mSets.size() - 1; i > 0; i--) {
            if (mSets.at(i) == 0) {
                mSets.pop_back();
            }
            else {
                break;
            }
        }
    }
}

int BITSET::GetNumSets() const {
    /* This returns the number of sets present, which is used 
     * to check for out of bounds and resizing in other functions. */ 
    return static_cast<int>(mSets.size());
}

int BITSET::GetSet(int which_set) const {
    //Retrieves a given set and returns it to the screen/console.
    if ((which_set + 1) > GetNumSets()) {
        return 0;
    }
    else {
        return mSets.at(which_set);
    }
}
