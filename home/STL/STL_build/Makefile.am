AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = -I m4
AM_CFLAGS = -fPIC -Wall -Wextra -std=c++11

EXTRA_DIST = autogen.sh 

bin_PROGRAMS = ProTest

ProTest_SOURCES = main.cpp

lib_LTLIBRARIES = libSTL.la
libSTL_la_SOURCES = ../STL_Stack.c
include_HEADERS = STL.h