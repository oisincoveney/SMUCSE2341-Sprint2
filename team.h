#ifndef TEAM_H
#define TEAM_H

#include "dsstring.h"
#include "Vector.h"
#include "player.h"
#include <fstream>


/**
 * The Team class contains the attributes for a team of players
 * playing in a laser tag game, as a part of the Laser Tag
 * project in CSE 2341.
 *
 * The Team class holds four attributes: the team name, the number
 * of players, a list of the players, and the team's score. While the
 * first three variables are initialized at construction, the score
 * is not initialized until a Match object is created and uses the
 * function getTeamScore() to set the team's score based on the
 * match file's specifications.
 *
*/
class Team
{
    private:

        String teamName;
        int numPlayers;
        Vector<Player> players;
        int score;

    public:

        //Constructor
        Team();                // the Team initialzes to all zeroes
                               // and an empty list
        Team(ifstream& t);     // the ifstream constructor initializes the
                               // first three variables

        //Getters and setters
        String getTeamName() const;
        void setTeamName(const String& value);

        int getNumPlayers() const;
        void setNumPlayers(int value);

        Vector<Player>& getPlayers();
        void setPlayers(const Vector<Player>& value);

        int getScore() const;
        void setScore(int value);

        //searches the player list for a name based on ID
        String getPlayerName(int id);

        //Calls the insertion_sort() function in Vector
        //based on the comparison operators in Player
        void sort();

}; //end class Team

#endif // TEAM_H
