#include "CommonOciCalls.h"

const char* username = "DBUSER";
const char* database = "DBNAME";
const char* password = "DBPASSWORD";
const char* type_name ="TYPE_NAME";
const char* remote_username = "REMOTE_DBUSER";
const char* remote_database = "REMOTE_DBNAME";
const char* remote_password = "REMOTE_PASSWORD";

//int _beThreadSafe = 0;

int checkError(dvoid *Hdp , sword status, enum errorMode mode)
{
	char *errMsg = NULL;
	sb4 errorCode = 0;
	int ret = -1;

	errMsg = (char *)malloc(ERRORMSGLEN *sizeof(char));
	if(!errMsg)
		return ret;
	
	switch(status)
	{
	case OCI_SUCCESS:
		/* No error. Proceed ahead.*/
		ret = 0;
		break;
	case OCI_SUCCESS_WITH_INFO:
		if(ERRHND == mode)
			OCIErrorGet(Hdp, (ub4 ) 1, (text *)NULL, (sb4 *)&errorCode, (text *)errMsg, (ub4 )(ERRORMSGLEN), OCI_HTYPE_ERROR);
		else if(ENVHND == mode)
			OCIErrorGet(Hdp, (ub4 ) 1, (text *)NULL, (sb4 *)&errorCode, (text *)errMsg, (ub4 )(ERRORMSGLEN), OCI_HTYPE_ENV);
		LogInfo((stdout,"Warning : %s\n",errMsg));
		ret =0;
		break;
	case OCI_STILL_EXECUTING:
		//LogInfo((stdout," OCI_STILL_EXECUTING.\n"));
		ret =0;
		break;
	case OCI_CONTINUE:
		//LogInfo((stdout," OCI_CONTINUE.\n"));
		ret = 0;
		break;
	case OCI_INVALID_HANDLE:
		LogError((stdout," OCI_INVALID_HANDLE.\n"));
		break; 
	case OCI_NEED_DATA:
		LogError((stdout," OCI_NEED_DATA\n"));
		break;
	case OCI_NO_DATA:
		//LogError((stdout," OCI_NO_DATA\n"));
		ret =0;
		break;
	case OCI_ERROR:
		if(ERRHND == mode)
			OCIErrorGet(Hdp, (ub4 ) 1, (text *)NULL, (sb4 *)&errorCode, (text *)errMsg, (ub4 )(ERRORMSGLEN), OCI_HTYPE_ERROR);
		else if(ENVHND == mode)
			OCIErrorGet(Hdp, (ub4 ) 1, (text *)NULL, (sb4 *)&errorCode, (text *)errMsg, (ub4 )(ERRORMSGLEN), OCI_HTYPE_ENV);

		LogError((stdout," : %s\n",errMsg));
		break;
	default:
		break;
	}
	return ret;
}


FILE * getFileDescriptor(char *fileName, char *mode)
{
	FILE *LogFileHd = NULL;
	//LogInfo((stdout,"In getfile file = %s mode = %s \n",fileName,mode));
	LogFileHd = fopen((char *)fileName ,(const char *) mode);
	//LogInfo((stdout,"In getfile file = %s mode = %s \n",fileName,mode));
	
	if(LogFileHd == NULL)
		LogError((stdout,"Unable to open logfile %s in mode %s\n",fileName,mode));
	//else
	//	LogInfo((stdout,"fd is not null\n"));

	return LogFileHd;
}

void cleanUp(OCIEnv *envHdp,OCIServer *srvHdp,OCISvcCtx *svcHdp,OCISession *usrHdp,OCIError *errHdp)
{
	if(envHdp)
	{
		/* Ending the Session created with OCISessionBegin() call.*/
		if(svcHdp && errHdp && usrHdp)
			checkError(errHdp,OCISessionEnd(svcHdp,errHdp,usrHdp,OCI_DEFAULT),(ub4)ERRHND);
	
		/*Detacking OCI application from the data srource attached by OCIServerAttach call.*/
		if(srvHdp && errHdp)
			checkError(errHdp,OCIServerDetach(srvHdp,errHdp,OCI_DEFAULT),(ub4)ERRHND);
	
		LogInfo((stdout,"In cleanup before env handle free.\n"));

		if( OCIHandleFree(envHdp, OCI_HTYPE_ENV) == OCI_SUCCESS)
			LogInfo((stdout,"Cleanup done successful.\n"));
		else 
			LogError((stdout,"Cleanup unsuccessful.\n"));
		
		LogInfo((stdout,"In cleanup after env handle free.\n"));
	}
}


