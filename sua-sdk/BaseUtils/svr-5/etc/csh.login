#
#
# Copyright (c) Microsoft Corporation.  All rights reserved.
#
# THIS SOFTWARE IS PROVIDED ``AS IS'' BY MICROSOFT CORP. AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL MICROSOFT CORPORATION BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#C-

#----------------------------------------------
#
# Filename: /etc/csh.login
#
# RCSID = $Header: /E/SUA/src/etc.files/csh.login,v 1.27 1999/10/13 17:56:05 rodney Exp $
# 
# This is the system level shell login that is sourced in when a shell 
# starts.  This is where system level environment configuration should take 
# place, and it should be done by the system's administrator.
#
# Please remember to ensure that this file has no carriage-return/line-feeds
# after editting it. If you do use a Win32 program to edit this file,
# be sure to run /SUA/bin/flip to convert it back into the 
# UNIX/POSIX format.
#
#  e.g) From a CMD.EXE command prompt
#
#    $ c:\SUA\bin\flip -u csh.login
#

# -------------
# PATH setup:

# speed improvement during startup
unhash

# save the original 'PATH'  environment variable to PATH_ORIG
# so the user can use it in his/her personal cshrc later.
#
setenv PATH_ORIG "$PATH"

# 
#  When a POSIX subsystem process is started, the PATH environment 
#  variable was created from the system NT 'Path' variable by changing 
#  the directory
#  separator from ";" to ":", and the drive letter ids from "N:" to "/N".
#
#  We now have to prefix it with the path to where the SUA commands
#  and utilties product was installed.
#
#

set __x11_dir = /usr/X11R6

setenv PATH  "/svr-5/bin:/svr-5/usr/sbin:/bin:/opt/gcc.3.3/bin:/usr/contrib/bin:${__x11_dir}/bin:/usr/local/bin:/usr/contrib/win32/bin"

#
# now check for the existance of a directory to the local compiler 
#
if ($?INTERIX_COMPILERDIR) then
    #
    # search for known directories where compiler executables and DLLs
    # may be found in MSVC4.x, MSVC5.x, MSVC6.x and MSVC7.x
    #
    set VC5_DIRS="VC/BIN SharedIDE/BIN"
    set VC6_DIRS="Vc98/Bin Common/Msdev98/BIN"
    set VC7_DIRS="Common7/Tools Common7/Tools/Bin Vc7/bin Common7/IDE SDK/v1.1/Bin"
    set VC8_DIRS="VC/bin VC/vcpackages SDK/v2.0/Bin"
    foreach i ( $VC8_DIRS $VC7_DIRS $VC6_DIRS $VC5_DIRS BIN )
       set i=`ntpath2posix -c "${INTERIX_COMPILERDIR}/${i}"`
       if ( -d "${i}" ) then
	    # note: need to separate ':' from $PATH otherwise
	    #    csh will treat it as a variable modifier meta-character.
	    # 
	    setenv PATH "$PATH":"${i}"
       endif
    end
endif

# -------------
#
# TMPDIR is used by a number of utilities as a place in which temporary files
# can always be placed.
#
# look for several 'tmp' environment variables and check if any of these
# directories exist.
# If so, then use this directory as the value for TMPDIR
# Order of precedence:
#    INTERIX_TMPDIR 
#    TMPDIR	// user can set this in "ControlPanel/System/Environment"
#
# Note: INTERIX_TMPDIR and TMPDIR are available so that user can set these
#       via the "ControlPanel/System/Environment".
#
if ($?TMPDIR) then
    set origTMPDIR="${TMPDIR}" # save original value
    unsetenv TMPDIR
endif

#
# now check each directory and set TMPDIR to the first one that 
# is writeable
#
foreach _i ( INTERIX_TMPDIR origTMPDIR )

    # check if $_i variable is defined 
    # since Csh complains if the env. variable is not set,
    # we have to explicitly test it ourselves
    #
    eval set _isdefined = '$?'$_i	

    if ( $_isdefined ) then
	eval set _i='$'$_i	# set _i to the value of env. variable

	if ( "${_i}" != "" ) then	# check if env. variable is empty

	   # try this path converted to POSIX format and using existing case
	   if ( -d "${_i}" ) then
		(print > "${_i}/.tmp$$xx") >& /dev/null \
			&& rm -f "${_i}/.tmp$$xx"  # check if dir is writable
		if ( $status == 0 ) then
		    setenv TMPDIR "${_i}"
		    break
		endif
	   endif

	endif
    endif
end

