AUTOMAKE_OPTIONS = foreign subdir-objects
ACLOCAL_AMFLAGS = -I m4
AM_CFLAGS = -fPIC -Wall -Wextra -std=c90

EXTRA_DIST = autogen.sh 

lib_LTLIBRARIES = libSorting.la
libSorting_la_SOURCES = ../sorting.c ../compare.c ../convertions.c ../others.c ../adv_sorting.c
libSorting_la_CFLAGS = $(AM_CFLAGS)
include_HEADERS = ../sorting.h