bin_PROGRAMS = server tests
server_SOURCES = gohorse.c mustache.c main.c
tests_SOURCES = test.c mustache.c
server_CFLAGS = $(GLIB_CFLAGS) $(LIBMICROHTTPD_CFLAGS) -fnested-functions
server_LDADD = $(GLIB_LIBS) $(LIBMICROHTTPD_LIBS)

tests_CFLAGS = $(GLIB_CFLAGS) $(LIBMICROHTTPD_CFLAGS)
tests_LDADD = $(GLIB_LIBS) $(LIBMICROHTTPD_LIBS)
