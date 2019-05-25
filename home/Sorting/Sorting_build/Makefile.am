AUTOMAKE_OPTIONS = foreign subdir-objects
ACLOCAL_AMFLAGS = -I m4
AM_CFLAGS = -fPIC -Wall -Wextra -std=c90

EXTRA_DIST = autogen.sh 

lib_LTLIBRARIES = libSTL.la
libSTL_la_SOURCES = ../STL_Stack.c
libSTL_la_CFLAGS = $(AM_CFLAGS)
include_HEADERS = ../STL.h