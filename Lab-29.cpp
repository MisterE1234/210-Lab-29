//COMSC-210|Ethan Aylard|Lab-29
//IDE used: Visual Studio Code

//Include necessary headers for files, data structures, processing, and ect.

//Define a class named Voter:
    //would hold a int party variable with three options (1-3). To represent left, moderate, right.
    //an bool variable to see if the voter is staunch or not.
    //a partial constructor to have a custom party affiliation with staunch set false by default.

//Define a function that would simulate what event[s] would have happend for this voting period and how they affect different voters using a probabilty matrix.
    //Parameters: a voter, and 3 random int variables
    //returns: an integer indicating which party they are a part of now and and if they are staunch.

//Define main function:
    //Initialize a map to store party information, each associated with its different kinds of voters.
    //declare int variables named rPop, lPop, iPop, nonPop, and rStaunch, lStaunch, iStaunch, and nonStaunch.
    
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
                    
    //end of main function.
