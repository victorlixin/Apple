#include "CommonOciCalls.h"

/* Define SQL statements to be used in program. */
text *selStudent = (text *) "SELECT id,name,age FROM student WHERE id = :1";


int main(int argc, char** argv)
{
	/********OCI9i APIs*********/

	OCIEnv *env  = NULL;
	OCIError *errhp = NULL;
	OCISvcCtx *svchp = NULL;
	OCIServer *srvhp = NULL;
	OCIStmt *stmt = NULL;
	OCISession *authp = (OCISession *) 0;
	OCIDefine *defnpp = NULL;
	OCIBind   *bindp = NULL;
	FILE *fd = NULL;
	char *fileName = (char *)argv[1];

	int PassFailFlag = -1;

	char name[NAMELEN]={'\0'};
	int age = 0;
	int id = 1;
	
	time_t tloc1 = 0;
	time_t tloc2 = 0;

	sword status = -1;

	//Initialize the OCI package
	LogBegin((stdout," For Select Query stmts : ociCallsSelectBindPos.\n"));

	if(initHandles(&env,&errhp,&svchp,&srvhp,&stmt,&authp,PRESENTRELEASE,OCI_DEFAULT,0,NULL) != OCI_SUCCESS)
	{
		LogError((stdout," Unable to do initialization of environment.\n"));
		LogFail((stdout));
		LogEnd((stdout," For Select Query stmts : ociCallsSelectBindPos.\n")); 
		exit(EXIT_FAILURE);
	}
	
	if(logOn(getEnvData(USERNAME),getEnvData(PASSWORD),getEnvData(DATABASE_NAME),
			&errhp,&svchp,&srvhp,&authp) != OCI_SUCCESS)
	{
		LogError((stdout," Unable to do initialization of environment.\n"));
		LogFail((stdout));
		LogEnd((stdout," For Select Query stmts : ociCallsSelectBindPos.\n")); 
		exit(EXIT_FAILURE);
	}

	/* Preparing the statement for execution. */
	PassFailFlag = checkError(errhp, OCIStmtPrepare( stmt, errhp,(CONST text *)selStudent,	strlen((const char *)selStudent),
							OCI_NTV_SYNTAX, OCI_DEFAULT ),ERRHND);	

	if(FAIL == PassFailFlag)
	{
		cleanUp(env,srvhp,svchp,authp,errhp);
		LogFail((stdout));
		LogEnd((stdout," For Select Query stmts : ociCallsSelectBindPos.\n"));
		exit(EXIT_FAILURE);
	}

	PassFailFlag = checkError(errhp, OCIBindByPos(stmt,&bindp,errhp,(ub4)1,
							&id,(sb4)sizeof(int),SQLT_INT,NULL,
							NULL,NULL,0,NULL,OCI_DEFAULT),ERRHND);

	if(FAIL == PassFailFlag)
	{
		cleanUp(env,srvhp,svchp,authp,errhp);
		LogFail((stdout));
		LogEnd((stdout," For Select Query stmts : ociCallsSelectBindPos.\n"));
		exit(EXIT_FAILURE);
	}

	//Defining variables which needs to be used for output.*/
	PassFailFlag = checkError(errhp, OCIDefineByPos( stmt, &defnpp, errhp, 1,&id,
						   sizeof(int), SQLT_INT, NULL, 
						   NULL, NULL, OCI_DEFAULT ),ERRHND);

	if(FAIL == PassFailFlag)
	{
		cleanUp(env,srvhp,svchp,authp,errhp);
		LogFail((stdout));
		LogEnd((stdout," For Select Query stmts : ociCallsSelectBindPos.\n"));
		exit(EXIT_FAILURE);
	}

	PassFailFlag = checkError(errhp,OCIDefineByPos( stmt, &defnpp, errhp, 2, name,
						   sizeof(name), SQLT_CHR, NULL, 
						   NULL, NULL, OCI_DEFAULT ),ERRHND);

	if(FAIL == PassFailFlag)
	{
		cleanUp(env,srvhp,svchp,authp,errhp);
		LogFail((stdout));
		LogEnd((stdout," For Select Query stmts : ociCallsSelectBindPos.\n"));
		exit(EXIT_FAILURE);
	}
	PassFailFlag = checkError(errhp,OCIDefineByPos( stmt, &defnpp, errhp, 3, &age,
						   sizeof(int), SQLT_INT, NULL, 
						 NULL, NULL, OCI_DEFAULT ),ERRHND);

	if(FAIL == PassFailFlag)
	{
		cleanUp(env,srvhp,svchp,authp,errhp);
		LogFail((stdout));
		LogEnd((stdout," For Select Query stmts : ociCallsSelectBindPos.\n"));
		exit(EXIT_FAILURE);
	}
	time(&tloc1);
	LogInfo((stdout,"Time before execution = %ld\n",tloc1));

	/* Executing the statement.*/
	PassFailFlag = checkError(errhp, OCIStmtExecute( svchp, stmt, errhp, 0, 0, 
						   (OCISnapshot *)NULL, (OCISnapshot *) NULL,
						   OCI_DEFAULT ),ERRHND);

	if(FAIL == PassFailFlag)
	{
		cleanUp(env,srvhp,svchp,authp,errhp);
		LogFail((stdout));
		LogEnd((stdout," For Select Query stmts : ociCallsSelectBindPos.\n"));
		exit(EXIT_FAILURE);
	}

	time(&tloc2);
	LogInfo((stdout,"Time after execution = %ld & Time taken = %ld\n",tloc2,tloc2-tloc1));
	
	/* Fetching the results of above executed stmt.*/
	status = OCIStmtFetch(stmt, errhp, (ub4) 1, (ub4) OCI_FETCH_NEXT,(ub4) OCI_DEFAULT);
	PassFailFlag = checkError(errhp,status,ERRHND);
	
	if(FAIL == PassFailFlag)
	{
		cleanUp(env,srvhp,svchp,authp,errhp);
		LogFail((stdout));
		LogEnd((stdout," For Select Query stmts : ociCallsSelectBindPos.\n"));
		exit(EXIT_FAILURE);
	}

	fd = getFileDescriptor(fileName,"a");
	if(fd == NULL)
		fd = stdout;
		
	LogBegin((fd,"Result log for ociCallsSelectbindPos begin.\n"));

	while (OCI_SUCCESS == status  || OCI_SUCCESS_WITH_INFO == status )
	{
		LogInfo((fd,"Student Id = %d\n",id));
		LogInfo((fd,"Student Name = %10.10s\n", name));
		LogInfo((fd,"Student Age = %10.10d\n", age));
		LogInfo((fd,"---------------------------------------\n"));
		status = OCIStmtFetch(stmt, errhp, (ub4) 1, (ub4) OCI_FETCH_NEXT,(ub4) OCI_DEFAULT);
		PassFailFlag = checkError(errhp,status,ERRHND);
	}

	LogEnd((fd,"Result log for ociCallsSelectBindPos ends.\n"));

	if(FAIL == PassFailFlag)
	{
		cleanUp(env,srvhp,svchp,authp,errhp);
		LogFail((stdout));
		LogEnd((stdout," For Select Query stmts : ociCallsSelectBindPos.\n"));
		exit(EXIT_FAILURE);
	}
	
	cleanUp(env,srvhp,svchp,authp,errhp);
	LogPass((stdout));
	LogEnd((stdout," For Select Query stmts : ociCallsSelectBindPos.\n"));
	return 0;
}