unset origTMPDIR
unset _isdefined
unset _i

#
# If TMPDIR still not set, then use the default value of "/Interix/tmp/"
# which was created at install time
# NOTE: permissions on this directory may need to be changed to 777
#       because this is not done at install time.
#

if (!($?TMPDIR)) then
	setenv TMPDIR "/tmp"
endif

# *** NOTE:
#    we do NOT convert TMP or TEMP (if they exist) to POSIX format
#    because user may invoke a Win32 program which uses this value
#    and if so, it must be in the Win32 format


#
# shared library support.
# Define LD_LIBRARY_PATH to the directory where shared libraries are.
#
set PROC_ARCH=`uname -m`
if ( $PROC_ARCH == "x86" ) then
setenv LD_LIBRARY_PATH /usr/lib:${__x11_dir}/lib
else
setenv LD_LIBRARY_PATH /usr/lib/x86:${__x11_dir}/lib
setenv GCC_EXEC_PREFIX /usr/lib/x86
endif

# -------------
#
# Terminal Behaviour
# The terminal behaves properly with respect to newlines, (versus carriage-
# return/newline) and cursor control for utilities like more and vi, if
# the following variables are correctly configured.
# TERM should be set to the default 'interix',
# TERMCAP needs to point to the directory with the termcap file.

# If the user has a larger terminal than TERM then it should be reset in
# their personal .login
if (!($?TERM)) then
	setenv TERM interix
endif

if (!($?TERMCAP)) then
    setenv TERMCAP "/usr/share/termcap"
endif


# -------------
#
# Set up the default MANPATH
#
if (!($?MANPATH)) then
    setenv MANPATH "/usr/share/man:${__x11_dir}/man:/usr/X11R5/man"
endif


# -------------
#
# Set up X11 variables
#
if (!($?XAPPLRESDIR)) then
    setenv XAPPLRESDIR "${__x11_dir}/lib/X11/app-defaults"
endif
if (!($?XFILESEARCHPATH)) then
    setenv XFILESEARCHPATH "${XAPPLRESDIR}/%N%S:${__x11_dir}/include/X11/bitmaps/%N%S"
endif

if (!($?XKEYSYMDB)) then
    setenv XKEYSYMDB "${__x11_dir}/lib/X11/XKeysymDB"
endif
if (!($?XCMSDB)) then
    setenv XCMSDB "${__x11_dir}/lib/X11/Xcms.txt"
endif

if (!($?UIDPATH)) then
    setenv UIDPATH "${__x11_dir}/lib/X11/uid/%U"
endif
if (!($?XNLSPATH)) then
    setenv XNLSPATH "${__x11_dir}/lib/X11/locale"
endif

#
# inherit DISPLAY from the previous environment.
# If its not set, then set it to something reasonable
#
if (!($?DISPLAY)) then
    set __hostname=`uname -n`
    if ( "$__hostname" == "" ) then
	setenv DISPLAY "localhost:0.0"
    else
	setenv DISPLAY "${__hostname}:0.0"
    endif
    unset __hostname
endif


# -------------
#
# These environment variables are used by various utilities to invoke 
# an editor for various tasks.  Set to vi initially.  The last is for utilities
#
setenv EDITOR ed
setenv VISUAL vi
setenv FCEDIT vi

# user must explicitly set SHELL - we don't want to inherit a bogus one
# from the NT/Win32 environment because it will probably be in the 
# incorrect path syntax and it may point to the wrong shell
#
unsetenv SHELL		

# -------------
#
# Change directory to user's home directory.
# On UNIX, this would be done by the login(1) program, but since
# we don't always run login(1) (for example, from a shortcut) we emulate
# it here to be sure.
#
if ($?HOME) then
    if ( -d "${HOME}" ) then
        cd "$HOME"
    endif
endif


#
# execute the csh.lcl file if it exists
#
if ( -f "/etc/csh.lcl" ) then
	source "/etc/csh.lcl"
endif

# -------------
# now unset the local variables
#
unset __x11_dir

#
# USERDOMAIN - a variable looked at by various utilities (ie. ls(1))
#                in order to strip off any leading DOMAIN name prefix
#               to shorten the display of user/group names.
#    If its not defined yet, then initialize it
#
if ( ! ${?USERDOMAIN} ) then
    # get user name, remove anything following the '+' in the user name
    #
    setenv USERDOMAIN `id -D -un | awk '{ gsub(/\+.*/, ""); print $1}'`
endif

#setting default timezone
setenv TZ :GMT

# turn the exec hash table on now
rehash
