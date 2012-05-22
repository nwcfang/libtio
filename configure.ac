#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.60])
AC_INIT([libtio], [0.4.8])


AC_CONFIG_SRCDIR([src/include/config.h.in])
AC_CONFIG_HEADERS([src/include/config.h])


AC_ARG_ENABLE([debug],
        AC_HELP_STRING([--disable-debug], [disable all debug info]),
        [debug="no"; AC_DEFINE([NDEBUG], 1, "Debug is disabled")])
AS_IF([ test "$debug" = "no"  ], [CFLAGS="$CFLAGS -Wall -Werror -O2 -pipe -fpic";], 
      [CFLAGS="$CFLAGS -Wall -O0 -ggdb -pipe -fpic";])

# Функции разрешающие использовафункция стандартной библиотеки для
# вывода строк
AC_ARG_ENABLE([vsprintf], 
               [AC_HELP_STRING([--enable-vsprintf], 
                              [enable or disbale useage of stdlib for numbers output])], 
               [ AS_IF([ test "$enableval" = "yes" ], 
                 [ AC_DEFINE([USE_VSPRINTF], 1, "Useage standart library for numbers output")])],
               [AC_DEFINE([USE_VSPRINTF], 1, "Useage standart library for numbers output")])
AC_ARG_ENABLE([init-return],
              [AC_HELP_STRING([--enable-init-return], 
              [enable to return from tioInit to main when initializatio error appeare])],
              [ AS_IF([ test "$enableval" = "yes" ],
                      [AC_DEFINE([INITRETURN],1,"Can return from tioInit")])])
AC_ARG_ENABLE([gprof],
              [AC_HELP_STRING([--enable-grof],[Enable to use gprof for profiling (default: no)])],
              [ AS_IF([ test "$enableval" = "yes" ],
                      [GPROF="-pg"] )],[ GPROF=""])

AC_ARG_ENABLE( [doc-pdf],
               [AC_HELP_STRING( [--enable-doc-pdf],
                                [Enable genrtate documentation in PDF format] )],
               [AS_IF( [ test "$enableval" = "yes" ],
                       [ LATEX=latex ; LATEXYES=YES; INSTALL_PDF_DOCS=install-pdf-docs ], 
                       [ LATEXYES=NO ] )],
               [LATEXYES=NO] )
AC_ARG_ENABLE( [doc-deep],
               [AC_HELP_STRING([--enable-doc-deep], [Enable documentate all parts of program])],
               [ AS_IF([ test "$enableval" = "yes" ],
                       [ DEEPDOC=YES ], [ DEEPDOC=NO ]) ], [ DEEPDOC=NO ] )


## Настройки сборки библиотеки

AC_ARG_ENABLE( [static],
               [AC_HELP_STRING([--enable-static], 
                               [Generate library for static linking library (default: no)])], 
               [ AS_IF([ test "$enableval" = "yes" ],
                       [ STATIC=static ]) ], [ STATIC="" ] )
AC_ARG_ENABLE( [dynamic],
               [AC_HELP_STRING([--enable-dynamic], 
                               [Generate library for dynamic linking library (default: yes)])], 
               [ AS_IF([ test "$enableval" = "yes" ],
                       [ DYNAMIC=dynamic ]) ], [  DYNAMIC=dynamic ] )
AS_IF([ test -z "$STATIC" && test -z "$DYNAMIC" ],
      [AC_MSG_ERROR("Any lib generation disable")])

## Настройки локализации для будующей библиотеки

AC_ARG_WITH( [locale], 
             [AC_HELP_STRING([--with-locale=<locale>],
                             [Compile library with mssages on selected locale (default ru_RU.UTF-8)])],
                             [MLOCALE=$withval],[MLOCALE=ru_RU.UTF-8])

if test "$MLOCALE" = "no" ; then
   MLOCALE="C";
fi

if test "$MLOCALE" = "yes" || test -z "$MLOCALE" ; then
   if test -n "$LANG"; then
      MLOCALE=$LANG;
   else
      MLOCALE="C";
   fi;
fi;

AC_SUBST([MLOCALE])

AC_MSG_RESULT([Selected locale $MLOCALE])

AC_SUBST([LATEX])
AC_SUBST([LATEXYES])
AC_SUBST([DEEPDOC])
AC_SUBST([STATIC])
AC_SUBST([DYNAMIC])
AC_SUBST([INSTALL_PDF_DOCS])
AC_SUBST([INSTALLDOCS])


#AC_PROG_CXX
AC_PROG_CC_STDC
AC_PROG_MAKE_SET
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MKDIR_P


AC_CHECK_PROG([CP], [cp], [cp -f])
AS_IF([ test -z "$CP" ], [AC_MSG_ERROR("Not found cp utilit")])

AC_CHECK_PROG([AR], [ar], [ar cur])
AS_IF([ test -n "$STATIC" && test -z "$AR" ], 
      [ AC_MSG_ERROR([No ar tool found, for build static library]) ])

AC_CHECK_PROG([RANLIB], [ranlib], [ranlib])
AS_IF([ test -n "$STATIC" && test -z "$RANLIB" ], 
        [AC_MSG_ERROR([No ranlib tool found, for build static library])])

AS_IF( [ test -n "$GPROF" ], 
       [ AC_CHECK_PROG([THEGPROF],[gprof],[yes],[no]) ])

AS_IF( [ test "$THEGPROF" = "no" ],
       [ AC_MSG_WARN("It sims thet you have no gprof") ] )

CFLAGS="$CFLAGS $GPROF"
#AC_CHECK_PROG([HG], [hg], [hg --template "r{node|short}_{date|shortdate}"])
AC_CHECK_PROG([HG], [hg], [hg])

if test -n "$HG" ; then
   HG="hg parents --template '{rev}'";
   MAKEVERSION=makeversion ;
else
   MAKEVERSION="" ;
fi;

AC_SUBST([HG])
AC_SUBST([MAKEVERSION])
AC_SUBST([LN_S])
AC_SUBST([CFLAGS])
        
# Checks for programs.
AC_PROG_AWK


# Checks for libraries.
# FIXME: Replace `main' with a function in `-lpthread':
AC_CHECK_LIB([pthread], [pthread_mutex_lock],,AC_MSG_ERROR(["No POSIX threads suport"]))
#AC_CHECK_LIB([m], [pow],,AC_MSG_ERROR(["No math 0_o it\'s imposable"]))
AC_CHECK_SIZEOF([pthread_t])
AC_CHECK_SIZEOF([long long])
AC_CHECK_SIZEOF([long])

# Checks for header files.
AC_CHECK_HEADERS([float.h limits.h stdlib.h string.h pthread.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([strerror])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/tests/Makefile
                 Doxyfile
                 src/tools/inlocgen.sh])
AC_OUTPUT
