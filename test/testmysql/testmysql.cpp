#include <iostream>  
#include <map>  
#include <string>  
#include <memory>  

#include "cppconn/driver.h"  
#include "cppconn/connection.h"  
#include "cppconn/driver.h"  
#include "cppconn/statement.h"  
#include "cppconn/prepared_statement.h"  
#include "cppconn/metadata.h"  
#include "cppconn/exception.h"  

#define DBHOST "tcp://114.215.196.183:3306"  
#define USER "root"  
#define PASSWORD "deduct"  
#define DATABASE "CTI"  

#define NUMOFFSET 100  
#define COLNAME 200  

using namespace std;
using namespace sql;

#pragma comment(lib, "mysqlcppconn.lib")  

void Demo();

int main(int argc, char *argv[])
{
	//CREATE TABLE `City` ( `CityName` varchar(30) DEFAULT NULL ) ENGINE=InnoDB DEFAULT CHARSET=utf8   
	Demo();
	std::getchar();
	return 0;
}

/* 获取数据库信息 */
static void GetDBMetaData(Connection *dbcon)
{
	if (dbcon->isClosed())
	{
		throw runtime_error("DatabaseMetaData FAILURE - database connection closed");
	}

	cout << "Database Metadata" << endl;
	cout << "-----------------" << endl;

	cout << boolalpha;

	/* The following commented statement won't work with Connector/C++ 1.0.5 and later */
	//auto_ptr < DatabaseMetaData > dbcon_meta (dbcon->getMetaData());  

	DatabaseMetaData *dbcon_meta = dbcon->getMetaData();

	cout << "Database Product Name: " << dbcon_meta->getDatabaseProductName() << endl;
	cout << "Database Product Version: " << dbcon_meta->getDatabaseProductVersion().c_str() << endl;
	cout << "Database User Name: " << dbcon_meta->getUserName().c_str() << endl << endl;

	cout << "Driver name: " << dbcon_meta->getDriverName() << endl;
	cout << "Driver version: " << dbcon_meta->getDriverVersion() << endl << endl;

	cout << "Database in Read-Only Mode?: " << dbcon_meta->isReadOnly() << endl;
	cout << "Supports Transactions?: " << dbcon_meta->supportsTransactions() << endl;
	cout << "Supports DML Transactions only?: " << dbcon_meta->supportsDataManipulationTransactionsOnly() << endl;
	cout << "Supports Batch Updates?: " << dbcon_meta->supportsBatchUpdates() << endl;
	cout << "Supports Outer Joins?: " << dbcon_meta->supportsOuterJoins() << endl;
	cout << "Supports Multiple Transactions?: " << dbcon_meta->supportsMultipleTransactions() << endl;
	cout << "Supports Named Parameters?: " << dbcon_meta->supportsNamedParameters() << endl;
	cout << "Supports Statement Pooling?: " << dbcon_meta->supportsStatementPooling() << endl;
	cout << "Supports Stored Procedures?: " << dbcon_meta->supportsStoredProcedures() << endl;
	cout << "Supports Union?: " << dbcon_meta->supportsUnion() << endl << endl;

	cout << "Maximum Connections: " << dbcon_meta->getMaxConnections() << endl;
	cout << "Maximum Columns per Table: " << dbcon_meta->getMaxColumnsInTable() << endl;
	cout << "Maximum Columns per Index: " << dbcon_meta->getMaxColumnsInIndex() << endl;
	cout << "Maximum Row Size per Table: " << dbcon_meta->getMaxRowSize() << " bytes" << endl;

	cout << "Database schemas: " << endl;

	auto_ptr < ResultSet > rs(dbcon_meta->getSchemas());

	cout << "Total number of schemas = " << rs->rowsCount() << endl;
	cout << endl;

	int row = 1;

	while (rs->next()) {
		cout << "/t" << row << ". " << rs->getString("TABLE_SCHEM") << endl;
		++row;
	} // while  

	cout << endl << endl;
}

/* 获取结果集信息 */
static void GetResultDataMetaBata(ResultSet *rs)
{

	if (rs->rowsCount() == 0)
	{
		throw runtime_error("ResultSetMetaData FAILURE - no records in the result set");
	}

	cout << "ResultSet Metadata" << endl;
	cout << "------------------" << endl;

	/* The following commented statement won't work with Connector/C++ 1.0.5 and later */
	//auto_ptr < ResultSetMetaData > res_meta ( rs -> getMetaData() );  

	ResultSetMetaData *res_meta = rs->getMetaData();

	int numcols = res_meta->getColumnCount();
	cout << "/nNumber of columns in the result set = " << numcols << endl << endl;

	cout.width(20);
	cout << "Column Name/Label";
	cout.width(20);
	cout << "Column Type";
	cout.width(20);
	cout << "Column Size" << endl;

	for (int i = 0; i < numcols; ++i)
	{
		cout.width(20);
		cout << res_meta->getColumnLabel(i + 1);
		cout.width(20);
		cout << res_meta->getColumnTypeName(i + 1).c_str();
		cout.width(20);
		cout << res_meta->getColumnDisplaySize(i + 1) << endl << endl;
	}

	cout << "/nColumn \"" << res_meta -> getColumnLabel(1).c_str();  
		cout << "\" belongs to the Table : \"" << res_meta->getTableName(1).c_str();
	cout << "\" which belongs to the Schema : \"" << res_meta->getSchemaName(1).c_str() << "\"" << endl << endl;  
}

