//COMSC-210|Ethan Aylard|Lab-31
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

        bool debug = true;

        map < string, array <list <Voter>, 3 >> polLandscape;
        int rPop = INITIAL_R;
        int lPop = INITIAL_L;
        int iPop = INITIAL_I;

        int rStaunch = 0;
        int lStaunch = 0;
        int iStaunch = 0;

        int rNon = 0;
        int lNon = 0;
        int iNon = 0;

        int presidentParty = rand()%3 + 1; //The presidents party alignment will randomly be either Left(1), Independent(2), Right(3).
        int voterParty;

        int temp;
        int event;

        char confirm;
        bool disaster = false;
        bool war = false;
        int economic = 0;

        if(debug){
        cout << "testing Phrase:\n\n";
        }

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

    if(debug){
        cout << "File closed successfully!\n";
    }

    // Begin a time-based simulation for voting changes:
        //25 time intervals
        for (int year = 0; year > AMOUNT_SIMULATE, year++;){
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

                if(debug){
                    cout << "Event chosen successfully!\n";
                }
                //Iterate thorugh each map and list.
                
                auto itL  = polLandscape.find("Left");
                auto itI = polLandscape.find("Independent");
                auto itR = polLandscape.find("Right");
                Voter tempVote;

                // for each voter see if they are going to change party, stay, or become staunch
                        //if they become stauch it makes it harder for them to switch parties, same if they switch to non-voter.
                        // If they become staunch update their bool variable, if tehy were staunch and left their party set their stauch to false.
                        //If they are changing parties, save voter data to a temporary Voter and delete the original and then place the Voter in their new party.
                        //use the int variables to keep track of how many are in a division and how many are staunch.
                
                //going through the Left party first:
                voterParty = 1;
                for(int i = 0; i < 3; i++){
                    list <Voter>& tempList = itL->second[i];
                    
                    for(auto vote = tempList.begin(); vote !=tempList.end();){
                        switch (partyChange(*vote , disaster , war , economic , presidentParty , voterParty)){
                            case 0://Change to staunch
                                if(!vote->get_staunch()){
                                vote->set_staunch(true);
                                lStaunch++;
                                }
                            case 1:
                                break;
                            case 2: //Change voter to Independent:
                                tempVote = *vote;
                                tempList.erase(vote);
                                itI->second[i].push_back(tempVote);
                                
                                if(vote->get_staunch()){
                                    vote->set_staunch(false); //no longer staunch
                                    lStaunch--;
                                }
                                //changing the population count:

                                lPop--;
                                iPop++;
                                break;
                            case 3: //change voter to Right:
                                tempVote = *vote;
                                tempList.erase(vote);
                                itR->second[i].push_back(tempVote);
                                
                                if(vote->get_staunch()){
                                    vote->set_staunch(false); //no longer staunch
                                    lStaunch--;
                                }
                                //changing the population count:

                                lPop--;
                                rPop++;
                                break;
                            case 4: //change voter to non-Voter:
                                if(vote->get_non_vote()){
                                    vote->set_non_vote(false);
                                    lNon--;    
                                }
                                else{
                                    vote->set_non_vote(true);
                                    lNon++;
                                }
                                break;
                            default:
                                cout << "Error!. PartyChange not 0-4.\n";
                                return -1;
                            
                        }

                    }

                }

                //going through the Independent party next:
                voterParty = 2;
                for(int i = 0; i < 3; i++){
                    list <Voter>& tempList = itL->second[i];
                    
                    for(auto vote = tempList.begin(); vote !=tempList.end();){
                        switch (partyChange(*vote , disaster , war , economic , presidentParty , voterParty)){
                            case 0://Chnage to staunch
                                if(!vote->get_staunch()){
                                vote->set_staunch(true);
                                iStaunch++;
                                }
                                break;
                            case 1: //change to Left
                                tempVote = *vote;
                                tempList.erase(vote);
                                itL->second[i].push_back(tempVote);
                                
                                if(vote->get_staunch()){
                                    vote->set_staunch(false); //no longer staunch
                                    iStaunch--;
                                }
                                //changing the population count:

                                iPop--;
                                lPop++;
                                break;
                            case 2: //Change voter to Independent:
                                
                                break;
                            case 3: //change voter to Right:
                                tempVote = *vote;
                                tempList.erase(vote);
                                itR->second[i].push_back(tempVote);
                                
                                if(vote->get_staunch()){
                                    vote->set_staunch(false); //no longer staunch
                                    iStaunch--;
                                }
                                //changing the population count:

                                iPop--;
                                rPop++;
                                break;
                            case 4: //change voter to non-Voter:
                                if(vote->get_non_vote()){
                                    vote->set_non_vote(false);
                                    iNon--;    
                                }
                                else{
                                    vote->set_non_vote(true);
                                    iNon++;
                                }
                                break;
                            default:
                                cout << "Error!. PartyChange not 0-4.\n";
                                return -1;
                            
                        }

                    }

                }

                //going through the Right party next:
                voterParty = 3;
                for(int i = 0; i < 3; i++){
                    list <Voter>& tempList = itL->second[i];
                    
                    for(auto vote = tempList.begin(); vote !=tempList.end();){
                        switch (partyChange(*vote , disaster , war , economic , presidentParty , voterParty)){
                            case 0://Chnage to staunch
                                if(!vote->get_staunch()){
                                vote->set_staunch(true);
                                rStaunch++;
                                }
                                break;
                            case 1: //change to Left
                                tempVote = *vote;
                                tempList.erase(vote);
                                itL->second[i].push_back(tempVote);
                                
                                if(vote->get_staunch()){
                                    vote->set_staunch(false); //no longer staunch
                                    rStaunch--;
                                }
                                //changing the population count:

                                rPop--;
                                lPop++;
                                break;
                            case 2: //Change voter to Independent:
                                tempVote = *vote;
                                tempList.erase(vote);
                                itI->second[i].push_back(tempVote);
                                
                                if(vote->get_staunch()){
                                    vote->set_staunch(false); //no longer staunch
                                    rStaunch--;
                                }
                                //changing the population count:

                                rPop--;
                                iPop++;
                                break;
                            case 3: //change voter to Right:

                                break;
                            case 4: //change voter to non-Voter:
                                if(vote->get_non_vote()){
                                    vote->set_non_vote(false);
                                    rNon--;    
                                }
                                else{
                                    vote->set_non_vote(true);
                                    rNon++;
                                }
                                break;
                            default:
                                cout << "Error!. PartyChange not 0-4.\n";
                                return -1;
                            
                        }

                    }

                }

                //Now to display the results:
                //Print the changes by displaying the current party population with staunches as well.
                        //Pause after each display and wait for the user to confirm to continue.
                cout << "Left Party Population: " << lPop << ", Staunch: " << lStaunch << ", Non-voters: " << lNon << endl;
                cout << "Independent Party Population: " << iPop << ", Staunch: " << iStaunch << ", Non-voters: " << iNon << endl;
                cout << "Right Party Population: " << rPop << ", Staunch: " << rStaunch << ", Non-voters: " << rNon << endl;
                
                //deciding who is in charge next:
                int lVote = lPop - lNon;
                int iVote = iPop - iNon;
                int rVote = rPop - rNon;
                bool valid = false;

                if(lVote > iVote){ //if Left has more people than Independents:
                    if(lVote > rVote){ //if Left has more people than Right:
                        presidentParty = 1;
                        cout << "The new President is Left!\n";
                    }

                    else if (lVote < rVote){ // if Left has less people than Right:
                        presidentParty = 3;
                        cout << "The new President is Right!\n";
                    }

                    else{ //if Left and Right are tied
                        while(!valid){
                            presidentParty = rand()%3 + 1; //coin flip
                            if(presidentParty == 1){
                                cout << "The new President is Left!\n";
                                valid = true;
                            }

                            else if(presidentParty == 3){
                                cout << "The new President is Right!\n";
                                valid = true;

                            }

                        }
                        valid = false;
                    }

                }

                    else if(lVote < iVote){ // if Left has less people than Indpendent:
                        if(iVote > rVote){ //if Independent has more people than Right:
                            presidentParty = 2;
                            cout << "The new President is Independent!\n";
                        }

                        else if (iVote < rVote){ // if Independent has less people than Right:
                            presidentParty = 3;
                            cout << "The new President is Right!\n";
                        }

                        else{ //if Independent and Right are tied
                            while(!valid){
                                presidentParty = rand()%3 + 1; //coin flip
                                if(presidentParty == 2){
                                    cout << "The new President is Independent!\n";
                                    valid = true;
                                }

                                else if(presidentParty == 3){
                                    cout << "The new President is Right!\n";
                                    valid = true;

                                }

                            }
                        valid = false;
                        }
                    }
                    else{//If Left and Independent are tied:
                        

                        if (lVote < rVote){ // if Left has less people than Right:
                            presidentParty = 3;
                            cout << "The new President is Right!\n";
                        }

                        else{ //if Left and Right are tied
                            while(!valid){
                                presidentParty = rand()%3 + 1; //coin flip
                                if(presidentParty == 1){
                                    cout << "The new President is Left!\n";
                                    valid = true;
                                }

                                else if(presidentParty == 2){
                                    cout << "The new President is Independent!\n";
                                    valid = true;
                                }

                                else if(presidentParty == 3){
                                    cout << "The new President is Right!\n";
                                    valid = true;

                                }

                            }
                            valid = false;
                        }


                    }

                    //Confirm to continue:
                    while(!valid){
                        cout << "Continue? (y/n): ";
                        cin >> confirm;

                        if(cin.fail()){
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "Invalid input. try again.\n";
                        }
                        else if(confirm == 'y' || confirm == 'Y'){
                            valid = true;
                            cout << "Continuing ... \n";
                        }
                        else if (confirm == 'n' || confirm == 'N'){
                            valid = true;
                            cout << "Closing program ...\n";
                            exit;
                        }
                        else{
                            cout << "Error. Not y or n. Try again.\n";
                        }
                    }

                }
                
                

                
                    

                    


     
    
    //end of main function.
}



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


    while(true){
        prob = (rand()%100) + change;
        if(prob < 5){ // become staunch (0)
            return newParty;
        }
        else if(prob < 20){ // stay in party (party)
            newParty = party;
            return newParty;
        }
        else if(prob < 95){ //chance to change party (1-3)
            newParty = (rand()%3) + 1;
            return newParty;
        }
        else if(prob >= 95){// become non-voter (4)
            newParty = 4;
            return newParty;
        }
    }
    

    
}