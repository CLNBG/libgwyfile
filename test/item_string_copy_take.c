/*
 * $Id: item_string_copy_take.c 363 2022-02-10 12:15:04Z yeti-dn $
 *
 * Test string item with copied and taken data.
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
    char *value;

    item = gwyfile_item_new_string_copy("item", "value");
    assert(item);
    assert(gwyfile_item_type(item) == GWYFILE_ITEM_STRING);
    value = gwyfile_item_take_string(item);
    assert(!gwyfile_item_owns_data(item));
    assert(strcmp(gwyfile_item_name(item), "item") == 0);
    assert(strcmp(gwyfile_item_get_string(item), "value") == 0);
    assert(gwyfile_item_get_string(item) == value);
    gwyfile_item_free(item);
    assert(strcmp(value, "value") == 0);
    free(value);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
