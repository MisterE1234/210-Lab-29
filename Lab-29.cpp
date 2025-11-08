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

const int AMOUNT_SIMULATE = 25, EVENT_NUM = 3, VOTER_NUM = 100,  INITIAL_R = 40,  INITIAL_L = 40, INITIAL_I = 40, PROB_DISASTER = 40, PROB_WAR = 10, PROB_ECONOMY = 45; //The economy Probablity is actualy times 2

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
    //Parameters: a voter, 2 bools for the disaster and war events, and int variable for the economic events ,  an int to hold the presidents party, and an int hold the voters party.
    //returns: an integer indicating which party they are a part of now and and if they are staunch.

    int partyChange(Voter, bool, bool, int, int, int);

//Define main function:
    //
    //Initialize a map to store party information, each associated with its different kinds of voters.
    //declare int variables to hold the population in each party and how many are staunch or non-voters. Also a int variable that hold who is in charge:
    
    int main (){

        srand(time(0));
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

        int presidentParty = 0;

        int temp;
        int event;

        char confirm;
        bool disaster = false;
        bool war = false;
        int economic = 0;


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
            // run a random numbers for disaster, war, and economic condition.
            for (int e = 1; e >= EVENT_NUM, e++;){
                event = rand()%100 + 1;

                switch(e){
                    case 1:
                    if (event <= PROB_DISASTER){
                        disaster = true;
                    }
                    break;
                    case 2:
                    if (event <= PROB_WAR){
                        war = true;
                    }
                    break;
                    case 3:
                    if (event <= PROB_ECONOMY){
                        economic = 1;
                    }
                    else if(event >= 100 - PROB_ECONOMY)
                        economic = 2;
                    break;

                }

            }

                // Iterate through each voting division
                    // for each voter see if they are going to change party, stay, or become staunch
                        //if they become stauch it makes it harder for them to switch parties, same if they switch to non-voter.
                        // If they become staunch update their bool variable, if tehy were staunch and left their party set their stauch to false.
                        //If they are changing parties, save voter data to a temporary Voter and delete the original and then place the Voter in their new party.
                        //use the int variables to keep track of how many are in a division and how many are staunch.

                    //Print the changes by displaying the current party population with staunches as well.
                        //Pause after each display and wait for the user to confirm to continue.
        }
    }
    //end of main function.