dvoid *myAlloc(dvoid *ctxp, size_t size)
{
	if(size != 0)
	{
		return malloc(size);
	}
	else
		return NULL;
}

dvoid *myRealloc(dvoid *ctxp, dvoid *memptr, size_t newsize)
{
	if(newsize != 0)
	{
		LogInfo((stdout,"In user defined Realloc.\n"));
		return realloc(memptr, newsize);
	}
	else
		return memptr;
}

dvoid myFree(dvoid *ctxp, dvoid *memptr)
{
		LogInfo((stdout,"In user defined free .\n"));
		free (memptr);
		memptr = NULL;
		LogInfo((stdout,"In user defined free function, memory.\n"));
}

/**********************************************************************************
* Getting Username, UserPassword & Database Name.									
***********************************************************************************/

char * getEnvData(enum systemVariables type)
{
	char *strp = NULL;

	switch(type)
	{
	case USERNAME:
	{
		strp = getenv(username);
		if(NULL == strp)
		{
			LogError((stdout, "User name not defined in the environment = %s\n", username));
			return NULL;
		}
		break;
	}
	case PASSWORD:
	{
		strp = getenv(password);
		if(NULL == strp)
		{
			LogError((stdout, "Password not defined in the environment = %s\n", password));
			return NULL;
		}
		break;
	}
	case DATABASE_NAME:
	{
		strp = getenv(database);
		if(NULL == strp)
		{
			LogError((stdout, "Database name not defined in the environment = %s\n", database));
			return NULL;
		}
		break;
	}
	case TYPENAME:
	{
		strp = getenv(type_name);
		if(NULL == strp)
		{
			LogError((stdout, "Type name not defined in the environment = %s\n", type_name));
			return NULL;
		}
		break;
	}
	case REMOTE_USERNAME:
	{
		strp = getenv(remote_username);
		if(NULL == strp)
		{
			LogError((stdout, "User name not defined in the environment = %s\n", remote_username));
			return NULL;
		}
		break;
	}
	case REMOTE_PASSWORD:
	{
		strp = getenv(remote_password);
		if(NULL == strp)
		{
			LogError((stdout, "Password not defined in the environment = %s\n", remote_password));
			return NULL;
		}
		break;
	}
	case REMOTE_DATABASE_NAME:
	{
		strp = getenv(remote_database);
		if(NULL == strp)
		{
			LogError((stdout, "Database name not defined in the environment = %s\n", remote_database));
			return NULL;
		}
		break;
	}

	default:
		break;
	}
	return strp;
}


char *reverse(char *str,int end)
{
	char var;
	char *temp1 = str;
	char *temp2 = str,*temp = str;
    
	while(*temp != '\0')
	{
		temp2 = temp;
		temp++;
	}

	while(temp1 < temp2)
	{
		var = *temp1;
		*temp1 = *temp2;
		*temp2 = var;
		temp1++;
		temp2--;
	}
	return str;
}

char * itoa(int num,char *str,int size)
{
	int i = 0;
	if(str == NULL)
		return str;

	while(num)
	{
		if( i < size)
			str[i++] = num%10 + 48;
		else
			break;
		num = num/10;
	}

	if(i < size)
	{
		str[i] = '\0';
		return reverse(str, i);
	}
	else
		return NULL;
}	


/********************************************************************
* Initialize environment and allocate handles.
* param : flag is either BACKWARDCOMPIATABLE or PRESENTRELEASE
********************************************************************/

