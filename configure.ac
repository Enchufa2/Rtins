define([pkgversion], esyscmd([sh -c "grep Version: DESCRIPTION | cut -d' ' -f2 | tr -d '\n'"]))
AC_INIT(Rtins, [pkgversion], i.ucar86@gmail.com)
AC_MSG_NOTICE([${PACKAGE_NAME}: ${PACKAGE_VERSION}])

AC_ARG_WITH([libtins-include],
            AS_HELP_STRING([--with-libtins-include=INCLUDE_PATH],
		                       [location of the libtins header files]),
		        [libtins_include_path=$withval])

AC_ARG_WITH([libtins-lib],
            AS_HELP_STRING([--with-libtins-lib=LIB_PATH],
		                       [location of the libtins libraries]),
		        [libtins_lib_path=$withval])

: ${R_HOME=`R RHOME`}
if test -z "${R_HOME}"; then
  echo "could not determine R_HOME"
  exit 1
fi
CC=`"${R_HOME}/bin/R" CMD config CC`
CFLAGS=`"${R_HOME}/bin/R" CMD config CFLAGS`
CPPFLAGS=`"${R_HOME}/bin/R" CMD config CPPFLAGS`
LDFLAGS=`"${R_HOME}/bin/R" CMD config LDFLAGS`
CXX=`"${R_HOME}/bin/R" CMD config CXX`
CXXFLAGS=`"${R_HOME}/bin/R" CMD config CXXFLAGS`
AC_LANG(C++)

if test [ -n "$libtins_include_path" ] ; then
  CPPFLAGS="-I${libtins_include_path}"
else
  if test [ -n "${LIBTINS_INCLUDE}" ] ; then
    CPPFLAGS="-I{LIBTINS_INCLUDE}"
  fi
fi

if test [ -n "$libtins_lib_path" ] ; then
   LIBS="-L${libtins_lib_path}"
else
   if test [ -n "${LIBTINS_LIB}" ] ; then
      LIBS="-L${LIBTINS_LIB}"
   fi
fi

AC_C_INLINE
AC_PREREQ
AC_PROG_CC
AC_TYPE_SIZE_T
AC_CHECK_LIB(tins, main, 
             LIBS="${LIBS} -ltins", 
             LIBTINS_ERROR="libtins not found")

if test "${LIBTINS_ERROR}" != ""  ; then
    AC_MSG_FAILURE([
--------------------------------------------------------------------------------
  The libtins library that is required to build Rtins, but was not found.

  Please install libtins (libtins.github.io) and try again.

  If the libtins library is installed on your system but the Rtins configuration 
  is unable to find it, you can specify the include and lib paths to Rtins with:
 
  --configure-args='--with-libtins-include=INCLUDE_PATH --with-libtins-lib=LIB_PATH'
 
  or using the LIBTINS_INCLUDE and LIBTINS_LIB environment variables.
--------------------------------------------------------------------------------])
fi

AC_SUBST(PKG_CPPFLAGS, "${CPPFLAGS}")
AC_SUBST(PKG_LIBS, "$LIBS")
AC_CONFIG_FILES([src/Makevars])
AC_OUTPUT
