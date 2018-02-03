//
//  main.cpp
//  BigBen
//
//  Created by Guillaume Scigala on 03/02/2018.
//  Copyright © 2018 Silence. All rights reserved.
//

#include <boost/asio.hpp>
#include "clock.hpp"

int main(int argc, const char * argv[]) {
    
    boost::asio::io_service io;
    boost::asio::deadline_timer timer(io);
    Clock clock = Clock(timer);
    
    io.run();
    
    return 0;
}

