#include "player.h"

Player::Player() : id{0}, name{}, score{0}, numTags{0}
{}

Player::Player(int id, String name) : id{id}, name{name}, score{0}, numTags{0}
{}

Player::Player(int id, const char* name) : id{id}, name{String(name)}, score{0}, numTags{0}{}


/**
 * @return integer ID of player
 */
int Player::getId() const
{
    return id;
}

/**
 * @param value to set the player's ID to
 */
void Player::setId(int value)
{
    id = value;
}


/**
 * @return String player's name
 */
String Player::getName() const
{
    return name;
}

/**
 * @param value to set the Player's name
 */
void Player::setName(const String& value)
{
    name = value;
}

/**
 * @return number of tags by a Player
 */
int Player::getNumTags() const
{
    return numTags;
}

/**
 * @param value to set the number of tags to
 */
void Player::setNumTags(int value)
{
    numTags = value;
}

/**
 * @return the individual player's score
 */
int Player::getScore() const
{
    return score;
}

/**
 * @param value to set score
 */
void Player::setScore(int value)
{
    score = value;
}

std::ostream& operator<<(std::ostream& o, const Player& s)
{
    o << s.id << " " << s.name << " - " << s.numTags;
    return o;
}

/**
 * operator> overload the compares the number of TAGS
 * that a player has, then compares the name
 *
 * @param p - the player to compare against
 * @return true if greater than the other player, false if not
 */
bool Player::operator>(const Player& p)
{
    if(numTags == p.getNumTags())
        return name > p.getName();
    return numTags > p.getNumTags();
}

/**
 * operator< overload the compares the number of TAGS
 * that a player has, then compares the name
 *
 * @param p - the player to compare against
 * @return true if less than the other player, false if not
 */
bool Player::operator<(const Player& p)
{
    if(numTags == p.getNumTags())
        return name < p.getName();
    return numTags < p.getNumTags();
}
