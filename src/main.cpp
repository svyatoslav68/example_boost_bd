#include <iostream>
#include <string>
#include <boost/tuple/tuple.hpp>
#include "cli_options.hpp"
#include "connection.hpp"

int main(int argc, char **argv)
{
	std::cout << "Starting...\n";
	CliOptions options(argc, argv);
	std::cout << "User: " << options.getUser() << "; Password: " << options.getPassword() << std::endl;
	std::cout << "Database = " << options.getDatabase() << std::endl;
	socibd::Connection con;
	socibd::Connection::ParametrsBD parBD{options.getDatabase(), options.getUser(), options.getPassword()};
	con.open(socibd::Connection::POSTGRES_SERVER, parBD);
	std::string SQL;
	std::getline(std::cin, SQL);
	std::cout << "SQL: " << SQL << std::endl;
	boost::tuple<int, std::string> record = con.getRecord<int, std::string>(SQL);
	std::cout << "0:" << record.get<0>() << "; 1:" << record.get<1>() << std::endl;
}

