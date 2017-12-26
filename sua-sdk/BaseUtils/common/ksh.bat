:: a bat script to invoke a SFU/Interix login ksh
:: from MS Windows environment (ie cmd.exe )
:: This assmes the Interix subsystem and Interix utilities
:: have been installed
::
::
:: Rcsid = $Id$
::

posix /u /c /bin/ksh %1 %2 %3 %4 %5 %6 %7 %8 %9
