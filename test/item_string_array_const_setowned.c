/*
 * $Id: item_string_array_const_setowned.c 363 2022-02-10 12:15:04Z yeti-dn $
 *
 * Test string array item with constant and owned data.
 *
 * I, the copyright holder of this work, release this work into the public domain.  This applies worldwide.  In some
 * countries this may not be legally without any conditions, unless such conditions are required by law.
 * without any conditions, unless such conditions are required by law.
 */
#include "common.h"

int
main(void)
{
    GwyfileItem *item;
    unsigned int len = 3;
    const char *const value[] = { "abc", "def", "" };
    unsigned int newlen = 4;
    const char *const newconstvalue[] = { "yuck", "", "$", "Hello world!" };
    unsigned int i;
    const char *const *v;
    char **newvalue = memcpy(malloc(newlen*sizeof(char*)), newconstvalue,
                             newlen*sizeof(char*));
    for (i = 0; i < newlen; i++) {
        unsigned int l = strlen(newconstvalue[i]);
        newvalue[i] = memcpy(malloc(l + 1), newconstvalue[i], l + 1);
    }

    item = gwyfile_item_new_string_array_const("item", value, len);
    assert(item);
    assert(gwyfile_item_type(item) == GWYFILE_ITEM_STRING_ARRAY);
    gwyfile_item_set_string_array(item, newvalue, newlen);
    assert(gwyfile_item_owns_data(item));
    assert(strcmp(gwyfile_item_name(item), "item") == 0);
    assert(gwyfile_item_array_length(item) == newlen);
    v = gwyfile_item_get_string_array(item);
    for (i = 0; i < newlen; i++) {
        assert(strcmp(v[i], newvalue[i]) == 0);
    }
    assert(gwyfile_item_get_string_array(item) == (const char*const*)newvalue);
    gwyfile_item_free(item);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
