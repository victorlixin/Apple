/*C+
 * Copyright (c) Microsoft Corporation.  All rights reserved.
 *C-
 */ 

/*
 * rcsid = $Header:$
 */

#ifndef _INTERIX_REGISTRY_H
#define _INTERIX_REGISTRY_H

/*
 *  define the registry keys where the Interix information is to be stored.
 *  Note: OPENNT_KEY is deprecated and may be withdrawn in a future release.
 */
#define OPENNT_KEY      \
	L"\\Registry\\Machine\\Software\\Microsoft\\SUA"

#define INTERIX_KEY \
            L"\\Registry\\Machine\\Software\\Microsoft\\SUA"
            
#define INTERIX_SYSTEM_KEY \
	     L"\\Registry\\Machine\\Software\\Microsoft\\SUA"


#define ROOT_KEY_SYSWOW TEXT("Software\\Microsoft\\Wow64")

#define ROOT_KEY_LUA TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System")

#define SUA_KEY TEXT("SOFTWARE\\Microsoft\\SUA")

#define INTERIX_SYSTEM_NAME      "Interix"

/*
 *  values in the INTERIX_KEY
 */


#define REGVAL_INSTALLROOT_WIN	L"InstallRoot_Win"
#define REGVAL_CSPATH		L"_CS_PATH"
#define REGVAL_FORKWAIT		L"ForkWait"
#define REGVAL_MAXOPENFILES	L"MaxOpenFiles"
#define REGVAL_MAXPROC		L"MaxProc"
#define REGVAL_ENABLEASSERTIONS	L"EnableAssertions"
#define REGVAL_WINSOCKVER	L"Winsock_Version_To_Use"
#define REGVAL_LOGINDEFAULTDOMAIN	L"LoginDefaultDomain"
#define REGVAL_PRINCIPAL_DOMAIN	L"PrincipalDomain"
#define REGVAL_API_THREADS	L"ApiThreads"
#define REGVAL_API_THREADS_MAX	L"ApiThreadsMax"
#define REGVAL_TERMINAL_THREADS	L"TerminalThreads"
#define REGVAL_CURRENTVERSION	L"Version"
#define REGVAL_CONSOLE_TTYNAME	L"ConsoleTtyName"
#define REGVAL_PRIO_ADJ		L"PriorityAdjustment"
#define REGVAL_FORCE_DEBUG	L"ForceDebug"
#define REGVAL_TRACE_FLAGS	L"SubSystemTraceFlags"
#define REGVAL_DC_INTERVAL	L"DCSweepInterval"
#define REGVAL_ENABLE_SETUID_BINARIES      L"EnableSetuidBinaries"
#define REGVAL_MAXOPENFILES     L"MaxOpenFiles"
#define REGVAL_DISABLE_TURBODIS     TEXT("Wow64ExecuteFlags")
#define REGVAL_ENABLE_LUA  TEXT("EnableLUA")
#define REGVAL_ENABLE_SU_TO_ROOT TEXT("EnableSuToRoot")
#define REGVAL_MAXLDGRAMSIZE	L"MaxLocalDgramSize"
/* backward compat only */
/* Deprecated; may be withdrawn in a future release */
#define OPENNT_INSTALLROOT L"InstallRoot"
#define OPENNT_ASSERTIONS  L"AssertionsOn"
#define OPENNT_INSTALL_KEY      \
	L"\\Registry\\Machine\\Software\\Microsoft\\SUA"
/* OLD licensing key (pre2.0) */
#define LICENCE_VALUE  L"InstallKey"


/*
 * NT specific registry keys
 */
#define REGKEY_CurrentControlSet \
		L"\\Registry\\Machine\\System\\CurrentControlSet"

/* key to current ComputerName 
 * note: there is also ActiveComputerName.
 */
#define COMPUTERNAME_KEY   \
	REGKEY_CurrentControlSet L"\\Control\\ComputerName\\ComputerName"

/* key to ActiveComputerName  - this contains the name of the machine at time
 * of last reboot
 */
#define ACTIVECOMPUTERNAME_KEY   \
	REGKEY_CurrentControlSet L"\\Control\\ComputerName\\ActiveComputerName"

#define COMPUTERNAME_VALUE     L"ComputerName"

#define NT_SYSTEM_NAME          "Windows NT"

#define SESSION_ENVIRONMENT_KEY   \
	REGKEY_CurrentControlSet L"\\Control\\Session Manager\\Environment"

#define NT_VERSION_KEY  \
        L"\\Registry\\Machine\\Software\\Microsoft\\Windows NT\\CurrentVersion"
#define NT_VERSION_VALUE        L"CurrentVersion"
#define NT_PRODUCT_NAME_VALUE        L"ProductName"

#define NT_LOGON_KEY  \
        L"\\Registry\\Machine\\Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon"
#define NT_DOMAIN		L"CachePrimaryDomain"

#define NT_BUILD_KEY    \
        L"\\Registry\\Machine\\Software\\Microsoft\\Windows NT\\CurrentVersion"
#define NT_BUILD_VALUE  L"CurrentBuildNumber"

#define NT_SERVICEPACK_KEY      \
        L"\\Registry\\Machine\\Software\\Microsoft\\Windows NT\\CurrentVersion"
#define NT_SERVICEPACK_VALUE    L"CSDVersion"

#define REGKEY_TCPIP_PARAMETERS  \
		REGKEY_CurrentControlSet L"\\Services\\Tcpip\\Parameters"
#define REGVAL_HOSTNAME  L"Hostname"
#define NT_TIMEZONE_KEY   NT_VERSION_KEY L"\\Time Zones"

#define NW_PROVIDERS_KEY REGKEY_CurrentControlSet L"\\Control\\NetworkProvider\\Order"
#define NW_PROVIDER_VAL L"ProviderOrder"
#define PROVIDER_DETAILS_KEY REGKEY_CurrentControlSet L"\\Services"
#define PROVIDER_KEY L"\\NetworkProvider"
#define PROVIDER_NAME_VAL L"Name"

#define SDK_VERSION_KEY  \
        L"\\Registry\\Machine\\Software\\Microsoft\\SUA\\SDK"
#define SDK_VERSION_VALUE        L"Version"


#endif /* _INTERIX_REGISTRY_H */