/* 打印结果集中的数据 */
static void RetrieveDataAndPrint(ResultSet *rs, int type, int colidx, string colname)
{

	/* retrieve the row count in the result set */
	cout << "/nRetrieved " << rs->rowsCount() << " row(s)." << endl;

	cout << "/nCityName" << endl;
	cout << "--------" << endl;

	/* fetch the data : retrieve all the rows in the result set */
	while (rs->next())
	{
		if (type == NUMOFFSET)
		{
			cout << rs->getString(colidx).c_str() << endl;
		}
		else if (type == COLNAME)
		{
			cout << rs->getString(colname).c_str() << endl;
		} // if-else  
	} // while  

	cout << endl;
}

void Demo()
{

	Driver * driver = get_driver_instance();
	Connection *con;
	Statement *stmt;
	ResultSet *res;
	PreparedStatement *prep_stmt;
	Savepoint *savept;

	int updatecount = 0;

	/* initiate url, user, password and database variables */
	string url(DBHOST);
	const string user(USER);
	const string password(PASSWORD);
	const string database(DATABASE);

	try
	{
		//driver = get_mysql_driver_instance();

		/* create a database connection using the Driver */
		con = driver->connect(url, user, password);

		/* alternate syntax using auto_ptr to create the db connection */
		//auto_ptr  con (driver -> connect(url, user, password));  

		/* turn off the autocommit */
		con->setAutoCommit(0);

		cout << "\nDatabase connection/'s autocommit mode = " << con->getAutoCommit() << endl;

		/* select appropriate database schema */
		con->setSchema(database.c_str());

		/* retrieve and display the database metadata */
		GetDBMetaData(con);

		/* create a statement object */
		stmt = con->createStatement();

		cout << "Executing the Query: \"SELECT * FROM City \" .." << endl;

		/* run a query which returns exactly one result set */
		res = stmt->executeQuery("SELECT * FROM City");

		cout << "Retrieving the result set .." << endl;

		/* retrieve the data from the result set and display on stdout */
		RetrieveDataAndPrint(res, NUMOFFSET, 1, string("CityName"));

		/* retrieve and display the result set metadata */
		GetResultDataMetaBata(res);

		cout << "Demonstrating Prepared Statements .. " << endl << endl;

		/* insert couple of rows of data into City table using Prepared Statements */
		prep_stmt = con->prepareStatement("INSERT INTO City (CityName) VALUES (?)");

		cout << "/tInserting \"London, UK \" into the table, City .." << endl;

		prep_stmt->setString(1, "London, UK");
		updatecount = prep_stmt->executeUpdate();

		cout << "/tCreating a save point \"SAVEPT1 \" .." << endl;
		savept = con->setSavepoint("SAVEPT1");

		cout << "/tInserting \"Paris, France \" into the table, City .." << endl;

		prep_stmt->setString(1, "Paris, France");
		updatecount = prep_stmt->executeUpdate();

		cout << "/tRolling back until the last save point \"SAVEPT1 \" .." << endl;
		con->rollback(savept);
		con->releaseSavepoint(savept);

		cout << "/tCommitting outstanding updates to the database .." << endl;
		con->commit();

		cout << "/nQuerying the City table again .." << endl;

		/* re-use result set object */
		res = NULL;
		res = stmt->executeQuery("SELECT * FROM City");

		/* retrieve the data from the result set and display on stdout */
		RetrieveDataAndPrint(res, COLNAME, 1, string("CityName"));

		cout << "Cleaning up the resources .." << endl;

		/* Clean up */
		delete res;
		delete stmt;
		delete prep_stmt;
		con->close();
		delete con;

	}
	catch (SQLException &e) {
		cout << "ERROR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << ")" << endl;

		if (e.getErrorCode() == 1047) {
			/*
			Error: 1047 SQLSTATE: 08S01 (ER_UNKNOWN_COM_ERROR)
			Message: Unknown command
			*/
			cout << "/nYour server does not seem to support Prepared Statements at all. ";
			cout << "Perhaps MYSQL < 4.1?" << endl;
		}

		return;
	}
	catch (std::runtime_error &e) {
		cout << "ERROR: " << e.what() << endl;

		return;
	}

	return;
}