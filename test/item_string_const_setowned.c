/*
 * $Id: item_string_const_setowned.c 363 2022-02-10 12:15:04Z yeti-dn $
 *
 * Test string item with constant and owned data.
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
    char *value = strcpy(malloc(9), "newvalue");

    item = gwyfile_item_new_string_const("item", "value");
    assert(item);
    assert(gwyfile_item_type(item) == GWYFILE_ITEM_STRING);
    gwyfile_item_set_string(item, value);
    assert(gwyfile_item_owns_data(item));
    assert(strcmp(gwyfile_item_name(item), "item") == 0);
    assert(strcmp(gwyfile_item_get_string(item), "newvalue") == 0);
    assert(gwyfile_item_get_string(item) == value);
    gwyfile_item_free(item);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
