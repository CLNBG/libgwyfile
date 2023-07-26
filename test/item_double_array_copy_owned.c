/*
 * $Id: item_double_array_copy_owned.c 363 2022-02-10 12:15:04Z yeti-dn $
 *
 * Test double array item with copied and owned data.
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
    const double value[] = { -1.0, 3.141592, 1e38 };

    item = gwyfile_item_new_double_array_copy("item", value, len);
    assert(item);
    assert(gwyfile_item_type(item) == GWYFILE_ITEM_DOUBLE_ARRAY);
    assert(gwyfile_item_owns_data(item));
    assert(strcmp(gwyfile_item_name(item), "item") == 0);
    assert(gwyfile_item_array_length(item) == len);
    assert(memcmp(gwyfile_item_get_double_array(item), value,
                  len*sizeof(double)) == 0);
    assert(gwyfile_item_get_double_array(item) != value);
    gwyfile_item_free(item);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
