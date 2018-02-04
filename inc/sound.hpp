//
//  sound.hpp
//  BigBen
//
//  Created by Guillaume Scigala on 04/02/2018.
//  Copyright © 2018 Silence. All rights reserved.
//

#ifndef sound_hpp
#define sound_hpp

#include <string>

class Sound
{
public:
    Sound(std::string type, int level);
    
    void playHour(int hours);
    void playOneQuarter(void);
    void playHalf(void);
    void playThreeQuarter(void);
    
private:
    
    std::string mType;
    int mLevel;
    
    void playStrike(void);
    void play(std::string path);
    
};

#endif /* sound_hpp */