sb4 initHandles(OCIEnv **envHdpp, 
				 OCIError **errHdpp,	
				 OCISvcCtx **svcHdpp,
				 OCIServer **srvHdpp,
				 OCIStmt **stmtpp,
				 OCISession **authpp,
				 enum release flag,int mode,int memsize, void **memPtr)
{
	//LogInfo((stdout,"Inside inithandles\n"));
	 /* OCIEnvCreate() should be used instead of the OCIInitialize() and OCIEnvInit() calls. 
	  * OCIInitialize() and OCIEnvInit() calls will be supported for backward compatibility*/
	if(*envHdpp == NULL)
	{
		if(BACKWARDCOMPATIBLE == flag)
		{
			if (OCIInitialize((ub4) mode, (dvoid *)0,
				(dvoid * (*)(dvoid *, size_t)) 0,
				(dvoid * (*)(dvoid *, dvoid *, size_t))0,
				(void (*)(dvoid *, dvoid *)) 0 ))
			{
				LogError((stdout,"FAILED: OCIInitialize()\n"));
				return OCI_ERROR;
			}

			/* initialize environment handle */
			if (FAIL == checkError(*envHdpp , OCIEnvInit((OCIEnv **) envHdpp, (ub4) OCI_DEFAULT,
				(size_t) memsize, (dvoid **) memPtr ), ENVHND))
			{
				LogError((stdout,"FAILED: OCIEnvInit()\n"));
				return OCI_ERROR;
			}		
		}
		else if (PRESENTRELEASE == flag)
		{

			if(OCIEnvCreate ( (OCIEnv **) envHdpp, mode, NULL, NULL, NULL, NULL, (size_t)memsize, (dvoid **)memPtr))
			{
				LogError((stdout,"FAILED: OCIEnvCreate()\n"));
				return OCI_ERROR;
			}
		}
		else
		{
			LogError((stdout,"FAILED: Wrong flag passed to init_handles()\n"));
			return OCI_ERROR;
		}
	}

	if(svcHdpp != NULL && *svcHdpp == NULL)
	{
		if (FAIL == checkError(*envHdpp , OCIHandleAlloc((dvoid *) *envHdpp, (dvoid **) svcHdpp,
			(ub4) OCI_HTYPE_SVCCTX, (size_t) 0, (dvoid **) NULL), ENVHND))
		{
			LogError((stdout,"FAILED: OCIHandleAlloc()\n"));
			return OCI_ERROR;
		}
	}
	if(errHdpp != NULL && *errHdpp == NULL)
	{
		
		if (checkError(*envHdpp , OCIHandleAlloc((dvoid *) *envHdpp, (dvoid **) errHdpp,
			(ub4) OCI_HTYPE_ERROR, (size_t) 0, (dvoid **) NULL), ENVHND))
		{
			LogError((stdout,"FAILED: OCIHandleAlloc()\n"));
			return OCI_ERROR;
		}
	}

  if(stmtpp != NULL && *stmtpp == NULL)
  {
	  if (FAIL == checkError(*envHdpp , OCIHandleAlloc((dvoid *) *envHdpp, (dvoid **) stmtpp,
		  (ub4) OCI_HTYPE_STMT, (size_t) 0, (dvoid **) NULL), ENVHND))
	  {
		  LogError((stdout,"FAILED: OCIHandleAlloc()\n"));
		  return OCI_ERROR;
	  }
  }

  if(srvHdpp != NULL && *srvHdpp == NULL)
  {	
	  if (FAIL == checkError(*envHdpp , OCIHandleAlloc((dvoid *) *envHdpp, (dvoid **) srvHdpp,
		  (ub4) OCI_HTYPE_SERVER, (size_t) 0, (dvoid **)NULL),ENVHND))
	  {
		  LogError((stdout,"FAILED: OCIHandleAlloc()\n"));
		  return OCI_ERROR;
	  }
  }

  if(authpp != NULL && *authpp == NULL)
  {
	
	  if (FAIL == checkError(*envHdpp , OCIHandleAlloc((dvoid *) *envHdpp, (dvoid **) authpp,
		  (ub4) OCI_HTYPE_SESSION, (size_t) 0, (dvoid **) NULL), ENVHND))
	  {
		  LogError((stdout,"FAILED: OCIHandleAlloc()\n"));
		  return OCI_ERROR;
	  }
  	}
  return OCI_SUCCESS;
}



