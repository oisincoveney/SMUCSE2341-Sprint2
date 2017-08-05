#include "team.h"
#include "dsstring.h"


/**
 * Default constructor
 */
Team::Team() : teamName{""}, numPlayers{0}, players{}, score{0}
{}

/**
 * Constructor with ifstream parameter
 *
 * This constructor uses the ifstream to
 * place the data into a Player list, team name,
 * and number of players for easier access to data
 *
 * @param t - an ifstream containing team file data
 */
Team::Team(ifstream& t)
{
    t >> teamName;
    t >> numPlayers;
    for(int i{}; i < numPlayers && !t.eof(); i++)
    {
        int id;
        String player;
        t >> id;
        t >> player;
        players.pushBack(Player(id, player.substring(1))); //account for the extra space before each String
    }
}

/**
 * @return String containing the team's name
 */
String Team::getTeamName() const
{
    return teamName;
}

/**
 * @param value to replace the team's name with
 */
void Team::setTeamName(const String& value)
{
    teamName = value;
}

/**
 * @return the number of players on the team
 */
int Team::getNumPlayers() const
{
    return numPlayers;
}

/**
 * @param value to set the number of players to
 */
void Team::setNumPlayers(int value)
{
    numPlayers = value;
}

/**
 * @return a Vector of players on the team
 */
Vector<Player>& Team::getPlayers()
{
    return players;
}

/**
 * @param value to set the player Vector to
 */
void Team::setPlayers(const Vector<Player>& value)
{
    players = value;
}

/**
 * @return the team's score
 */
int Team::getScore() const
{
    return score;
}

/**
 * @param value to set the team's score
 */
void Team::setScore(int value)
{
    score = value;
}


/**
 * Returns the player's name based on the ID in the
 * Player Vector. If the player isn't found, then an
 * exception will be thrown
 *
 * @param id - the player's ID
 * @return a String containing the player's name
 */
String Team::getPlayerName(int id)
{
    for(int i{}; i < numPlayers; i++)
    {
        if(players.at(i).getId() == id)
            return players.at(i).getName();
    }
    throw std::out_of_range("No player name matches with ID : get_player_name in class Team");
}

/**
 * Calls the player Vector's insertion sort function
 * to sort the team by decreasing number of tags.
 * This sorting helps with final output.
 */
void Team::sort()
{
    players.insertionSortHigh();
}




