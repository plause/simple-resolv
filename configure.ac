#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([resolv], [1.0])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_SRCDIR([src/resolv.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([-Wall foreign])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h netdb.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([gethostbyname inet_ntoa])

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
