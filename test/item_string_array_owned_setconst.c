/*
 * $Id: item_string_array_owned_setconst.c 363 2022-02-10 12:15:04Z yeti-dn $
 *
 * Test string array item with owned and constant data.
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
    const char *const constvalue[] = { "abc", "def", "" };
    unsigned int newlen = 4;
    const char *const newconstvalue[] = { "yuck", "", "$", "Hello world!" };
    unsigned int i;
    const char *const *v;
    char **value = memcpy(malloc(len*sizeof(char*)), constvalue,
                          len*sizeof(char*));
    for (i = 0; i < len; i++) {
        unsigned int l = strlen(constvalue[i]);
        value[i] = memcpy(malloc(l + 1), constvalue[i], l + 1);
    }

    item = gwyfile_item_new_string_array("item", value, len);
    assert(item);
    assert(gwyfile_item_type(item) == GWYFILE_ITEM_STRING_ARRAY);
    gwyfile_item_set_string_array_const(item, newconstvalue, newlen);
    assert(!gwyfile_item_owns_data(item));
    assert(strcmp(gwyfile_item_name(item), "item") == 0);
    assert(gwyfile_item_array_length(item) == newlen);
    v = gwyfile_item_get_string_array(item);
    for (i = 0; i < newlen; i++) {
        assert(strcmp(v[i], newconstvalue[i]) == 0);
    }
    assert(gwyfile_item_get_string_array(item) == newconstvalue);
    gwyfile_item_free(item);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
