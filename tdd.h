#include <assert.h>
#include <stdbool.h>
#define assert_equals(x, y)  assert(g_strcmp0(x, y) == 0)
#define i_think_it(x) static void x () { \
    g_printf("it %s...\n", #x);

#define just_for_sure }
