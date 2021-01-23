/******************************************************************************
 **  Copyright (c) 2018, Connected Clock. All Rights Reserved.
 **
 **  This file is part of Connected Clock.
 **
 **  Connected Clock is free software; you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation; either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  Connected Clock is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with Foobar; if not, write to the Free Software
 **  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 **
 ******************************************************************************/

#include "boost/program_options.hpp"
#include <boost/asio.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>

#include "cuckoo.h"
#include "westminster.h"

#define UNUSED(identifier) (void)identifier

namespace logging = boost::log;
using namespace boost::asio;
namespace
{
const size_t ERROR_IN_COMMAND_LINE = 1;
const size_t SUCCESS = 0;
const size_t ERROR_UNHANDLED_EXCEPTION = 2;

} // namespace

int main(int argc, const char *argv[])
{
	try {
		/* Define and parse the program options */
		namespace po = boost::program_options;
		po::options_description desc("Options");
		desc.add_options()("path,p",
				   po::value<std::string>()->required(),
				   "[string] set clock ressources path")(
			"volume,v", po::value<int>()->required(),
			"[int] set sound volume in percent")(
			"clock,c", po::value<std::string>()->required(),
			"[string] set clock type (westminster)")(
			"no-tick,n",
			"disable second tick")("debug,d", "display debug log")(
			"trace,t", "display trace log")("help,h",
							"print help messages");

		po::variables_map vm;
		try {
			po::store(po::parse_command_line(argc, argv, desc), vm);

			/** --help option */
			if (vm.count("help")) {
				BOOST_LOG_TRIVIAL(info)
					<< "Connected clock program";
				BOOST_LOG_TRIVIAL(info) << desc;
				return SUCCESS;
			}

			if ((vm["clock"].as<std::string>() != "cuckoo")
				&& (vm["clock"].as<std::string>() != "westminster")) {
				throw std::invalid_argument(
					"Unknown clock type");
			}

			/* throws on error, so do after help in case
			               there are any problems */
			po::notify(vm);
		}

		catch (po::error &e) {
			BOOST_LOG_TRIVIAL(error) << "ERROR: " << e.what();
			BOOST_LOG_TRIVIAL(error) << desc;
			return ERROR_IN_COMMAND_LINE;
		}

		// Set log level
		if (vm.count("trace")) {
			logging::core::get()->set_filter(
				logging::trivial::severity >=
				logging::trivial::trace);
		} else if (vm.count("debug")) {
			logging::core::get()->set_filter(
				logging::trivial::severity >=
				logging::trivial::debug);
		} else {
			logging::core::get()->set_filter(
				logging::trivial::severity >=
				logging::trivial::info);
		}

		Sound sound = Sound(vm["path"].as<std::string>(),
				    vm["volume"].as<int>());

		io_service io;
		deadline_timer timer(io);

		Clock *clock;
		if (vm["clock"].as<std::string>() == "westminster") {
			clock = new Westminster(
				sound, !(vm.count("no-tick") >= 1), timer);
		} else if (vm["clock"].as<std::string>() == "cuckoo") {
			clock = new Cuckoo(sound, !(vm.count("no-tick") >= 1),
					   timer);
		}
		UNUSED(clock);

		BOOST_LOG_TRIVIAL(info) << "The connected clock has started !";

		io.run();
	} catch (std::exception &e) {
		BOOST_LOG_TRIVIAL(error)
			<< "Unhandled Exception reached the top of main: "
			<< e.what() << ", application will now exit";
		return ERROR_UNHANDLED_EXCEPTION;
	}

	return SUCCESS;
}
