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

#include "mustache.h"

void _iterate_over_hash (gpointer _key, gpointer _value, gpointer user_data) {
    GError *err = NULL;
    char *key = (char *) _key;
    char *value = (char *) _value;
    char **ref = user_data;
    char *original = *ref;
    char *pattern = g_strdup_printf("[{]{2}[ ]*%s[ ]*[}]{2}", key);
    GRegex *regex = g_regex_new (pattern, G_REGEX_DOTALL, G_REGEX_MATCH_NEWLINE_ANY, &err);
    char *rendered = g_regex_replace(regex, original, strlen(original), 0, value, G_REGEX_MATCH_NEWLINE_ANY, &err);

    g_free(original);
    *ref = rendered;
    g_free(pattern);
    g_regex_unref(regex);

}

char * mustache_render(const char *raw, GHashTable *context) {
    char *new = g_strdup(raw);
    g_hash_table_foreach(context, _iterate_over_hash, &new);
    return new;
}
