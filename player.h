#ifndef PLAYER_H
#define PLAYER_H

#include "dsstring.h"
#include "Vector.h"


/**
 * The Player class contains the details of a player playing
 * in a laser tag game, as a part of the Laser Tag project in
 * CSE 2341.
 *
 * A Player holds four attributes: integers for ID, score, and
 * number of tags, and a String for their name. Only the ID and
 * name are initialized in all three verbosities, since the
 * low verbosity does not require individual player scores or
 * number of tags.
 *
*/

class Player
{
    private:

        int id;
        String name;
        int score, numTags;                  //used only in medium and high verbosity

    public:

        //Constructors
        Player();
        Player(int id, String name);
        Player(int id, const char* name);

        //getters and setters
        int getId() const;
        void setId(int value);

        String getName() const;
        void setName(const String& value);

        int getNumTags() const;
        void setNumTags(int value);

        int getScore() const;
        void setScore(int value);

        //operator<< overload for easier debugging and output
        friend std::ostream& operator<<(std::ostream& o, const Player& s);

        //comparison operators for sorting players in a Vector
        bool operator< (const Player& p);
        bool operator>(const Player& p);


};

#endif // PLAYER_H
