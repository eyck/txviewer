package com.minres.scviewer.database.sqlite.db;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.HashMap;

public class SQLiteDatabase implements IDatabase {

	protected String dbFileName;
	
	protected HashMap<String, Object> props;
	
	public SQLiteDatabase(String dbFileName) {
		super();
		this.dbFileName = dbFileName;
		props = new HashMap<String, Object>();
	}

	@Override
	public Connection createConnection() throws SQLException {
        // create a database connection and return it
		return DriverManager.getConnection(getConnectionUrl() );
	}

	@Override
	public String getConnectionUrl() {
        // now we set up a set of fairly basic string variables to use in the body of the code proper
        String sJdbc = "jdbc:sqlite";
        String sDbUrl = sJdbc + ":" + dbFileName;
        // which will produce a legitimate Url for SqlLite JDBC :
        // jdbc:sqlite:hello.db
		return sDbUrl;
	}

	@Override
	public void close(ResultSet resultSet, Statement statement, Connection connection) {
		try {
			if(resultSet!=null) resultSet.close();
			if(statement!=null) statement.close();
			if(connection!=null) connection.close();
		} catch (SQLException e) {}

	}

	@Override
	public void close(PreparedStatement preparedStatement, Connection connection) {
		try {
			preparedStatement.close();
			connection.close();
		} catch (SQLException e) {}
	}

	@Override
	public void setData(String name, Object value){
		props.put(name, value);
	}
	
	@Override
	public Object getData(String name){
		return props.get(name);
	}

}
