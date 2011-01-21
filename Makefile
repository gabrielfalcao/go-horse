OPTS := `pkg-config --libs --cflags glib-2.0 libmicrohttpd` mustache.{c,h} gohorse.{c,h} -fnested-functions

compile:
	@gcc main.c -o server $(OPTS)

test:
	@gcc test.c -o run-tests $(OPTS)
	@./run-tests

all: compile runserver

runserver: compile
	@./server

