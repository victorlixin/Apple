#include "SFULog.h"

//By default we log minimal information
enum Level currLevel = Minimal;

//Used a seperator for all test cases
const char* line = "\n*****************************************************************************************\n";

//Interface to change the Loglevel
void SetLoggingLevel(enum Level val)
{
	if(Detailed == val)
	{
		currLevel = Detailed;
	}
	else if(Nothing == val)
	{
		currLevel = Nothing;
	}
	else //Default is to minimal info
	{
		currLevel = Minimal;
	}
}

enum Level GetLoggingLevel()
{
	return currLevel;
}

//Modifies the print string suitable and returns it to the function which actually prints
struct PrintInfo RetStructBegin(FILE* file, const char* formatstring, ...)
{
	char msg[MAX_STRING_SIZE];
	va_list ap;
	struct PrintInfo info;
	
	va_start(ap, formatstring);
	vsprintf(msg, formatstring, ap);
	info.file = file;

	strcpy(info.msg, line);
	strcat(info.msg, "Test Case Begin:");
	strcat(info.msg, msg); 

	return info;
}

struct PrintInfo RetStructEnd(FILE* file, const char* formatstring, ...)
{
	char msg[MAX_STRING_SIZE];
	va_list ap;
	struct PrintInfo info;
	
	va_start(ap, formatstring);
	vsprintf(msg, formatstring, ap);
	info.file = file;

	strcpy(info.msg, "\nTest Case End:\n");
	strcat(info.msg, msg); 
	strcat(info.msg, line);

	return info;
}

struct PrintInfo RetStructError(FILE* file, const char* formatstring, ...)
{
	char msg[MAX_STRING_SIZE];
	va_list ap;
	struct PrintInfo info;
	
	va_start(ap, formatstring);
	vsprintf(msg, formatstring, ap);
	info.file = file;

	strcpy(info.msg, "Error:");
	strcat(info.msg, msg); 

	return info;
}

struct PrintInfo RetStructWarning(FILE* file, const char* formatstring, ...)
{
	char msg[MAX_STRING_SIZE];
	va_list ap;
	struct PrintInfo info;
	
	va_start(ap, formatstring);
	vsprintf(msg, formatstring, ap);
	info.file = file;

	strcpy(info.msg, "Warning:");
	strcat(info.msg, msg); 

	return info;
}

struct PrintInfo RetStructInfo(FILE* file, const char* formatstring, ...)
{
	char msg[MAX_STRING_SIZE];
	va_list ap;
	struct PrintInfo info;
	
	va_start(ap, formatstring);
	vsprintf(msg, formatstring, ap);
	info.file = file;

	strcpy(info.msg, "Info:");
	strcat(info.msg, msg); 

	return info;
}

//The actual function which prints info
void MyLog(const char* fileName, int lineNo, const char* funcName, struct PrintInfo info)
{
	char num[64];
	char pid[64];
	char msg[MAX_STRING_SIZE];
	msg[0] = '\0';	//make the string an empty one

	if(Detailed == GetLoggingLevel())
	{
		strcat(msg, "<");
		strcat(msg, fileName);
		strcat(msg, "> <");
		strcat(msg, funcName);
		strcat(msg, "> ");
		sprintf(num, "<%d> ", lineNo);
		strcat(msg, num);

//Uses win32 api
#ifdef PUREWIN32
		sprintf(pid, "<%d> ", GetCurrentProcessId());
		sprintf(num, "<%d> ", GetCurrentThreadId());
#endif

//Uses Interix api
#ifndef PUREWIN32
		sprintf(pid, "<%d> ", getpid());
		sprintf(num, "<%d> ", pthread_self());
#endif

		strcat(msg, pid);
		strcat(msg, num);

		sprintf(num, "<%d> ", time(NULL));
		strcat(msg, num);

	}

	strcat(msg, info.msg);

	if(Nothing != GetLoggingLevel())
	{
        fprintf(info.file, msg);
	fflush(info.file);
	}
}

FILE* SFULogInit(const char* file, const char* mode)
{
	if (NULL == file || NULL == mode)
	{
		return NULL;
	}

	return fopen(file, mode);
}

void SFULogClose(FILE* file)
{
	fclose(file);
}
