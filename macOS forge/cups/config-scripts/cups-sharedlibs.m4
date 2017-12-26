dnl
dnl Shared library support for CUPS.
dnl
dnl Copyright 2007-2017 by Apple Inc.
dnl Copyright 1997-2005 by Easy Software Products, all rights reserved.
dnl
dnl Licensed under Apache License v2.0.  See the file "LICENSE" for more information.
dnl

PICFLAG=1
DSOFLAGS="${DSOFLAGS:=}"

AC_ARG_ENABLE(shared, [  --disable-shared        do not create shared libraries])

cupsbase="cups"
LIBCUPSBASE="lib$cupsbase"
LIBCUPSSTATIC="lib$cupsbase.a"

if test x$enable_shared != xno; then
	case "$host_os_name" in
		sunos*)
			LIBCUPS="lib$cupsbase.so.2"
			LIBCUPSCGI="libcupscgi.so.1"
			LIBCUPSIMAGE="libcupsimage.so.2"
			LIBCUPSMIME="libcupsmime.so.1"
			LIBCUPSPPDC="libcupsppdc.so.1"
			DSO="\$(CC)"
			DSOXX="\$(CXX)"
			DSOFLAGS="$DSOFLAGS -Wl,-h\`basename \$@\` -G \$(OPTIM)"
			;;
		linux* | gnu* | *bsd*)
			LIBCUPS="lib$cupsbase.so.2"
			LIBCUPSCGI="libcupscgi.so.1"
			LIBCUPSIMAGE="libcupsimage.so.2"
			LIBCUPSMIME="libcupsmime.so.1"
			LIBCUPSPPDC="libcupsppdc.so.1"
			DSO="\$(CC)"
			DSOXX="\$(CXX)"
			DSOFLAGS="$DSOFLAGS -Wl,-soname,\`basename \$@\` -shared \$(OPTIM)"
			;;
		darwin*)
			LIBCUPS="lib$cupsbase.2.dylib"
			LIBCUPSCGI="libcupscgi.1.dylib"
			LIBCUPSIMAGE="libcupsimage.2.dylib"
			LIBCUPSMIME="libcupsmime.1.dylib"
			LIBCUPSPPDC="libcupsppdc.1.dylib"
			DSO="\$(CC)"
			DSOXX="\$(CXX)"
			DSOFLAGS="$DSOFLAGS -dynamiclib -single_module -lc"
			;;
		*)
			echo "Warning: shared libraries may not be supported.  Trying -shared"
			echo "         option with compiler."
			LIBCUPS="lib$cupsbase.so.2"
			LIBCUPSCGI="libcupscgi.so.1"
			LIBCUPSIMAGE="libcupsimage.so.2"
			LIBCUPSMIME="libcupsmime.so.1"
			LIBCUPSPPDC="libcupsppdc.so.1"
			DSO="\$(CC)"
			DSOXX="\$(CXX)"
			DSOFLAGS="$DSOFLAGS -Wl,-soname,\`basename \$@\` -shared \$(OPTIM)"
			;;
	esac
else
	PICFLAG=0
	LIBCUPS="lib$cupsbase.a"
	LIBCUPSCGI="libcupscgi.a"
	LIBCUPSIMAGE="libcupsimage.a"
	LIBCUPSMIME="libcupsmime.a"
	LIBCUPSPPDC="libcupsppdc.a"
	DSO=":"
	DSOXX=":"
fi

AC_SUBST(DSO)
AC_SUBST(DSOXX)
AC_SUBST(DSOFLAGS)
AC_SUBST(LIBCUPS)
AC_SUBST(LIBCUPSBASE)
AC_SUBST(LIBCUPSCGI)
AC_SUBST(LIBCUPSIMAGE)
AC_SUBST(LIBCUPSMIME)
AC_SUBST(LIBCUPSPPDC)
AC_SUBST(LIBCUPSSTATIC)

if test x$enable_shared = xno; then
	LINKCUPS="../cups/lib$cupsbase.a"
	LINKCUPSIMAGE="../filter/libcupsimage.a"

	EXTLINKCUPS="-lcups"
	EXTLINKCUPSIMAGE="-lcupsimage"
else
	LINKCUPS="-l${cupsbase}"
	LINKCUPSIMAGE="-lcupsimage"

	EXTLINKCUPS="-lcups"
	EXTLINKCUPSIMAGE="-lcupsimage"
fi

AC_SUBST(EXTLINKCUPS)
AC_SUBST(EXTLINKCUPSIMAGE)
AC_SUBST(LINKCUPS)
AC_SUBST(LINKCUPSIMAGE)

dnl Update libraries for DSOs...
EXPORT_LDFLAGS=""

if test "$DSO" != ":"; then
	# When using DSOs the image libraries are linked to libcupsimage.so
	# rather than to the executables.  This makes things smaller if you
	# are using any static libraries, and it also allows us to distribute
	# a single DSO rather than a bunch...
	DSOLIBS="\$(LIBZ)"
	IMGLIBS=""

	# Tell the run-time linkers where to find a DSO.  Some platforms
	# need this option, even when the library is installed in a
	# standard location...
	case $host_os_name in
                sunos*)
                	# Solaris...
			if test $exec_prefix != /usr; then
				DSOFLAGS="-R$libdir $DSOFLAGS"
				LDFLAGS="$LDFLAGS -R$libdir"
				EXPORT_LDFLAGS="-R$libdir"
			fi
			;;
                *bsd*)
                        # *BSD...
			if test $exec_prefix != /usr; then
				DSOFLAGS="-Wl,-R$libdir $DSOFLAGS"
				LDFLAGS="$LDFLAGS -Wl,-R$libdir"
				EXPORT_LDFLAGS="-Wl,-R$libdir"
			fi
			;;
                linux* | gnu*)
                        # Linux, and HURD...
			if test $exec_prefix != /usr; then
				DSOFLAGS="-Wl,-rpath,$libdir $DSOFLAGS"
				LDFLAGS="$LDFLAGS -Wl,-rpath,$libdir"
				EXPORT_LDFLAGS="-Wl,-rpath,$libdir"
			fi
			;;
	esac
else
	DSOLIBS=""
	IMGLIBS="\$(LIBZ)"
fi

AC_SUBST(DSOLIBS)
AC_SUBST(IMGLIBS)
AC_SUBST(EXPORT_LDFLAGS)
