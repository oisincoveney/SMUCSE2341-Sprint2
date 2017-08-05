#include "tag.h"

/**
 * Default constructor
 */
Tag::Tag() : taggerID{0}, taggedID{0}, location{0}, score{0}
{}

/**
 * Constructor with three parameters
 *
 * @param integer - ID of tagger
 * @param tagged - ID of person who was tagged
 * @param location - a number between 1-4 that describes location of hit
 */
Tag::Tag(int tagger, int tagged, int location) : taggerID{tagger}, taggedID{tagged}, location{location}, score{scoreFromLocation(location)}
{}

/**
 * @return the score associated with the tag location
 */
int Tag::getScore() const
{
    return score;
}

/**
 * @param value to set the score
 */
void Tag::setScore(int value)
{
    score = value;
}

/**
 * @return an integer between 1 & 4 that describes the tag location
 */
int Tag::getLocation() const
{
    return location;
}

/**
 * @param value to set the location, must be from 1-4 or the score
 * will always be 0
 */
void Tag::setLocation(int value)
{
    location = value;
}

/**
 * @return the integer ID of the person who was tagged
 */
int Tag::getTaggedID() const
{
    return taggedID;
}

/**
 * @param value to set the tagged ID
 */
void Tag::setTaggedID(int value)
{
    taggedID = value;
}

/**
 * @return integer of the tagger
 */
int Tag::getTaggerID() const
{
    return taggerID;
}

/**
 * @param value to set the tagger ID to
 */
void Tag::setTaggerID(int value)
{
    taggerID = value;
}

/**
 * Returns the score based on the location given in the parameter
 * @param l - the location of the tag
 * @return a score based on the location
 */
int Tag::scoreFromLocation(int l)
{
    switch(l)
    {
        case 1:
            return 5;
        case 2:
            return 8;
        case 3:
            return 10;
        case 4:
            return 15;
        default:
            return 0;
    }
}

/**
 * Overloaded operator<< gives a short-hand view of the tag
 *
 * General template:
 *
 * (Tagger ID) -> (Tagged ID) at (Location) : (Score) points
 *
 * @param o - the ostream to input data into
 * @param s - the Tag where the data will come from
 * @return the ostream containing the new data from the Tag
 */
std::ostream& operator<<(std::ostream& o, const Tag& s)
{
    o << s.taggerID << "->" << s.taggedID << " at " << s.location << " : " << s.score << " pts";
    return o;
}


