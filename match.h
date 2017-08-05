#ifndef MATCH_H
#define MATCH_H

#include "tag.h"
#include "Vector.h"
#include "team.h"
#include <iostream>
#include <fstream>

using namespace std;


/**
 *
 * The Match class contains the functionality for working with a match file
 * in the Laser Tag project in CSE 2341. A match file contains 5 attributes
 * distributed across multiple lines, and the functions in the class
 * are used to parse the data. This data is placed into a list of Tag objects,
 * which encapsulate the data in a tag in a laser tag game.
 *
 * The data parsed out in the following manner, using an example match file:
 *
 *      6               <- the number of tags (int num_tags)
 *      6 1 8388 2      <- the next three lines are the same -
 *      3 5 10111 1        1st number: tagger ID
 *      4 2 12123 3        2nd : tagged ID
 *                         3rd : time in ms
 *                         4th : location of the tag
 *
 * This data is encapsulated into a list of Tag objects, and can later be
 * manipulated using the Output class.
 *
 */

class Match
{
    private:

        Vector<Tag> tags;
        int num_tags;

    public:

        // Constructors
        Match();
        Match(ifstream& m);

        // Parses each line of the match file as described
        // in the class description
        void parseLines(ifstream& m);

        //Getter and setter for the tags vector
        Vector<Tag> getTags() const;
        void setTags(const Vector<Tag>& value);

        // Retrieves number of tags based on tagger and tagged IDs
        int getNumTags(int tagger);
        int getNumTags(int tagger, int tagged);

        //Returns a team's score using a Team object's player list
        int getTeamScore(Team t);

        //Returns the player's score
        int getPlayerScore(int id);

};  //end class Match

#endif // MATCH_H
