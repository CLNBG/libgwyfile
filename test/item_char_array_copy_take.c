/*
 * $Id: item_char_array_copy_take.c 363 2022-02-10 12:15:04Z yeti-dn $
 *
 * Test character array item with copied and taken data.
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
    char *takenvalue;

    item = gwyfile_item_new_char_array_copy("item", value, len);
    assert(item);
    assert(gwyfile_item_type(item) == GWYFILE_ITEM_CHAR_ARRAY);
    takenvalue = gwyfile_item_take_char_array(item);
    assert(!gwyfile_item_owns_data(item));
    assert(strcmp(gwyfile_item_name(item), "item") == 0);
    assert(gwyfile_item_array_length(item) == len);
    assert(memcmp(gwyfile_item_get_char_array(item), value,
                  len*sizeof(char)) == 0);
    assert(memcmp(gwyfile_item_get_char_array(item), takenvalue,
                  len*sizeof(char)) == 0);
    assert(gwyfile_item_get_char_array(item) == takenvalue);
    gwyfile_item_free(item);
    assert(memcmp(value, takenvalue, len*sizeof(char)) == 0);
    free(takenvalue);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
