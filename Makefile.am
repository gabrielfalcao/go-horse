bin_PROGRAMS = server tests
server_SOURCES = gohorse.c mustache.c
tests_SOURCES = test.c mustache.c
server_CFLAGS = $(GLIB_CFLAGS) $(LIBMICROHTTPD_CFLAGS)
server_LDFLAGS = $(GLIB_LDFLAGS) $(LIBMICROHTTPD_LDFLAGS)

tests_CFLAGS = $(GLIB_CFLAGS)
tests_LDFLAGS = $(GLIB_LDFLAGS)
