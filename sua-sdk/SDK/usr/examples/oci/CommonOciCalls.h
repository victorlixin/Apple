#ifndef _COMMONOCICALLS_H
#define _COMMONOCICALLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

//#include <unistd.h>
#include <sys/types.h>
//#include <pthread.h>
#include <signal.h>


#include <oci.h>
#include <orl.h>
#include <oratypes.h>
#include <ocidfn.h>
#include <ocidem.h>
#include <ociap.h>

#include "SFULog.h"

/**************************************************************/
/* Temporary Solution to Libc problem.*/
extern int _beThreadSafe;
/***********************************************************/

/* Defining Macros.*/

#define  DEFER_PARSE        1
#define  NATIVE             1
#define  VERSION_7          2
//#define PRESENTRELEASE 0
//#define BACKWARDCOMPATIBLE 1

//#define USERNAME 1
//#define PASSWORD 2
//#define DATABASE_NAME 3
//#define TYPENAME 4
#define NAMELEN 20
#define TABLENAMELEN 64
#define FAIL -1
#define PASS 0
#define NO_OF_ROWS	6000000
#define MAXROWS  70000
#define MEMSIZE 512

#define NUMTHREADS  3
#define MAXTHREAD 10

#define MAXBUFLEN  5000

#define MAX_DATE_LENGTH 25

#ifdef _WIN64
#define GRACE_MEMORY 100
#define MEMORYSIZE 4000000000
//#define MEMORYSIZE 40000
#define LOBCOPYAMOUNT 4000000000
#define MAX 2200000000
#define MAX_CONNS 40000000  //Infeasible till .processes paramter in SPfile needs to be changed to allow more processes.See load.sql for SPfile.
							 // Need to increase LARGE_POOL_SIZE else memory fault will happen due to less memory but more requirement.
#define MAX_THREADS 100000000 //Scenario1 depends on this macro.Please see before making any changes. 
#define MAX_BUFFER 1000000000  //Scenario4 depends on this macro.Please see before making any changes. 
#define  MAXIMIUM_CACHE_SIZE 1250
#define BUFFER_SIZE 100000000 //For Scenario5.
#define MAXROWSPOSSIBLE 65530
#define ERRORMSGLEN 4000000000
#define FORMATSIZE 900000000000
#define MAXDATASIZE 2200000000
#define NUMBERTEXTCONVERSION 100
#define RAWMEMORYSIZE 210000000
#else
#define GRACE_MEMORY 0
#define MEMORYSIZE 2000
#define LOBCOPYAMOUNT 40000
#define MAX 30000
#define MAX_CONNS 10 //21000 //.processes paramter in SPfile needs to be changed to allow more processes.See load.sql for SPfile.
#define MAX_THREADS 5
#define MAX_BUFFER 10000
#define  MAXIMIUM_CACHE_SIZE 125
#define BUFFER_SIZE 10000
#define MAXROWSPOSSIBLE 3220
#define ERRORMSGLEN 1024
#define FORMATSIZE 9000
#define MAXDATASIZE 800000000
#define NUMBERTEXTCONVERSION 50
#define RAWMEMORYSIZE 60000
#endif


#define CLOB 1
#define BLOB 2

#define TEMPSIZE 0
#define LOBSIZE 1

#define LOBAPPEND 1
#define LOBCOPY 2
#define LOBWRITE 3
#define LOBERASE 4

#define OVERWRITE 1
#define WRITEAPPEND 2

#define LOADFROMFILE 1
#define LOBREAD 2

#define NAMESTRLEN 40
#define MEMORYSIZENULL 0
#define SIZE 20

#define NAMEDIRLEN 30
#define NAMEFILELEN 255

#define USERDEFINED 1
#define OCIDEFINED 2

extern const char* username;
extern const char* database;
extern const char* password;
extern const char* type_name;
extern const char* remote_username;
extern const char* remote_database;
extern const char* remote_password;


enum systemVariables {USERNAME=1,PASSWORD,DATABASE_NAME,TYPENAME,REMOTE_USERNAME, REMOTE_PASSWORD,REMOTE_DATABASE_NAME};

enum release {PRESENTRELEASE,BACKWARDCOMPATIBLE};

enum errorMode {ERRHND, ENVHND};


/* For AQ calls.*/
typedef struct message
{
  OCIString   *subject;
  OCIString   *data;
}message;

typedef struct null_message
{
  OCIInd    null_adt;
  OCIInd    null_subject;
  OCIInd    null_data;
}null_message;


/* For OCITHREAD calls. */



typedef struct ThrCtx
{
   OCIThreadId      *mainTID_ThrCtx;   /* ID for the main thread */
   /* All of the spawned threads do a check to make sure that their thread  */
   /* ID is different from that of the main thread.                        */

   OCIThreadMutex       *tidArMx_ThrCtx;  /* Mutex for 'tidAr_'   */

   /* Array of thread IDs */
   OCIThreadId    *tidAr_ThrCtx[NUMTHREADS];
   /* As threads are spawned, the array is filled up with their IDs.  The   */
   /* mutex must be held in order for it be safe to access the array.       */

   sword  tnumAr_ThrCtx[NUMTHREADS];  /* Array of thread #'s  */
   /* A thread whose ID is in position 'i' in 'tidAr_' will put 'i' in      */
   /* position 'i' of this array.  The main thread checks this to ensure    */
   /* that everything went OK.                                              */

   OCIThreadKey       *key_ThrCtx;   /* Thread key             */

   ub1   keyAr_ThrCtx[NUMTHREADS];   /* Values for thread key */

}ThrCtx;


/* Function prototypes. */
int checkError(void *Hdp , sword status, enum errorMode mode);

FILE * getFileDescriptor(char *fileName, char *mode);

void cleanUp(OCIEnv *envHdp,OCIServer *srvHdp,OCISvcCtx *svcHdp,OCISession *usrHdp,OCIError *errHdp);

char* getEnvData(enum systemVariables type);

dvoid *myAlloc(dvoid *ctxp, size_t size);

dvoid *myRealloc(dvoid *ctxp, dvoid *memptr, size_t newsize);

dvoid myFree(dvoid *ctxp, dvoid *memptr);

char * itoa(int,char *,int);

sb4 initHandles(OCIEnv **envHdpp, 
				 OCIError **errHdpp,	
				 OCISvcCtx **svcHdpp,
				 OCIServer **srvHdpp,
				 OCIStmt **stmtpp,
				 OCISession **authpp,
				 enum release flag,int mode , int memsize, void **memPtr);

sb4 initHandlesWithUserDefined(OCIEnv **envHdpp, 
				 OCIError **errHdpp,	
				 OCISvcCtx **svcHdpp,
				 OCIServer **srvHdpp,
				 OCIStmt **stmtpp,
				 OCISession **authpp,
				 enum release flag,int mode , int memsize, void **memPtr);

//sb4 initSubscriptionHandle(

sb4 logOn(char *userName , 
		  char *password, 
		  char *databaseName, 
		  OCIError **errHdp,
		  OCISvcCtx **svcHdp,	
		  OCIServer **srvHdp,
		  OCISession **authp);

#endif
