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
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stddef.h>
#include <pthread.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <sys/mman.h>
#include <netdb.h>
#include <netinet/in.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <microhttpd.h>
#include <time.h>
#include <glib.h>
#include "mustache.h"

/* DEBUG */
/*********************************************************************/
#define WHERESTR "\033[1;31mDEBUG - \033[1;36m%s:%d - \033[1;33m"
#define WHEREARG __FILE__, __LINE__
#define _gh_debug(...) fprintf(stderr, __VA_ARGS__)
#define gh_debug(_fmt, ...)  _gh_debug(WHERESTR _fmt "\033[0m", WHEREARG, __VA_ARGS__)
/*********************************************************************/

/* DSL */
/*********************************************************************/
#define _GH_GET3(url, ll, data, body) GHResponse* _gh_answer_##ll(GHRequest *request) { body }; _gh_register_response(url, _gh_answer_##ll, data);
#define _GH_GET2(url, ll, data, body) _GH_GET3(url, ll, data, body)
#define _GH_GET1(url, ll, data, body) _GH_GET2(url, ll, data, body)
#define _GH_GET(url, ll, data, body)  _GH_GET1(url, ll, data, body)
#define GET(url, body) _GH_GET("^" url "$", __LINE__, NULL, body)

#define GO_HORSE() GOHorseDaemon *__quick_daemon__; \
    __quick_daemon__ = gh_run_server(8888); \
    gh_stop_server(__quick_daemon__);

/*********************************************************************/

/* HELPERS */
/*********************************************************************/
#define render(string) return a_new_response(string);
#define render_template(string, context) return mustache_render(string, context);
#define is ==
#define true 1
#define false 0
/*********************************************************************/

typedef struct MHD_Daemon GOHorseDaemon;
typedef struct MHD_Response GHResponse;
typedef struct MHD_Connection GHConnection;
typedef struct _GHRequest
{
    GHConnection *connection;
    const gchar *url;
    const gchar *method;
    const gchar *http_version;
    const gchar *upload_data;
    size_t *upload_data_size;
    GHashTable *parameters;
    GHashTable *cookies;
    GHashTable *post_data;
    int queue_code;
} GHRequest;
typedef GHResponse* (*GHResponseCallback) (GHRequest* request);

GOHorseDaemon *gh_run_server(int port);
void gh_stop_server (GOHorseDaemon *daemon);
void _gh_register_response(const gchar* regex, GHResponseCallback callback, gpointer data);
GHResponse* a_new_response(gchar *string);
void gh_exit_program (int sig);
