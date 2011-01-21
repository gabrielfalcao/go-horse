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
#include "tdd.h"
#include "mustache.h"

i_think_it(should_render_simple_variable_for_hello_world)

    GHashTable *context = g_hash_table_new(g_str_hash, g_str_equal);
    g_hash_table_replace(context, "variable", "World");

    char *rendered = mustache_render("Hello {{ variable }}", context);
    assert_equals(rendered, "Hello World");

just_for_sure

i_think_it(should_render_many_variables)

    GHashTable *context = g_hash_table_new(g_str_hash, g_str_equal);
    g_hash_table_replace(context, "variable", "World");
    g_hash_table_replace(context, "name", "Fabio");

    char *rendered = mustache_render("Hello {{ variable }}, {{ name }}", context);
    assert_equals(rendered, "Hello World, Fabio");

just_for_sure

int main (int argc, char **argv) {
    should_render_simple_variable_for_hello_world();
    should_render_many_variables();
    return 0;
}
