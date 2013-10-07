AC_INIT([rocnroll], [0.01], [wissenschaft@bargsten.org],[http://wissenschaft.bargsten.org])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])

AC_LANG_PUSH([C++])
AC_CONFIG_MACRO_DIR([m4])

AC_PROG_CC
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_0X

AC_ARG_WITH( [h5], [AS_HELP_STRING([--with-h5], [support h5 @<:@default=no@:>@])], [], [with_h5=no])
          
LIBH5=
USE_LIBH5=0
AS_IF([test "x$with_h5" != xno],[
  AC_CHECK_HEADERS([H5Cpp.h],[
      AX_CXX_CHECK_LIB(hdf5_cpp,H5::H5File,[
          AC_SUBST([LIBH5], ["-lhdf5_cpp -lhdf5 -lsz"])
          AC_SUBST([USE_LIBH5], [1])
          AC_DEFINE([HAVE_LIBH5], [1], [Define if you have libh5])
          USE_LIBH5=1
        ],
        [AC_MSG_FAILURE([--with-h5 was given, but test for h5 failed])],
        [-lhdf5 -lsz]
      )
    ],
    [AC_MSG_FAILURE([--with-h5 was given, but test for h5 failed])],
  )
])

AM_CONDITIONAL([USE_LIBH5], [test "$with_h5" != no -a "$USE_LIBH5" -eq 1])
#AC_CHECK_LIB([hdf5],[H5Fcreate])



AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
