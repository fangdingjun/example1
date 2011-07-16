#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.64])
AC_INIT([shellexec], [0.1], [fangdingjun@gmail.com])
AC_CONFIG_SRCDIR([header.h])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE(shellexec,0.1)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_RANLIB

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lICE':
#AC_CHECK_LIB([ICE], [main])
# FIXME: Replace `main' with a function in `-lQtCore':
#AC_CHECK_LIB([QtCore], [main])
# FIXME: Replace `main' with a function in `-lQtGui':
#AC_CHECK_LIB([QtGui], [main])
# FIXME: Replace `main' with a function in `-lSM':
#AC_CHECK_LIB([SM], [main])
# FIXME: Replace `main' with a function in `-lX11':
#AC_CHECK_LIB([X11], [main])
# FIXME: Replace `main' with a function in `-lXext':
#AC_CHECK_LIB([Xext], [main])
# FIXME: Replace `main' with a function in `-lXrender':
#AC_CHECK_LIB([Xrender], [main])
# FIXME: Replace `main' with a function in `-ldl':
#AC_CHECK_LIB([dl], [main])
# FIXME: Replace `main' with a function in `-lfontconfig':
#AC_CHECK_LIB([fontconfig], [main])
# FIXME: Replace `main' with a function in `-lfreetype':
#AC_CHECK_LIB([freetype], [main])
# FIXME: Replace `main' with a function in `-lm':
#AC_CHECK_LIB([m], [cos])
# FIXME: Replace `main' with a function in `-lpng':
#AC_CHECK_LIB([png], [main])
# FIXME: Replace `main' with a function in `-lpthread':
#AC_CHECK_LIB([pthread], [pthread_create])
# FIXME: Replace `main' with a function in `-lrt':
#AC_CHECK_LIB([rt], [main])
# FIXME: Replace `main' with a function in `-lz':
#AC_CHECK_LIB([z], [main])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h netdb.h netinet/in.h stdlib.h string.h sys/ioctl.h sys/socket.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_PID_T

# Checks for library functions.
AC_FUNC_ALLOCA
AC_FUNC_FORK
AC_CHECK_FUNCS([gethostbyname inet_ntoa memset pow socket])

AC_CONFIG_FILES([Makefile
                 gtk/Makefile
                 wx/Makefile])
AC_OUTPUT
