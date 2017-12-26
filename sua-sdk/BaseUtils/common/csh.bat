:: a bat script to invoke a SFU/Interix login csh
:: from MS Windows environment (ie cmd.exe )
:: This assmes the Interix subsystem and Interix utilities
:: have been installed
::
::
:: Rcsid = $Id$
::

posix /u /c /bin/tcsh %1 %2 %3 %4 %5 %6 %7 %8 %9
