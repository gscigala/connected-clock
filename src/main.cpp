//
//  main.cpp
//  BigBen
//
//  Created by Guillaume Scigala on 03/02/2018.
//  Copyright © 2018 Silence. All rights reserved.
//
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include "boost/program_options.hpp"
#include <boost/asio.hpp>
#include <iostream>
#include "clock.hpp"

namespace logging = boost::log;
using namespace boost::asio;
namespace
{
    const logging::trivial::severity_level LOG_LEVEL = logging::trivial::debug;
    
    const size_t ERROR_IN_COMMAND_LINE = 1;
    const size_t SUCCESS = 0;
    const size_t ERROR_UNHANDLED_EXCEPTION = 2;
    
} // namespace

int main(int argc, const char * argv[]) {

    // Set log level
    logging::core::get()->set_filter
    (
     logging::trivial::severity >= LOG_LEVEL
     );
    
    try
    {
        /** Define and parse the program options
         */
        namespace po = boost::program_options;
        po::options_description desc("Options");
        desc.add_options()
        ("help,h", "print help messages")
        ("type,t", po::value<std::string>()->required(), "set clock type")
        ("level,l", po::value<int>()->required(), "set sound level");
        
        po::variables_map vm;
        try
        {
            po::store(po::parse_command_line(argc, argv, desc), vm);
            
            /** --help option
             */
            if ( vm.count("help")  )
            {
                std::cout << "Basic Command Line Parameter App" << std::endl
                << desc << std::endl;
                return SUCCESS;
            }
            
            po::notify(vm); // throws on error, so do after help in case
            // there are any problems
        }
        
        catch(po::error& e)
        {
            std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
            std::cerr << desc << std::endl;
            return ERROR_IN_COMMAND_LINE;
        }
        
        io_service io;
        deadline_timer timer(io);
        Clock clock = Clock(timer);
        
        io.run();
    }
    catch(std::exception& e)
    {
        std::cerr << "Unhandled Exception reached the top of main: "
        << e.what() << ", application will now exit" << std::endl;
        return ERROR_UNHANDLED_EXCEPTION;
    }
    
    return SUCCESS;
}

