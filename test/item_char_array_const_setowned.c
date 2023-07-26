/*
 * $Id: item_char_array_const_setowned.c 363 2022-02-10 12:15:04Z yeti-dn $
 *
 * Test character array item with constant and owned data.
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
    const char value[] = { -1, 3, 127 };
    unsigned int newlen = 4;
    const char newconstvalue[] = { 4, 5, 7, -1 };
    char *newvalue = memcpy(malloc(newlen*sizeof(char)), newconstvalue,
                            newlen*sizeof(char));

    item = gwyfile_item_new_char_array_const("item", value, len);
    assert(item);
    assert(gwyfile_item_type(item) == GWYFILE_ITEM_CHAR_ARRAY);
    gwyfile_item_set_char_array(item, newvalue, newlen);
    assert(gwyfile_item_owns_data(item));
    assert(strcmp(gwyfile_item_name(item), "item") == 0);
    assert(gwyfile_item_array_length(item) == newlen);
    assert(memcmp(gwyfile_item_get_char_array(item), newvalue,
                  newlen*sizeof(char)) == 0);
    assert(gwyfile_item_get_char_array(item) == newvalue);
    gwyfile_item_free(item);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
