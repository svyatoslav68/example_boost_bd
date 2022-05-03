#include <string>
#include <iostream>
#include <tuple>
#define SOCI_USE_BOOST
#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>
#include "connection.hpp"

using namespace soci;

namespace socibd {

Connection::Connection()
{
	m_con = new session();
}

Connection::~Connection()
{
	//std::cout << "Begin destructor.\n";
	delete m_con;
	//std::cout << "End destructor.\n";
}

Connection::Connection(const Connection &con)
{
	//std::cout << "Begin copying constructor.\n";
	m_nameBD = con.m_nameBD;
	m_con = con.m_con;
}

void Connection::open(Connection::TypeCBD type_server, const ParametrsBD &con)
{
	switch (type_server){
		case MYSQL_SERVER:
			m_con->open("mysql", "dbname='"+con.nameBD+"' user='"+con.user+
								"'password='"+con.password+"'");
			*m_con << "SET names utf8";
			break;
		case POSTGRES_SERVER:
			m_con->open("postgresql", "dbname='"+con.nameBD+"' user='"+con.user+
								"'password='"+con.password+"'");
			break;
		default:
			;
	}
}

session *Connection::getConnect() const
{
	return m_con;
}

soci::rowset<soci::row> Connection::execute(std::string &SQL)
{
	return m_con->prepare << SQL;
}

boost::tuple<int, std::string, std::string> Connection::getTuple(std::string& SQL)
{
	indicator ind;
	boost::tuple<int, std::string, std::string> result;// {1,2,3};
	//auto [a, b, c] = result;
	//std::tuple<int, std::string, std::string> result2;
	std::cout << SQL << std::endl;
	int result1;
	//session connect("mysql", "dbname='unit' user='slava' password='677183'");
	//boost::tuple<int, std::string, std::string> result1;
	//(*m_con) << SQL, soci::into(result);
	(*m_con) << SQL, into(result, ind);
	return result;
}

} //namespace socibd
