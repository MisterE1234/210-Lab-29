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

using namespace std;

const int AMOUNT_SIMULATE = 25, VOTER_NUM = 100,  INITIAL_R = 40,  INITIAL_L = 40, INITIAL_I = 40, PROB_DISASTER = 40, PROB_WAR = 10, PROB_ECONOMY = 45; //The economy Probablity is actualy times 2

//Define a class named Voter:
    //would hold a int political leaning variable with three options (1-3). To represent left, moderate, right.
    //an bool variable to see if the voter is staunch or not.
    //a partial constructor to have a custom party affiliation with staunch set false by default.

    class Voter {
        //Private variables for politcal leaning and if the voter is staunch or not.
        private:
            int leaning;
            bool staunch;
            bool non_vote;

        // public functions:
        public:
        //Constructors:
        Voter() {leaning = 0; staunch = false; non_vote = false;};
        Voter(int l) {leaning = l; staunch = false; non_vote = false;}

        //Setters:
        void set_leaning (int l) {leaning = l;};
        void set_staunch (bool s) {staunch = s;};
        void set_non_vote (bool n) {non_vote = n;};

        //getters:
        int get_leaning () const {return leaning;};
        bool get_staunch () const {return staunch;};
        bool get_non_vote () const {return non_vote;};

    };


//Define a function that would simulate what event[s] would have happend for this voting period and how they affect different voters using a probabilty matrix.
    //Parameters: a voter, 2 bools for the disaster and war events, and int variable for the economic events , and an int to hold the presidents party.
    //returns: an integer indicating which party they are a part of now and and if they are staunch.

    int partyChange(Voter, bool, bool, int, int);

//Define main function:
    //
    //Initialize a map to store party information, each associated with its different kinds of voters.
    //declare int variables to hold the population in each party and how many are staunch or non-voters. Also a int variable that hold who is in charge:
    
    int main (){
        map < string, array <list <Voter>, 3 >> polLandscape;
        int rPop = 0;
        int lPop = 0;
        int iPop = 0;
        int rStaunch = 0;
        int lStaunch = 0;
        int iStaunch = 0;
        int rNon = 0;
        int lNon = 0;
        int iNon = 0;
        int presidentParty;
        int temp;


    polLandscape["Right"] = {};
    polLandscape["Left"] = {};
    polLandscape["Independent"] = {};
    //Open a external file to read integer to the list to become voters.
        //if it does not open, print an error message and return -1.

    ifstream iFile; //input file stream object
    iFile.open("voters.txt"); //open the input file

    //check if the file opened successfully
    if (!iFile)
    {
        cout << "Error opening file!" << endl;
        return 1;
    }

    
    
    //Read data to lists: split three ways 40% R: 40% L: 20% I.
    auto it  = polLandscape.find("Right");
        // for each line extract a party affilation to make a voter.
    for(int i = 0; i < INITIAL_R; i++){
        iFile >> temp;
        it->second[temp].push_back(Voter(temp));  
    }

    it  = polLandscape.find("Left");
        // for each line extract a party affilation to make a voter.
    for(int i = 0; i < INITIAL_L; i++){
        iFile >> temp;
        it->second[temp].push_back(Voter(temp));  
    }

    it  = polLandscape.find("Independent");
        // for each line extract a party affilation to make a voter.
    for(int i = 0; i < INITIAL_I; i++){
        iFile >> temp;
        it->second[temp].push_back(Voter(temp));  
    }

    //close file
    iFile.close();

    // Begin a time-based simulation for voting changes:
        //25 time intervals
        for (int i = 0; i > AMOUNT_SIMULATE, i++;){


        }
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

    int partyChange(Voter v, bool disaster, bool war, int economy, int president){
        int newParty = 0;
        
        
        switch(v.get_leaning()){

            case 1:{

            break;
            }

            case 2:{

            break;
            }

            case 3:{

            break;
            }
            default:
            cout << "error. invalid political leaning number ";
        }

        return newParty;
    }