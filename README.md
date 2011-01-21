# go-horse

High-scallable, funny and useless http server written entirely in C

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
