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

int main() {


    GET("/",
        render(
            "<html>"
            "  <head>"
            "    <title>Welcome to GO-Horse</title>"
            "  </head>"
            "  <body>"
            "    <h1>Welcome to GO-Horse</h1>"
            "    <h3>you can go to one of these URLs:</h3>"
            "    <ul>"
            "      <li><a href=\"/001122334455\">regex that match numbers</a></li>"
            "      <li><a href=\"/aAbBcCdD\">regex that match letters</a></li>"
            "    </ul>"
            "  </body>"
            "</html>"
        );
    )

    GET("/[a-zA-Z]+",
        gchar *path = g_strstrip(g_strdelimit(g_strdup(request->url), "/", ' '));
        render(
            "<html>"
            "  <head>"
            "    <title>Welcome to GO-Horse</title>"
            "  </head>"
            "  <body>"
            "    <h1>Welcome to GO-Horse</h1>"
            "    <h2>this controller match letters</h2>"
            "    <h3>and you choose <em>\"%s\"</em></h3>"
            "  </body>"
            "</html>",
            path
        );
    )

    GET("/\\d+",
        gchar *path = g_strstrip(g_strdelimit(g_strdup(request->url), "/", ' '));
        render(
            "<html>"
            "  <head>"
            "    <title>Welcome to GO-Horse</title>"
            "  </head>"
            "  <body>"
            "    <h1>Welcome to GO-Horse</h1>"
            "    <h2>this controller match numbers</h2>"
            "    <h3>and you choose <em>\"%s\"</em></h3>"
            "  </body>"
            "</html>",
            path
        );
    )

    GO_HORSE();
    return 0;
}


