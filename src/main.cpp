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
#include "sound.hpp"
#include "clock.hpp"

#define UNUSED(identifier) (void)identifier

namespace logging = boost::log;
using namespace boost::asio;
namespace
{
    const size_t ERROR_IN_COMMAND_LINE = 1;
    const size_t SUCCESS = 0;
    const size_t ERROR_UNHANDLED_EXCEPTION = 2;
    
} // namespace

int main(int argc, const char * argv[]) {
    
    try
    {
        /** Define and parse the program options
         */
        namespace po = boost::program_options;
        po::options_description desc("Options");
        desc.add_options()
        ("path,p", po::value<std::string>()->required(), "[string] set clock ressources path")
        ("volume,v", po::value<int>()->required(), "[int] set sound volume")
        ("debug,d", "display debug log")
        ("trace,t", "display trace log")
        ("help,h", "print help messages");
        
        po::variables_map vm;
        try
        {
            po::store(po::parse_command_line(argc, argv, desc), vm);
            
            /** --help option
             */
            if(vm.count("help"))
            {
                BOOST_LOG_TRIVIAL(info) << "Connected clock program";
                BOOST_LOG_TRIVIAL(info) <<  desc;
                return SUCCESS;
            }
            
            po::notify(vm); // throws on error, so do after help in case
            // there are any problems
        }
        
        catch(po::error& e)
        {
            BOOST_LOG_TRIVIAL(error) << "ERROR: " << e.what();
            BOOST_LOG_TRIVIAL(error) << desc;
            return ERROR_IN_COMMAND_LINE;
        }

        // Set log level
        if(vm.count("trace"))
        {
            logging::core::get()->set_filter(
                logging::trivial::severity >= logging::trivial::trace
                );
        }
        else if(vm.count("debug"))
        {
            logging::core::get()->set_filter(
                logging::trivial::severity >= logging::trivial::debug
                );
        }
        else
        {
            logging::core::get()->set_filter(
                logging::trivial::severity >= logging::trivial::info
                );
        }
        
        Sound sound = Sound(vm["path"].as<std::string>(), vm["volume"].as<int>());
        
        io_service io;
        deadline_timer timer(io);
        Clock clock = Clock(sound, timer);
        UNUSED(clock);

        BOOST_LOG_TRIVIAL(info) << "The connected clock has started !";
        
        io.run();
    }
    catch(std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << "Unhandled Exception reached the top of main: "
        << e.what() << ", application will now exit";
        return ERROR_UNHANDLED_EXCEPTION;
    }
    
    return SUCCESS;
}

