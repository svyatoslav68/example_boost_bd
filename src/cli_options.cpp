#include <iostream>
#include "cli_options.hpp"

CliOptions::CliOptions()
{
	namespace po = boost::program_options;
	desc.add_options()
		("help,h", "help message")
		("version,v", "Show version of application")
		("server,s", po::value<std::string>(&m_typeserver)->default_value("postgres"), "Type server (postgres|mysql)")
		("user,u", po::value<std::string>(&m_user), "database username")
		("password,p", po::value<std::string>(&m_password), "database password")
		("database", po::value<std::string>(&m_databasename), "name of database")
	;
	pd.add("database", -1);
}

CliOptions::CliOptions(int ac, char **av):CliOptions()
{
	namespace po = boost::program_options;
	auto parsed = po::command_line_parser(ac, av).options(desc).positional(pd).run();
	po::store(parsed, vm);
	po::notify(vm);
	if (vm.count("help")){
		std::cout << desc;
		std::exit(0);
	}
}