sb4 initHandlesWithUserDefined(OCIEnv **envHdpp, 
				 OCIError **errHdpp,	
				 OCISvcCtx **svcHdpp,
				 OCIServer **srvHdpp,
				 OCIStmt **stmtpp,
				 OCISession **authpp,
				 enum release flag,int mode,int memsize, void **memPtr)
{
	 /* OCIEnvCreate() should be used instead of the OCIInitialize() and OCIEnvInit() calls. 
	  * OCIInitialize() and OCIEnvInit() calls will be supported for backward compatibility*/
	if(*envHdpp == NULL)
	{
		if(BACKWARDCOMPATIBLE == flag)
		{
			if (OCIInitialize((ub4) mode, (dvoid *)0,
				(dvoid * (*)(dvoid *, size_t)) myAlloc,
				(dvoid * (*)(dvoid *, dvoid *, size_t))myRealloc,
				(void (*)(dvoid *, dvoid *)) myFree ))
			{
				LogError((stdout,"FAILED: OCIInitialize()\n"));
				return OCI_ERROR;
			}

			/* initialize environment handle */
			if (FAIL == checkError(*envHdpp , OCIEnvInit((OCIEnv **) envHdpp, (ub4) OCI_DEFAULT,
				(size_t) memsize, (dvoid **) memPtr ), ENVHND))
			{
				LogError((stdout,"FAILED: OCIEnvInit()\n"));
				return OCI_ERROR;
			}		
		}
		else if (PRESENTRELEASE == flag)
		{

			if(OCIEnvCreate ( (OCIEnv **) envHdpp, mode, NULL, myAlloc, myRealloc, myFree, (size_t)memsize, (dvoid **)memPtr))
			{
				LogError((stdout,"FAILED: OCIEnvCreate()\n"));
				return OCI_ERROR;
			}
		}
		else
		{
			LogError((stdout,"FAILED: Wrong flag passed to init_handles()\n"));
			return OCI_ERROR;
		}
	}

	if(svcHdpp != NULL && *svcHdpp == NULL)
	{
		if (FAIL == checkError(*envHdpp , OCIHandleAlloc((dvoid *) *envHdpp, (dvoid **) svcHdpp,
			(ub4) OCI_HTYPE_SVCCTX, (size_t) 0, (dvoid **) NULL), ENVHND))
		{
			LogError((stdout,"FAILED: OCIHandleAlloc()\n"));
			return OCI_ERROR;
		}
	} 

	if(errHdpp != NULL && *errHdpp == NULL)
	{
		if (FAIL == checkError(*envHdpp , OCIHandleAlloc((dvoid *) *envHdpp, (dvoid **) errHdpp,
							(ub4) OCI_HTYPE_ERROR, (size_t) 0, (dvoid **) NULL), ENVHND))
		{
			LogError((stdout,"FAILED: OCIHandleAlloc()\n"));
			return OCI_ERROR;
		}
	}
	if(stmtpp != NULL && *stmtpp == NULL)
	{
		if (FAIL == checkError(*envHdpp , OCIHandleAlloc((dvoid *) *envHdpp, (dvoid **) stmtpp,
			(ub4) OCI_HTYPE_STMT, (size_t) 0, (dvoid **) NULL), ENVHND))
		{
			LogError((stdout,"FAILED: OCIHandleAlloc()\n"));
			return OCI_ERROR;
		}
	}
	
	  if(srvHdpp != NULL && *srvHdpp == NULL)
	  {	
		if (FAIL == checkError(*envHdpp , OCIHandleAlloc((dvoid *) *envHdpp, (dvoid **) srvHdpp,
			(ub4) OCI_HTYPE_SERVER, (size_t) 0, (dvoid **)NULL),ENVHND))
		{
			LogError((stdout,"FAILED: OCIHandleAlloc()\n"));
			return OCI_ERROR;
		}
	  }
	  
