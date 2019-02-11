# Autoconf requirements

# Initialize, but use more options. Note parameters brackts and whitespace.
AC_INIT([SetsCalc], [1.0], [anton2920@gmail.com])

# Safety check - list a source file that wouldn't be in other directories:
AC_CONFIG_SRCDIR([src/main.c])

# Put configuration results here, so we can easily #include them:
AC_CONFIG_HEADERS([config.h])

# Put autotools auxiliary files in a subdir, so they don't clutter top dir:
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

# Enable «automake» to simplify creating makefiles:
AM_INIT_AUTOMAKE([subdir-objects -Wall])
AC_CONFIG_FILES([Makefile])

# Look for a C compiler:
AC_LANG(C)
AC_PROG_CC

# Perhaps check for: (more) programs, libraries, header files, types,
# structures, compiler characteristics, library functions, system services.

# Do final output.
AC_OUTPUT
