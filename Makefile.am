SUBDIRS = include
bin_PROGRAMS = server tests
server_SOURCES = gohorse.c mustache.c main.c
tests_SOURCES = test.c mustache.c tdd.h
server_CFLAGS = $(GLIB_CFLAGS) $(LIBMICROHTTPD_CFLAGS) -fnested-functions -I$(top_srcdir)/include
server_LDADD = $(GLIB_LIBS) $(LIBMICROHTTPD_LIBS)

tests_CFLAGS = $(GLIB_CFLAGS) $(LIBMICROHTTPD_CFLAGS) -I$(top_srcdir)/include
tests_LDADD = $(GLIB_LIBS) $(LIBMICROHTTPD_LIBS)
