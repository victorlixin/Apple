#
# Copyright (c) Microsoft Corporation. All rights reserved.
# 
# srcId = $Id: aliases.ksh#1 2004/09/23 05:45:17 FAREAST\\ranas $
#
# Sample aliases file which includes contents of the stock
# WINNT40/system32 directory.


# create _WINSYS environment variable - to the 'system32' directory
#
_WINSYS="$(ntpath2posix -c ${SYSTEMROOT}/system32)"

# Create a WINSYS environment variable
# If WINSYS is already defined, don't change it.
#
if ! [ "$WINSYS" ]
then
	WINSYS=$(ntpath2posix -c ${SYSTEMROOT}/system32 )
	export WINSYS
	echo Setting WINSYS
fi

#
# go to _WINSYS directory and gather up all the executable file names
# and convert them all to lowercase
#
files="$(cd ${_WINSYS}; print *.exe *.EXE)"

#
# create an alias for all executable files in the 'files' list
#
for i in $files; do

    # convert the filename to lowercase and remove the .exe extension
    #
    typeset -l fname=${i%.[Ee][Xx][Ee]}

    # skip any built-in commands and/or previously defined aliases
    #
    if whence $fname > /dev/null 2>&1; then
	continue
    fi

    alias $fname=${_WINSYS}/$i
done

#
# cleanup
#
unset files
unset fname
