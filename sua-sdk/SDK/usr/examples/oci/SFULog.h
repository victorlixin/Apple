#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

//All pure win32 applications must define this flag
#ifdef PUREWIN32
#include <windows.h>
#endif

//For mixed mode applications and interix applications
#ifndef PUREWIN32
#include <unistd.h>
#include <pthread.h>
#endif

//This is the maximum string size one can print at a time
#define MAX_STRING_SIZE 4096

//Enum for the level of logging
enum Level
{
	Detailed,
	Minimal,
	Nothing
};

//Helper struct to print the log info
struct PrintInfo
{
	FILE* file;
	char msg[MAX_STRING_SIZE];
};

//Function declarations
enum Level GetLoggingLevel();

void SetLoggingLevel(enum Level val);

FILE* SFULogInit(const char* file, const char* mode);

void SFULogClose(FILE* file);

void MyLog(const char* fileName, int lineNo, const char* funcName, struct PrintInfo info);

struct PrintInfo RetStructError(FILE* file, const char* formatstring, ...);

struct PrintInfo RetStructWarning(FILE* file, const char* formatstring, ...);

struct PrintInfo RetStructInfo(FILE* file, const char* formatstring, ...);

struct PrintInfo RetStructBegin(FILE* file, const char* formatstring, ...);

struct PrintInfo RetStructEnd(FILE* file, const char* formatstring, ...);


//Macros for logging Info
#define LogInfo(params) MyLog(__FILE__, __LINE__, __FUNCTION__, RetStructInfo params)

#define LogError(params) MyLog(__FILE__, __LINE__, __FUNCTION__, RetStructError params)

#define LogWarning(params) MyLog(__FILE__, __LINE__, __FUNCTION__, RetStructWarning params)

#define LogBegin(params) MyLog(__FILE__, __LINE__, __FUNCTION__, RetStructBegin params)

#define LogEnd(params) MyLog(__FILE__, __LINE__, __FUNCTION__, RetStructEnd params)

#define LogPass(file) fprintf(file, "TEST_RESULT:PASS\n");

#define LogFail(file) fprintf(file, "TEST_RESULT:FAIL\n");
