#ifndef TAG_H
#define TAG_H

#include "dsstring.h"
#include <iostream>

/**
 * The Tag class contains the details of a "tag" during
 * a game of laser tag, as a part of the Laser Tag
 * project in CSE 2341.
 *
 * A "tag" consists of four variables: the ID of the tagger,
 * the ID of the person who was tagged, the location ID of the
 * tag, and the score derived from the location.
 *
 * A Tag object is generally used as an object that encapsulates
 * data taken from the match file, and placed in a Vector list
 * that allows for easier accessing and display of data.
 *
*/

class Tag
{
    private:

        int taggerID;
        int taggedID;
        int location;
        int score;


    public:

        //Constructors
        Tag();
        Tag(int, int, int);

        //getters and setters
        int getScore() const;
        void setScore(int value);

        int getLocation() const;
        void setLocation(int value);

        int getTaggedID() const;
        void setTaggedID(int value);

        int getTaggerID() const;
        void setTaggerID(int value);


        int scoreFromLocation(int l);   //Calculates score from location ID

        friend std::ostream& operator<<(std::ostream& o, const Tag& s);

};

#endif // TAG_H
