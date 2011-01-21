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
GHashTable *possible_responses = NULL;

int _connection_values_to_hash_table (gpointer cls,
                                     enum MHD_ValueKind kind,
                                     const gchar *key,
                                     const gchar *value)
{
    g_hash_table_replace((GHashTable *)cls, (gchar *)key, (gchar *)value);
    return MHD_YES;
}

void _gh_match_response (gpointer key, gpointer value, gpointer user_data)
{
    GHRequest *request = user_data;
    GError *error = NULL;
    gchar *regex_string = key;
    gboolean matches = g_regex_match_simple(regex_string, request->url, G_REGEX_EXTENDED, G_REGEX_MATCH_ANCHORED);
    GHResponse *response = NULL;
    GHResponseCallback callback = value;
    if (matches == TRUE) {
        response = callback(request);
        //response = MHD_create_response_from_data (strlen(rendered), (void*)rendered, MHD_YES, MHD_YES);
        request->queue_code = MHD_queue_response(request->connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);

        time_t curtime;
        struct tm *loctime;
        curtime = time (NULL);
        loctime = localtime (&curtime);

        printf("\033[1;37m%s \033[1;33m%s\033[0m - \033[1;32m200 OK\033[0m - \033[1;30m%s\033[0m", request->method, request->url, asctime(loctime));
    }
}

int gh_response (void *cls,
                 GHConnection *connection,
                 const char *url,
                 const char *method,
                 const char *version,
                 const char *upload_data,
                 size_t *upload_data_size,
                 void **con_cls)
{
    GHResponse *response = NULL;
    GHRequest *request = g_new0(GHRequest, 1);
    request->connection = connection;
    request->url = (gchar *)url;
    request->method = (gchar *)method;
    request->http_version = (gchar *)version;
    request->upload_data = (gchar *)upload_data;
    request->upload_data_size = upload_data_size;
    request->parameters = g_hash_table_new(g_str_hash, g_str_equal);
    request->cookies = g_hash_table_new(g_str_hash, g_str_equal);
    request->post_data = g_hash_table_new(g_str_hash, g_str_equal);
    request->queue_code = 0;

    MHD_get_connection_values(connection, MHD_GET_ARGUMENT_KIND, &_connection_values_to_hash_table, request->parameters);
    MHD_get_connection_values(connection, MHD_POSTDATA_KIND, &_connection_values_to_hash_table, request->post_data);
    MHD_get_connection_values(connection, MHD_COOKIE_KIND, &_connection_values_to_hash_table, request->cookies);

    if (possible_responses !=NULL) {
        g_hash_table_foreach(possible_responses, _gh_match_response, (gpointer)request);
        g_hash_table_unref(request->parameters);
        g_hash_table_unref(request->post_data);
        g_hash_table_unref(request->cookies);

        if (request->queue_code != 0) {
            return request->queue_code;
        }
    }

    int queue_code;
    const gchar* response404 = "<html><head></head><body><h1>404 - not found</h1></body></html>";
    response = MHD_create_response_from_data(strlen(response404), (void*)response404, MHD_NO, MHD_NO);
    queue_code = MHD_queue_response(request->connection, 404, response);
    time_t curtime;
    struct tm *loctime;
    curtime = time (NULL);
    loctime = localtime (&curtime);

    printf("\033[1;37m%s \033[1;33m%s\033[0m - \033[1;31m404 NOT FOUND\033[0m - \033[1;30m%s\033[0m", request->method, request->url, asctime(loctime));

    return queue_code;
}

void _gh_register_response(const gchar* regex, GHResponseCallback callback, gpointer data){
    if (possible_responses == NULL) {
        possible_responses = g_hash_table_new(g_str_hash, g_str_equal);
    }
    g_hash_table_replace(possible_responses, (gchar *)regex, callback);
}

GOHorseDaemon *gh_run_server(int port) {
    GOHorseDaemon *d = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, port, NULL, NULL, &gh_response, NULL, MHD_OPTION_END);
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

GHResponse* a_new_response(gchar *string) {
    return MHD_create_response_from_data(strlen(string), (void*)string, MHD_NO, MHD_NO);
}
