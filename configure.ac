#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([go-horse], [0.1], [http://github.com/gabrielfalcao/go-horse])
AC_CONFIG_SRCDIR([gohorse.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE(foreign)
AM_SILENT_RULES([yes])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h netdb.h netinet/in.h stddef.h stdint.h stdlib.h string.h sys/socket.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_CHECK_HEADER_STDBOOL

# Checks for .pc packages
PKG_CHECK_MODULES([GLIB], [glib-2.0])
AC_SUBST([GLIB_CFLAGS])
AC_SUBST([GLIB_LIBS])

PKG_CHECK_MODULES([LIBMICROHTTPD], [libmicrohttpd])
AC_SUBST([LIBMICROHTTPD_CFLAGS])
AC_SUBST([LIBMICROHTTPD_LIBS])

# Checks for library functions.

AC_CONFIG_FILES([
        Makefile
        include/Makefile
        include/gohorse/Makefile
])
AC_OUTPUT
