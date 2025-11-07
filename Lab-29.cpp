//COMSC-210|Ethan Aylard|Lab-30
//IDE used: Visual Studio Code

//Include necessary headers for files, data structures, processing, and ect.

#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <array>


//Define a class named Voter:
    //would hold a int political leaning variable with three options (1-3). To represent left, moderate, right.
    //an bool variable to see if the voter is staunch or not.
    //a partial constructor to have a custom party affiliation with staunch set false by default.

    class Voter {
        //Private variables for politcal leaning and if the voter is staunch or not.
        private:
            int leaning;
            bool staunch;

        // public functions:
        public:
        //Constructors:
        Voter() {leaning = 0; staunch = false;}
        Voter(int l) {leaning = l; staunch = false;}

        //Setters:
        void set_leaning (int l) {leaning = l;};
        void set_staunch (bool s) {staunch = s;};

        //getters:
        int get_leaning () const {return leaning;};
        bool get_staunch () const {return staunch;};

    };


//Define a function that would simulate what event[s] would have happend for this voting period and how they affect different voters using a probabilty matrix.
    //Parameters: a voter, and 3 random int variables
    //returns: an integer indicating which party they are a part of now and and if they are staunch.

    int partyChange(Voter, int, int, int);

//Define main function:
    //
    //Initialize a map to store party information, each associated with its different kinds of voters.
    //declare int variables named rPop, lPop, iPop, nonPop, and rStaunch, lStaunch, iStaunch, and nonStaunch. Also a string array that hold who is in charge:
    
    int main (){
        map < string , array <list <Voter>, 3 >> polLandscape;
        list <Voter> vote;

    
    //Open a external file to read integer to the list to become voters.
        //if it does not open, print an error message and return -1.
    
    //Read data to lists: split three ways 30% R: 30% L: 40% I.
        // for each line extract a party affilation to make a voter.

    //close file

    // Begin a time-based simulation for voting changes:
        //25 time intervals
            // run a random numbers for disaster, war, and economic condition.
                // Iterate through each voting division
                    // for each voter see if they are going to change party, stay, or become staunch
                        //if they become stauch it makes it harder for them to switch parties, same if they switch to non-voter.
                        // If they become staunch update their bool variable, if tehy were staunch and left their party set their stauch to false.
                        //If they are changing parties, save voter data to a temporary Voter and delete the original and then place the Voter in their new party.
                        //use the int variables to keep track of how many are in a division and how many are staunch.

                    //Print the changes by displaying the current party population with staunches as well.
                        //Pause after each display and wait for the user to confirm to continue.
                    
    }
    //end of main function.
