#pragma one
#include <boost/program_options.hpp>

class CliOptions
{
public:
	CliOptions();
	CliOptions(int ac, char **av);
	std::string getUser() const {return m_user;}
	std::string getPassword() const {return m_password;}
	std::string getDatabase() const {return m_databasename;}
private:
	// Переменные, необходимые для работы boost:program_options
	boost::program_options::options_description desc;
	boost::program_options::positional_options_description pd;
	boost::program_options::variables_map vm;
	//**********************************************************
	// Приватные члены, хранящие значения, полученных из командной
	// строки опций.
	std::string m_typeserver;
	std::string m_user;
	std::string m_password;
	std::string m_databasename;
};