  	if(authpp != NULL && *authpp == NULL)
	  {
		if (FAIL == checkError(*envHdpp , OCIHandleAlloc((dvoid *) *envHdpp, (dvoid **) authpp,
			(ub4) OCI_HTYPE_SESSION, (size_t) 0, (dvoid **) NULL), ENVHND))
		{
			LogError((stdout,"FAILED: OCIHandleAlloc()\n"));
			return OCI_ERROR;
		}
	  }
	return OCI_SUCCESS;
}


/**************************************************************************
* Attaching to the server and log on as UserName/password@databaseName 
**************************************************************************/

sb4 logOn(char *userName , 
		  char *password, 
		  char *databaseName, 
		  OCIError **errHdp,
		  OCISvcCtx **svcHdp,	
		  OCIServer **srvHdp,
		  OCISession **authp)
{
	if(!userName || !password || !databaseName || !*errHdp || !*svcHdp || !*srvHdp || !*authp)
	{
		LogError((stdout,"Wrong Parameters passed to logOn().\n"));
		return OCI_ERROR;
	}

	/* In applications requiring more complex session management, 
	*  the service context must be explicitly allocated, 
	*  and the server handle and user session handle must be explicitly set into the service context. 
	*  OCIServerAttach() and OCISessionBegin(), calls initialize the server and user session handle respectively.*/

	/*  Initializes the Server handle.*/
  /* Attaching to the server.In this server context calls made to server are BLOCKING.*/
  if (FAIL == checkError(*errHdp, OCIServerAttach(*srvHdp, *errHdp, (text *) databaseName,
							(sb4) strlen(databaseName), (ub4) OCI_DEFAULT), ERRHND))
  {
    LogError((stdout,"FAILED: OCIServerAttach()\n"));
    return OCI_ERROR;
  }

 
   /* Setting the server attribute in the service context handle.*/
  if (FAIL == checkError(*errHdp, OCIAttrSet((dvoid *) *svcHdp, (ub4) OCI_HTYPE_SVCCTX,
						(dvoid *) *srvHdp, (ub4) 0, (ub4) OCI_ATTR_SERVER, *errHdp), ERRHND))
  {
    LogError((stdout,"FAILED: OCIAttrSet()\n"));
    return OCI_ERROR;
  }

  /* Setting the username for the session.*/
  if (FAIL == checkError(*errHdp, OCIAttrSet((dvoid *) *authp, (ub4) OCI_HTYPE_SESSION,
						(dvoid *) userName, (ub4) strlen((char *)userName),
						(ub4) OCI_ATTR_USERNAME, *errHdp) , ERRHND))
  {
    LogError((stdout,"FAILED: OCIAttrSet()\n"));
    return OCI_ERROR;
  }

  /* Setting the password for the session.*/
  if (FAIL == checkError(*errHdp, OCIAttrSet((dvoid *) *authp, (ub4) OCI_HTYPE_SESSION,
						(dvoid *) password, (ub4) strlen((char *)password),
						(ub4) OCI_ATTR_PASSWORD, *errHdp), ERRHND))
  {
    LogError((stdout,"FAILED: OCIAttrSet()\n"));
    return OCI_ERROR;
  }

  /* Initializing the user session handle.*/
  if (FAIL == checkError(*errHdp, OCISessionBegin(*svcHdp, *errHdp, *authp, (ub4) OCI_CRED_RDBMS,
								(ub4) OCI_DEFAULT) , ERRHND))
  {
    LogError((stdout,"FAILED: OCISessionBegin()\n"));
    return OCI_ERROR;
  }

  /* Setting the session attribute in the service context. */
  if (FAIL == checkError(*errHdp, OCIAttrSet((dvoid *) *svcHdp, (ub4) OCI_HTYPE_SVCCTX, 
							(dvoid *) *authp,(ub4) 0, (ub4) OCI_ATTR_SESSION, *errHdp), ERRHND))
  {
    LogError((stdout,"FAILED: OCIAttrSet()\n"));
    return OCI_ERROR;
  }

  return OCI_SUCCESS;
}
