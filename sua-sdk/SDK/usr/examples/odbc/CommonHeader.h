#include <interix/mixedmode.h>

#include <stdio.h>
#include <odbc/sql.h>
#include <odbc/sqlext.h>
#include <odbc/sqltypes.h>
#include <odbc/odbcss.h>
#include <stdlib.h>
#include <odbc/odbcinst.h>
#include <errno.h>
#define NAME_LEN 50

#define MYFAIL -1
#define MYPASS 0

/* displays the last error message */
void ShowError(SQLHSTMT hstmt,SQLSMALLINT HandleType)
{
	SQLCHAR       SqlState[6], SQLStmt[100], Msg[SQL_MAX_MESSAGE_LENGTH];
	SQLINTEGER    NativeError;
	SQLSMALLINT   i, MsgLen;
	SQLRETURN     rc1, rc2;
	i = 1;
	while ((rc2 = SQLGetDiagRec(HandleType, hstmt, i, SqlState, &NativeError,Msg, sizeof(Msg), &MsgLen)) != SQL_NO_DATA) 
	{
		printf("SqlState %s,NativeError %d ,Msg %s \n",SqlState,NativeError,Msg);
		i++;
	}
}
/* establishes the connection with the DB */
int ConnectToDB(char *DSN,char * UserId ,char *passwd,SQLHENV *henv,SQLHDBC *hdbc)
{
	SQLRETURN      retcode;

	if(SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, henv))
	{
		printf("SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv) failed\n");
		return MYFAIL;
	}
	if(SQLSetEnvAttr(*henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3,0))
	{
		printf("SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3,0) failed\n");
		return MYFAIL;
	}
	if(SQLAllocHandle(SQL_HANDLE_DBC, *henv, hdbc))
	{
		printf("SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc) failed\n");
		return MYFAIL;
	}


	if((retcode =SQLSetConnectAttr(*hdbc, (SQLINTEGER)SQL_ATTR_ODBC_CURSORS,(SQLPOINTER)SQL_CUR_USE_IF_NEEDED,0))!=SQL_SUCCESS)//SQL_CUR_USE_ODBC
	{
		printf("Error In Using Cursor Library\n");
		return MYFAIL;
	}
	//Setting Connection Attribute
	if((retcode=SQLSetConnectAttr(*hdbc,(SQLINTEGER)SQL_LOGIN_TIMEOUT, (SQLPOINTER  )5, 0))!=SQL_SUCCESS)
	{
		printf( "Error In Setting The Connection Handler\n");
		return MYFAIL;
	}
	//Connecting to SQL-SERVER
	if((retcode =SQLConnect(*hdbc,(SQLCHAR *)DSN,SQL_NTS, (SQLCHAR *) UserId,SQL_NTS,(SQLCHAR *) passwd,SQL_NTS ))!=SQL_SUCCESS_WITH_INFO)
	{
		printf( "Error In Connecting To The SQLSERVER \n");
		return MYFAIL;
	}
	return MYPASS;

}
void CloseConnection(SQLHENV henv,SQLHDBC hdbc)
{
	//Free the Connection Handle														
	if( hdbc)
		SQLFreeHandle( SQL_HANDLE_DBC, hdbc );	
	//Free the Environment  Handle
	if( henv)
		SQLFreeHandle( SQL_HANDLE_ENV, henv );
}

