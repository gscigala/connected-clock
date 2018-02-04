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
    Sound(std::string path, int level);
    
    const void playHour(int hours);
    const void playOneQuarter(void);
    const void playHalf(void);
    const void playThreeQuarter(void);
    
private:
    
    const std::string mPath;
    const float mVolume;
    
    const void playStrike(void);
    const void play(std::string path);
    
};

#endif /* sound_hpp */
