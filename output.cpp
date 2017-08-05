#include "output.h"
#include <fstream>
#include "tag.h"
#include "player.h"
#include "match.h"
#include "team.h"
#include <cstring>


/**
 * Default Constructor - it will always throw an exception
 * because files are needed to succeed with output
 */
Output::Output() : m{}, a{}, b{}, o{}
{
    throw std::invalid_argument("Output class requires file I/O to function");
}

/**
 * Constructor with four parameters
 *
 * This constructor facilitates the opening and closing of the input and
 * output files, and initializes the data into Match and Tean objects to
 * be used in outputting the desired data.
 *
 * @param tA - a team file containing player data
 * @param tB - a team file containing player data
 * @param match - the match file containing tag data
 * @param output_char - the file to output the data to
 */
Output::Output(char* tA, char* tB, char* match, char* output_char)
{
    ifstream match_stream, teamA, teamB;

    match_stream.open(match);
    teamA.open(tA);
    teamB.open(tB);
    o.open(output_char);

    m = Match(match_stream);
    a = Team(teamA);
    b = Team(teamB);


    if(a.getTeamName() > b.getTeamName())   //places the teams in alphabetical order so
    {                                       //no comparisons need to happen later
        Team place_holder = a;
        a = b;
        b = place_holder;
    }


    a.setScore(m.getTeamScore(a));          //Gets scores for the team files
    b.setScore(m.getTeamScore(b));

    match_stream.close();                   //closes the input files because
    teamA.close();                          // the data has been parsed
    teamB.close();

}

/**
 * Prints the data to the output file using the verbosity char*
 * @param verb - the verbosity that should be outputted
 */
void Output::print(char* verb)
{
    if(strcmp(verb, "vlow") == 0)
        low();
    else
    {
        if(strcmp(verb, "vmed") == 0)
            med();
        else
            high();
    }
}

/**
 * low() outputs the team names and scores, as well as the winners
 */
void Output::low()
{
    lowHelper(a);
    lowHelper(b);
    winners();
}

/**
 * lowHelper() outputs the team name and number of points
 * @param t - the team to output
 */
void Output::lowHelper(Team t)
{
    o << t.getTeamName() << ": " << t.getScore() << " points" << endl;
}

/**
 * med() outputs the team's players and number of individual tags,
 * then outputs all of the data that low() outputs
 */
void Output::med()
{
    medGetPlayerTags();

    medHelper(a);
    medHelper(b);

    bestScore(a);
    bestScore(b);

    low();
}

/**
 * medHelper() outputs the team's name and the player's
 * individual tags within the match
 * @param t - the team to access data from
 */
void Output::medHelper(Team t)
{
    o << t.getTeamName() << endl;
    Vector<Player> p = t.getPlayers();
    for(int i{}; i < t.getNumPlayers(); i++)
    {
        Player x = p.at(i);
        o << "\t" << x.getName() << " had a total of " << x.getNumTags() << " tags" << endl;
    }

    o << endl;
}

/**
 * medGetPlayerTags() uses the medGetTagsHelper() to set the score and number of tags
 * for each individual players on a team
 */
void Output::medGetPlayerTags()
{
    medGetTagsHelper(a);
    medGetTagsHelper(b);
}

/**
 * medGetTagsHelper uses a Team reference to set the score and number of tags for
 * each individual player in the team file
 *
 * @param t - the team reference to modify each player
 */
void Output::medGetTagsHelper(Team& t)
{
    Vector<Player>& players = t.getPlayers();
    for(int i{}; i < players.size(); i++)
    {
        Player& p = players.at(i);
        int id = p.getId();
        p.setNumTags(m.getNumTags(id));
        p.setScore(m.getPlayerScore(id));

    }
    t.sort();
}

/**
 * Outputs the individual with the best score, used for medium verbosity output
 * @param t - the team file to search
 */
void Output::bestScore(Team& t)
{
    Vector<Player> p = t.getPlayers();
    Player best = p.at(0);
    for(int i{1}; i < t.getNumPlayers(); i++)
    {
        if(best.getScore() < p.at(i).getScore())
            best = p.at(i);
    }
    o << "Best score from " << t.getTeamName() << ": ";
    o << best.getName() << " (" << best.getScore() << " points)" << endl;
}

/**
 * high() outputs the players and their tags against the individual players
 * of the opposing team, and outputs the total points of each player
 * and each team. The winner is then presented
 */
void Output::high()
{
    medGetPlayerTags();
    highHelper(a, b);
    highHelper(b, a);
    winners();
}

void Output::highHelper(Team& t, Team& t2)
{
    o << t.getTeamName() << endl;
    Vector<Player> p = t.getPlayers();
    for(int i{}; i < t.getNumPlayers(); i++)
    {
        Player x = p.at(i);
        getCrossTags(x, t2);
        o << "\t" << x.getName() << " had a total of " << x.getNumTags() << " tags" << endl;
    }

    o << "\t";
    lowHelper(t);
    o << endl;

}

/**
 * getCrossTags() outputs the number of times that a certain player of
 * one team tags each member of the opposing team. The function then
 * uses the member ofstream to output the data
 *
 * @param player - the Player who is tagging
 * @param t2 - the team to check the player's tags against
 */
void Output::getCrossTags(Player player, Team& t2)
{
    Vector<Player> p = t2.getPlayers();
    for(int i{}; i < t2.getNumPlayers(); i++)
    {
        Player x = p.at(i);
        o << "\t" << player.getName() << " tagged " << p[i].getName() << " ";
        o << m.getNumTags(player.getId(), p[i].getId()) << " times.";
        o << endl;
    }
}

/**
 * Outputs the winners of the game based on the team's scores
 */
void Output::winners()
{
    o << "Overall winners: ";
    o << ((a.getScore() > b.getScore()) ? a.getTeamName() : b.getTeamName());
    o << endl;
}


/**
 * Destructor - closes the ofstream once the object is done functioning
 * (effectively after print() is called)
 */
Output::~Output()
{
    if(o.is_open())
        o.close();
}
