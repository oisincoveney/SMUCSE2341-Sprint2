#ifndef OUTPUT_H
#define OUTPUT_H

#include "match.h"
#include <fstream>
#include <iostream>

using namespace std;

/**
 * The Output class facilitates the input and output of files, and is
 * responsible for encapsulating all the data from the match and team
 * files, and outputting the data in various forms based on the
 * inputted verbosities of "vlow", "vmed", or "vhigh".
 *
 * To achieve this goal, the function contains four member variables -
 * three of these variables originate from the Match and Team classes,
 * to replicate a laser tag scoring system. These objects are then used
 * to display the informtion needed.
 *
 * This class is responsible for achieving the final output for the
 * files in the Laser Tag project in CSE 2341.
 *
 */
class Output
{
    private:

        //Objects that take input files
        Match m;
        Team a;
        Team b;

        //output stream for final output
        ofstream o;

    public:

        //Constructors
        Output();                           //Throws an exception because an
                                            //output requires file names
        Output(char*, char*, char*, char*);


        //Low verbosity
        void low();
        void lowHelper(Team t);


        //Medium Verbosity functions
        void med();
        void medHelper(Team t);
        void medGetPlayerTags();
        void medGetTagsHelper(Team& t);     //sets tags and scores for player

        //High Verbosity Functions
        void high();
        void highHelper(Team& t, Team& t2);
        void getCrossTags(Player player, Team& t2); //gets number of tags
                                                    //for a pair of players
                                                    //on opposing teams


        void winners();                     //prints out winning team
        void print(char* verb);             //control structure for diff. verbosities
        void bestScore(Team& t);            //Gets best player score for the team


        //Destructor
        ~Output();
};

#endif // OUTPUT_H
