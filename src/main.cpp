#include <iostream>
#include <string>
#include "cli_options.hpp"
#include "connection.hpp"

int main(int argc, char **argv)
{
	std::cout << "Starting...\n";
	CliOptions options(argc, argv);
	std::cout << "User: " << options.getUser() << "; Password: " << options.getPassword() << std::endl;
	std::cout << "Database = " << options.getDatabase() << std::endl;
	std::string SQL;
	std::getline(std::cin, SQL);
	std::cout << "SQL: " << SQL << std::endl;
	socibd::Connection con;
}

