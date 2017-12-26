#include <stdio.h>
#include "CommonHeader.h"

#define ROWS 3
#define NEWBALANCEVALUE 2000
#define TIMESTOSQLFETCHSCROLL 5
#define SQLTEXTLEN 1024

/* buffers for inserting values into the table */
#define INPUTCOUNT 9
int accno_array[]={1,2,3,4,5,6,7,8,9};
float bal_array[]={1000,2000,3000,4000,5000,6001,7000,800,9000};


SQLRETURN  CreateAndFillTables(SQLHENV henv,SQLHDBC hdbc)
{	
	SQLRETURN      retcode;
	SQLINTEGER     ACCOUNT_IDArray[ROWS];
	SQLINTEGER     ACCOUNT_IDIndArray[ROWS];
	SQLINTEGER     BalanceArray[ROWS];
	SQLINTEGER     BalanceIndArray[ROWS];
	SQLUSMALLINT   RowStatusArray[ROWS], RowNum;
	SQLHSTMT       hstmt;
	SQLCHAR		   cursorName[NAME_LEN];
	SQLINTEGER     cursorLen;
	SQLINTEGER	   NewBalance=NEWBALANCEVALUE;
	SQLINTEGER	   NewBalanceInd;
	char SQL_Text[SQLTEXTLEN];
	int CursorTypeValue = 0;
	int i=0,k=0;

	if(SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt)!=0)
	{
		printf("Error In Setting The Connection Handler\n");
		return MYFAIL;
	}
	retcode=SQLSetStmtAttr(hstmt, (SQLINTEGER)SQL_ATTR_CONCURRENCY, (SQLPOINTER)SQL_CONCUR_VALUES,0);
	if(retcode== SQL_ERROR)
	{
		return MYFAIL;
	}
	else if(retcode==SQL_SUCCESS_WITH_INFO)
	{
		printf("Required cursor not set, Cursor type set is %d, but wanted %d \n\n",CursorTypeValue,SQL_CONCUR_VALUES);
	}
	retcode=SQLSetStmtAttr(hstmt, SQL_ATTR_CURSOR_TYPE,(SQLPOINTER)SQL_CURSOR_KEYSET_DRIVEN,0);// , 0);
	if(retcode== SQL_ERROR)
	{
		return MYFAIL;
	}
	else if(retcode==SQL_SUCCESS_WITH_INFO)
	{
		printf("Required cursor not set, Cursor type set is %d, but wanted %d\n\n",CursorTypeValue,SQL_CURSOR_KEYSET_DRIVEN);
	}
	if(SQLSetStmtAttr(hstmt, SQL_ATTR_ROW_BIND_TYPE, SQL_BIND_BY_COLUMN, 0)!=0)
	{
		return MYFAIL;
	}
	if(SQLSetStmtAttr(hstmt, SQL_ATTR_ROW_ARRAY_SIZE, (SQLPOINTER)ROWS, 0)!=0)
	{
		return MYFAIL;
	}
	if(SQLSetStmtAttr(hstmt, SQL_ATTR_ROW_STATUS_PTR, RowStatusArray, 0)!=0)
	{
		return MYFAIL;
	}

	if(SQLSetCursorName(hstmt, "MY_CURSOR", SQL_NTS))
	{
		return MYFAIL;
	}

	// Bind arrays to the ACCOUNT_IDArray
	if(SQLBindCol(hstmt, 1, SQL_C_SLONG, ACCOUNT_IDArray, 0, ACCOUNT_IDIndArray)!=0)
	{
		return MYFAIL;
	}

	
	if(SQLBindCol(hstmt, 2, SQL_C_SLONG, BalanceArray, 0, BalanceIndArray)!=0)
	{
		return MYFAIL;
	}

	// delete the existing table
	SQLExecDirect(hstmt, "drop table accounts", SQL_NTS);// ignore errors if any

	/* create the table accounts */
	if(SQLExecDirect(hstmt, "create table accounts(account_id  int not null unique,bal decimal(11,2))", SQL_NTS)!=0)
	{
		return MYFAIL;
	}

	/* insert the values in the table*/
	for(i=0;i<INPUTCOUNT;i++)
	{
		sprintf(SQL_Text,"insert into accounts values (%d,%f)",accno_array[i],bal_array[i]);
		if(SQLExecDirect(hstmt, SQL_Text, SQL_NTS)!=0)
		{
			return MYFAIL;
		}
	}


	// Execute a statement to retrieve rows from the Customers table.
	if(SQLExecDirect(hstmt, "select * from ACCOUNTS", SQL_NTS)!=0)
	{
		return MYFAIL;
	}


	// Fetch and display the rows, from the table
	while(1)
	{
		if(SQLFetchScroll(hstmt, SQL_FETCH_NEXT, 0))
			break;
		for(k=0;k<ROWS;k++)
		{
			printf("ACCOUNT_ID: %d Balance: %d \n",ACCOUNT_IDArray[k],BalanceArray[k]);
		}
	}

	SQLCloseCursor(hstmt);
	return MYPASS;
FAILED:
	SQLCloseCursor(hstmt);
	return MYFAIL;
}


int main(int argc, char **argv)
{
	char dsn[256] 	 = "ODBC-TEST";
	char user[256] 	 = "sa";
	char passwd[256] = "111_aaa";
	SQLHENV henv;
	SQLHDBC hdbc;

	if (argc > 1)
	{
		strcpy(dsn, argv[1]);
	}
	if(argc > 2)
	{
		strcpy(user, argv[2]);
	}
	if(argc > 3)
	{
		strcpy(passwd, argv[3]);
	}

	if(MYFAIL == ConnectToDB(dsn, user, passwd, &henv, &hdbc))
	{
		printf("Could not establish connection\n");
		return 1;
	}

	CreateAndFillTables(henv, hdbc);

	return 0;
	
}
