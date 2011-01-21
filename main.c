// -*- coding: utf-8 -*-
// <gohorse - cowboy http framework for c lovers>
// Copyright (C) <2010>  Gabriel Falcão <gabriel@nacaolivre.org>

// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
#include "gohorse.h"

void quit_app (int sig) {
    printf("\033[D\033[D\033[1;31mserver was shutdown\033[0m\n");
    exit(sig);
}

GHResponse* index_resp(GHRequest *request){
    return a_new_response("Hello!");
}

int main(int argc, char ** argv) {
    GOHorseDaemon *daemon;
    int port = 8888;
    _gh_register_response("/$", index_resp, NULL);

    signal(SIGABRT, quit_app);
    signal(SIGTERM, quit_app);
    signal(SIGINT, quit_app);

    if (argc == 2) {
        port = atoi(argv[1]);
    }
    daemon = gh_run_server(port);
    gh_stop_server(daemon);

    return 0;
}


