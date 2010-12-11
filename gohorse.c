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
#include "mustache.h"

int get_parameters (void *cls, enum MHD_ValueKind kind, const char *key, const char *value)
{
    g_hash_table_replace((GHashTable *)cls, (char *)key, (char *)value);
    return MHD_YES;
}

int gh_response (void *cls,
                 struct MHD_Connection *connection,
                 const char *url,
                 const char *method,
                 const char *version,
                 const char *upload_data,
                 size_t *upload_data_size,
                 void **con_cls)
{
    int ret;
    GHashTable *params = g_hash_table_new(g_str_hash, g_str_equal);
    struct MHD_Response *response;

    MHD_get_connection_values (connection, MHD_GET_ARGUMENT_KIND, &get_parameters, params);

    char *rendered = mustache_render("<html><body><h1>Hello, {{ me }}</h1></body></html>", params);

    response = MHD_create_response_from_data (strlen (rendered), (void*) rendered, MHD_NO, MHD_NO);
    ret = MHD_queue_response (connection, MHD_HTTP_OK, response); MHD_destroy_response (response);

    time_t curtime;
    struct tm *loctime;
    curtime = time (NULL);
    loctime = localtime (&curtime);

    printf("\033[1;37m%s \033[1;32m%s\033[0m - \033[1;30m%s\033[0m", method, url, asctime (loctime));
    return ret;
}

GOHorseDaemon *gh_run_server(int port) {
    GOHorseDaemon *d = MHD_start_daemon (MHD_USE_SELECT_INTERNALLY, port, NULL, NULL, &gh_response, NULL, MHD_OPTION_END);
    if (d is NULL) {
        printf("Could not start GO Horse server on port %d\n", port);
        exit(1);
    }
    printf("GO Horse is running on localhost:%d\n", port);
    while (true) {getchar();}
}

void gh_stop_server (GOHorseDaemon *daemon) {
    MHD_stop_daemon(daemon);
}
