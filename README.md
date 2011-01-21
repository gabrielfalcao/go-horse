# go-horse

Funny, and simple HTTP Server DSL written entirely in C

## crash course

**go-horse** tries to make funnier to program in C, it has macros and
  helpers to make your code look like *beauty*.

### step 1

after installed, edit the file main.c

### step 2

use the macro `GET` to map as many URL's you want, followed by the
code that returns a string to be returned

example:

    #import "gohorse.h"

    int main() {
        GET("/",
            render("Hello World!");
        )
        GET("/foo",
            render("<html><body><h1>Foo Bar</h1></body></html>");
        )
        GO_HORSE();
        return 0;
    }

### step 3

build with:

    make compile

run with

    ./server

### step 4

ENJOY THE RIDE :)

# furthermore

## instalation

### Mac OS

1. Install [home brew](http://github.com/mxcl/homebrew)
2. Install dependencies through: `sudo brew install libmicrohttpd glib`

## running tests

    make test

## writting tests

    #import "tdd.h"

    i_think_it(should_be_my_test_name)
        assert_equals("foo", "foo");
    just_for_sure

yeah that is C with macros :)

## compiling

    make compile

## running

    ./server

it runs on port 8888
