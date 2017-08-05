#include "match.h"
/**
 * @return vector of Tag objects
 */
Vector<Tag> Match::getTags() const
{
    return tags;
}

/**
 * @param value - the Vector to set the tags variable
 */
void Match::setTags(const Vector<Tag>& value)
{
    tags = value;
}

/**
 * Finds the number of tags that a player has a certain player, using
 * the tagger ID number as the reference
 *
 * @param tagger - the tagger ID to find in the match file
 * @return number of tags that the player has
 */
int Match::getNumTags(int tagger)
{
    int s = tags.size();
    int count = 0;
    for(int i{}; i < s; i++)
    {
        if(tags.at(i).getTaggerID() == tagger)
        {
            count ++;
        }
    }
    return count;
}

/**
 * Finds the number of tags that a player has against a player, using
 * the tagger ID number and tagged ID number as references
 *
 * @param tagger - the tagger ID to find in the match file
 * @param tagged - the ID of the person who was tagged
 * @return number of tags that the player has
 */
int Match::getNumTags(int tagger, int tagged)
{
    int s = tags.size();
    int count = 0;
    for(int i{}; i < s; i++)
    {
        Tag tg = tags.at(i);
        if(tg.getTaggerID() == tagger && tg.getTaggedID() == tagged)
        {
            count ++;
        }
    }
    return count;
}


/**
 * Uses the Tag data and finds the team's score by cross referencing
 * Tag objects' tagger IDs with the player IDs in the Team objects
 * @param t - the Team object to cross reference
 * @return the team's score
 */
int Match::getTeamScore(Team t)
{
    int s = t.getNumPlayers();
    Vector<Player> p = t.getPlayers();
    int count = 0;

    for(int i{}; i < num_tags; i++)
    {
        for(int j{}; j < s; j++)
        {
            if(p.at(j).getId() == tags.at(i).getTaggerID())
            {
                count += tags.at(i).getScore();
            }
        }
    }
    return count;
}

/**
 * Gets the player's score based on their ID
 * by iterating through the list and getting
 * the score from the Tag object
 *
 * @param id - the player's ID
 * @return player's score
 */
int Match::getPlayerScore(int id)
{
    int s = 0;
    for(int i{}; i < num_tags; i++)
    {
        Tag& t = tags.at(i);
        if(t.getTaggerID() == id)
        {
            s += t.getScore();
        }
    }
    return s;
}

/**
 * Default constructor, but does nothing because
 * a file name is needed
 */
Match::Match() : tags{}, num_tags{0}
{}

/**
 * Constructor with ifstream
 * @param m - the ifstream to pull data from
 */
Match::Match(ifstream& m)
{
    m >> num_tags;  //the total number of tags in the game
    parseLines(m);  //parse the next lines into Tag objects
}

/**
 * Parses the lines from the ifstream into Tag
 * objects based on the number of tags found in
 * the Match file
 * @param m - the ifstream to pull data from
 */
void Match::parseLines(ifstream& m)
{

    for(int i{}; i < num_tags && !m.eof(); i++)
    {
        int tr, td, time, l;
        m >> tr >> td >> time >> l;
        tags.pushBack(Tag(tr, td, l));
    }
}


