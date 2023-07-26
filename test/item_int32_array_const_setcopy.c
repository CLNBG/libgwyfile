/*
 * $Id: item_int32_array_const_setcopy.c 363 2022-02-10 12:15:04Z yeti-dn $
 *
 * Test int32 array item with constant and copied data.
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
    const int32_t value[] = { -1, 3, INT32_MAX };
    unsigned int newlen = 4;
    const int32_t newvalue[] = { 4, 5, 7, INT32_MIN };

    item = gwyfile_item_new_int32_array_const("item", value, len);
    assert(item);
    assert(gwyfile_item_type(item) == GWYFILE_ITEM_INT32_ARRAY);
    gwyfile_item_set_int32_array_copy(item, newvalue, newlen);
    assert(gwyfile_item_owns_data(item));
    assert(strcmp(gwyfile_item_name(item), "item") == 0);
    assert(gwyfile_item_array_length(item) == newlen);
    assert(memcmp(gwyfile_item_get_int32_array(item), newvalue,
                  newlen*sizeof(int32_t)) == 0);
    assert(gwyfile_item_get_int32_array(item) != newvalue);
    gwyfile_item_free(item);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