int partyChange(Voter v, bool disaster, bool war, int economy, int president, int party){
    int newParty = 0;
    int change = 0;
    int prob;
    int staunch = 0;
    if(v.get_staunch()){
            staunch = 20;
        }
    switch(party){
        case (1) : // The voter is a part of the left party:

        
        switch(president){
            case 1: // the president is an Left party member (same as voter):
                switch(v.get_leaning()){
                //left leaning:
                    case 1:{
                
                        if (economy = 2){ //Economic downturn:
                            change = +(20 - staunch);
                        }

                        if (disaster == true){ // disaster happened:
                            change = +(25 - staunch);
                        }

                        if (war == true) { //war happened:
                            change = +(40 - staunch);
                    
                        }
                        if (economy = 1){ // Economic boom:
                            change = -(20 + staunch);
                        }

                    

                        break;
                     }
                    //moderate leaning:
                    case 2:{
                
                        if (economy = 2){ //Economic downturn:
                            change = +(30 - staunch);
                        }

                        if (disaster == true){ // disaster happened:
                            change = +(35 - staunch);
                        }

                        if (war == true) { //war happened:
                            change = +(50 - staunch);
                    
                        }
                        if (economy = 1){ // Economic boom:
                            change = -(15 + staunch);
                        }

                
                    break;
                    }
            //right leaning:
                    case 3:{
                        if (economy = 2){ //Economic downturn:
                            change = +(40 - staunch);
                        }

                        if (disaster == true){ // disaster happened:
                            change = +(45 - staunch);
                        }

                        if (war == true) { //war happened:
                            change = +(60 - staunch);
                    
                        }
                        if (economy = 1){ // Economic boom:
                            change = -(10 + staunch);
                        }

                    break;
                    }
                    //error handling
                    default:
                        cout << "error. invalid political leaning number.\n ";
                }
            break;

            case 2: // The president is an Independent:
                switch(v.get_leaning()){
                //left leaning:
                    case 1:{
                
                        if (economy = 2){ //Economic downturn:
                            change = -(15 + staunch);
                        }

                        if (disaster == true){ // disaster happened:
                            change = -(10 + staunch);
                        }

                        if (war == true) { //war happened:
                            change = -(25 + staunch);
                    
                        }
                        if (economy = 1){ // Economic boom:
                            change = +(15 - staunch);
                        }

                    

                        break;
                     }
                    //moderate leaning:
                    case 2:{
                
                        if (economy = 2){ //Economic downturn:
                            change = -(10 + staunch);
                        }

                        if (disaster == true){ // disaster happened:
                            change = -(5 + staunch);
                        }

                        if (war == true) { //war happened:
                            change = -(20 + staunch);
                    
                        }
                        if (economy = 1){ // Economic boom:
                            change = +(25 - staunch);
                        }

                
                    break;
                    }
            //right leaning:
                    case 3:{
                        if (economy = 2){ //Economic downturn:
                            change = -(10 + staunch);
                        }

                        if (disaster == true){ // disaster happened:
                            change = -(10 + staunch);
                        }

                        if (war == true) { //war happened:
                            change = -(25 + staunch);
                    
                        }
                        if (economy = 1){ // Economic boom:
                            change = +(20 - staunch);
                        }

                    break;
                    }
                    //error handling
                    default:
                        cout << "error. invalid political leaning number.\n ";
                }
            break;
            case 3: // the President a Right Party member:
                switch(v.get_leaning()){
                //left leaning:
                    case 1:{
                
                        if (economy = 2){ //Economic downturn:
                            change = -(20 + staunch);
                        }

                        if (disaster == true){ // disaster happened:
                            change = -(15 + staunch);
                        }

                        if (war == true) { //war happened:
                            change = -(50 + staunch);
                    
                        }
                        if (economy = 1){ // Economic boom:
                            change = +(15 - staunch);
                        }

                    

                        break;
                     }
                    //moderate leaning:
                    case 2:{
                
                        if (economy = 2){ //Economic downturn:
                            change = -(10 + staunch);
                        }

                        if (disaster == true){ // disaster happened:
                            change = -(10 + staunch);
                        }

                        if (war == true) { //war happened:
                            change = -(20 + staunch);
                    
                        }
                        if (economy = 1){ // Economic boom:
                            change = +(20 - staunch);
                        }

                
                    break;
                    }
            //right leaning:
                    case 3:{
                        if (economy = 2){ //Economic downturn:
                            change = -(5 + staunch);
                        }

                        if (disaster == true){ // disaster happened:
                            change = -(10 + staunch);
                        }

                        if (war == true) { //war happened:
                            change = -(15 + staunch);
                    
                        }
                        if (economy = 1){ // Economic boom:
                            change = +(25 - staunch);
                        }

                    break;
                    }
                    //error handling
                    default:
                        cout << "error. invalid political leaning number.\n ";
                }

            break;
            default: //error handling
                cout << "Error. Invalid Presidential Party.\n";
        }
        break;

        case (2) : // The voter is a part of the Independent party:
        switch(president){
            case 1: // the president is an Left party member (same as voter):
                switch(v.get_leaning()){
                //left leaning:
                    case 1:{
                
                        if (economy = 2){ //Economic downturn:
                            change = -(10 + staunch);
                        }

                        if (disaster == true){ // disaster happened:
                            change = -(10 + staunch);
                        }

                        if (war == true) { //war happened:
                            change = -(20 + staunch);
                    
                        }
                        if (economy = 1){ // Economic boom:
                            change = +(20 - staunch);
                        }

                    

                        break;
                     }
                    //moderate leaning:
                    case 2:{
                
                        if (economy = 2){ //Economic downturn:
                            change = -(10 + staunch);
                        }

                        if (disaster == true){ // disaster happened:
                            change = -(10 + staunch);
                        }

                        if (war == true) { //war happened:
                            change = -(25 + staunch);
                    
                        }
                        if (economy = 1){ // Economic boom:
                            change = +(30 - staunch);
                        }

                
                    break;
                    }
            //right leaning:
                    case 3:{
                        if (economy = 2){ //Economic downturn:
                            change = -(15 + staunch);
                        }

                        if (disaster == true){ // disaster happened:
                            change = -(15 + staunch);
                        }

                        if (war == true) { //war happened:
                            change = -(25 + staunch);
                    
                        }
                        if (economy = 1){ // Economic boom:
                            change = +(25 - staunch);
                        }

                    break;
                    }
                    //error handling
                    default:
                        cout << "error. invalid political leaning number.\n ";
                }
            break;

            case 2: // The president is an Independent:
                switch(v.get_leaning()){
                //left leaning:
                    case 1:{
                
                        if (economy = 2){ //Economic downturn:
                            change = +(30 - staunch);
                        }

                        if (disaster == true){ // disaster happened:
                            change = +(30 - staunch);
                        }

                        if (war == true) { //war happened:
                            change = +(45 - staunch);
                    
                        }
                        if (economy = 1){ // Economic boom:
                            change = -(15 + staunch);
                        }

                    

                        break;
                     }
                    //moderate leaning:
                    case 2:{
                
                        if (economy = 2){ //Economic downturn:
                            change = +(20 - staunch);
                        }

                        if (disaster == true){ // disaster happened:
                            change = +(25 - staunch);
                        }

                        if (war == true) { //war happened:
                            change = +(35 - staunch);
                    
                        }
                        if (economy = 1){ // Economic boom:
                            change = -(25 + staunch);
                        }

                
                    break;
                    }
            //right leaning:
                    case 3:{
                        if (economy = 2){ //Economic downturn:
                            change = +(25 - staunch);
                        }

                        if (disaster == true){ // disaster happened:
                            change = +(30 - staunch);
                        }

                        if (war == true) { //war happened:
                            change = +(40 - staunch);
                    
                        }
                        if (economy = 1){ // Economic boom:
                            change = -(20 + staunch);
                        }

                    break;
                    }
                    //error handling
                    default:
                        cout << "error. invalid political leaning number.\n ";
                }
            break;
            case 3: // the President a Right Party member:
                switch(v.get_leaning()){
                //left leaning:
                    case 1:{
                
                        if (economy = 2){ //Economic downturn:
                            change = -(15 + staunch);
                        }

                        if (disaster == true){ // disaster happened:
                            change = -(10 + staunch);
                        }

                        if (war == true) { //war happened:
                            change = -(25 + staunch);
                    
                        }
                        if (economy = 1){ // Economic boom:
                            change = +(20 - staunch);
                        }

                    

                        break;
                     }
                    //moderate leaning:
                    case 2:{
                
                        if (economy = 2){ //Economic downturn:
                            change = -(10 + staunch);
                        }

                        if (disaster == true){ // disaster happened:
                            change = -(10 + staunch);
                        }

                        if (war == true) { //war happened:
                            change = -(20 + staunch);
                    
                        }
                        if (economy = 1){ // Economic boom:
                            change = +(25 - staunch);
                        }

                
                    break;
                    }
            //right leaning:
                    case 3:{
                        if (economy = 2){ //Economic downturn:
                            change = -(10 + staunch);
                        }

                        if (disaster == true){ // disaster happened:
                            change = -(10 + staunch);
                        }

                        if (war == true) { //war happened:
                            change = -(15 + staunch);
                    
                        }
                        if (economy = 1){ // Economic boom:
                            change = +(30 - staunch);
                        }

                    break;
                    }
                    //error handling
                    default:
                        cout << "error. invalid political leaning number.\n ";
                }

            break;
            default: //error handling
                cout << "Error. Invalid Presidential Party.\n";
        }
        case (3) : // The voter is a part of the Right party:
        switch(president){
            case 1: // the president is an Left party member (same as voter):
                switch(v.get_leaning()){
                //left leaning:
                    case 1:{
                
                        if (economy = 2){ //Economic downturn:
                            change = -(20 + staunch);
                        }

                        if (disaster == true){ // disaster happened:
                            change = -(15 + staunch);
                        }

                        if (war == true) { //war happened:
                            change = -(25 + staunch);
                    
                        }
                        if (economy = 1){ // Economic boom:
                            change = +(35 - staunch);
                        }

                    

                        break;
                     }
                    //moderate leaning:
                    case 2:{
                
                        if (economy = 2){ //Economic downturn:
                            change = -(15 + staunch);
                        }

                        if (disaster == true){ // disaster happened:
                            change = -(10 + staunch);
                        }

                        if (war == true) { //war happened:
                            change = -(25 + staunch);
                    
                        }
                        if (economy = 1){ // Economic boom:
                            change = +(30 - staunch);
                        }

                
                    break;
                    }
            //right leaning:
                    case 3:{
                        if (economy = 2){ //Economic downturn:
                            change = -(10 + staunch);
                        }

                        if (disaster == true){ // disaster happened:
                            change = -(10 + staunch);
                        }

                        if (war == true) { //war happened:
                            change = -(25 + staunch);
                    
                        }
                        if (economy = 1){ // Economic boom:
                            change = +(25 - staunch);
                        }

                    break;
                    }
                    //error handling
                    default:
                        cout << "error. invalid political leaning number.\n ";
                }
            break;

            case 2: // The president is an Independent:
                switch(v.get_leaning()){
                //left leaning:
                    case 1:{
                
                        if (economy = 2){ //Economic downturn:
                            change = -(15 + staunch);
                        }

                        if (disaster == true){ // disaster happened:
                            change = -(10 + staunch);
                        }

                        if (war == true) { //war happened:
                            change = -(30 + staunch);
                    
                        }
                        if (economy = 1){ // Economic boom:
                            change = +(35 - staunch);
                        }

                    

                        break;
                     }
                    //moderate leaning:
                    case 2:{
                
                        if (economy = 2){ //Economic downturn:
                            change = -(10 + staunch);
                        }

                        if (disaster == true){ // disaster happened:
                            change = -(10 + staunch);
                        }

                        if (war == true) { //war happened:
                            change = -(25 + staunch);
                    
                        }
                        if (economy = 1){ // Economic boom:
                            change = +(30 - staunch);
                        }

                
                    break;
                    }
            //right leaning:
                    case 3:{
                        if (economy = 2){ //Economic downturn:
                            change = -(15 + staunch);
                        }

                        if (disaster == true){ // disaster happened:
                            change = -(15 + staunch);
                        }

                        if (war == true) { //war happened:
                            change = -(30 + staunch);
                    
                        }
                        if (economy = 1){ // Economic boom:
                            change = +(25 - staunch);
                        }

                    break;
                    }
                    //error handling
                    default:
                        cout << "error. invalid political leaning number.\n ";
                }
            break;
            case 3: // the President a Right Party member:
                switch(v.get_leaning()){
                //left leaning:
                    case 1:{
                
                        if (economy = 2){ //Economic downturn:
                            change = +(30 - staunch);
                        }

                        if (disaster == true){ // disaster happened:
                            change = +(30 - staunch);
                        }

                        if (war == true) { //war happened:
                            change = +(50 - staunch);
                    
                        }
                        if (economy = 1){ // Economic boom:
                            change = -(20 + staunch);
                        }

                    

                        break;
                     }
                    //moderate leaning:
                    case 2:{
                
                        if (economy = 2){ //Economic downturn:
                            change = +(20 - staunch);
                        }

                        if (disaster == true){ // disaster happened:
                            change = +(25 - staunch);
                        }

                        if (war == true) { //war happened:
                            change = +(45 - staunch);
                    
                        }
                        if (economy = 1){ // Economic boom:
                            change = -(20 + staunch);
                        }

                
                    break;
                    }
            //right leaning:
                    case 3:{
                        if (economy = 2){ //Economic downturn:
                            change = +(25 - staunch);
                        }

                        if (disaster == true){ // disaster happened:
                            change = +(20 - staunch);
                        }

                        if (war == true) { //war happened:
                            change = +(40 - staunch);
                    
                        }
                        if (economy = 1){ // Economic boom:
                            change = -(25 + staunch);
                        }

                    break;
                    }
                    //error handling
                    default:
                        cout << "error. invalid political leaning number.\n ";
                }

            break;
            default: //error handling
                cout << "Error. Invalid Presidential Party.\n";
        }
        
    }

    prob = rand()%100 + change;
    if(prob < 5){
        return newParty;
    }
    else if(prob < 20){
        newParty = party;
        return newParty;
    }
    else if(prob < 35){
        newParty 
    }

    
}