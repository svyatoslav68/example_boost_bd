#pragma once
#define SOCI_USE_BOOST
//#include <mysql.h>
#include <soci/soci.h>
//#include <soci/mysql/soci-mysql.h>

namespace socibd {

class Connection {
public:
	enum TypeCBD{
		MYSQL_SERVER,	
		POSTGRES_SERVER
	};
	struct ParametrsBD {
		std::string nameBD; // название базы данных
		std::string user;	// имя пользователя
		std::string password;	// пароль
	};
	Connection();
	Connection(const Connection &);
	~Connection();
	soci::session *getConnect() const;
	void open(TypeCBD type_server, const ParametrsBD &con);
	soci::rowset<soci::row> execute(std::string &SQL);
	boost::tuple<int, std::string, std::string> getTuple(std::string& SQL);
	template <typename ...T>
	/* Шаблонная функция. Возвращает tuple одной строки запроса SQL
	 * Типы данных определяются из параметров запроса */
	boost::tuple<T ...> getRecord(std::string& SQL){ //, T ...args){
		boost::tuple<T ...> result;//{args...};
		(*m_con) << SQL, soci::into(result);
		return result;
	}
	template <typename T>
	/* Возвращает вектор нулевого столбца запроса SQL. Тип данных
	 * является параметром шаблона метода */
	std::vector<T> getColumn(std::string &SQL){
		soci::rowset<soci::row> result_query = m_con->prepare << SQL;	
		std::vector<T> result;
		for (soci::rowset<soci::row>::const_iterator it = result_query.begin();
								it != result_query.end(); ++it){
			result.push_back((*it).get<T>(0));
		}
		return result;
	}
private:
	soci::session *m_con;
	std::string m_nameBD;
};

} // namespace socibd


