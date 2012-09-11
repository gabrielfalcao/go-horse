SUBDIRS = include
bin_PROGRAMS = go-horse
noinst_PROGRAMS = tests
go_horse_SOURCES = gohorse.c mustache.c main.c
tests_SOURCES = test.c mustache.c tdd.h
go_horse_CFLAGS = $(GLIB_CFLAGS) $(LIBMICROHTTPD_CFLAGS) -fnested-functions -I$(top_srcdir)/include
go_horse_LDADD = $(GLIB_LIBS) $(LIBMICROHTTPD_LIBS)

tests_CFLAGS = $(GLIB_CFLAGS) $(LIBMICROHTTPD_CFLAGS) -I$(top_srcdir)/include
tests_LDADD = $(GLIB_LIBS) $(LIBMICROHTTPD_LIBS)
