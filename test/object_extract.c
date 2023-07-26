/*
 * $Id: object_extract.c 363 2022-02-10 12:15:04Z yeti-dn $
 *
 * Test taking out items from objects.
 *
 * I, the copyright holder of this work, release this work into the public domain.  This applies worldwide.  In some
 * countries this may not be legally without any conditions, unless such conditions are required by law.
 * without any conditions, unless such conditions are required by law.
 */
#include "common.h"

int
main(void)
{
    GwyfileObject *object, *sub;
    GwyfileItem *item;

    object = gwyfile_object_new("Main",
                                gwyfile_item_new_int32("i", 42),
                                gwyfile_item_new_object("o",
                                                        gwyfile_object_new("Sub",
                                                                           gwyfile_item_new_bool("b", true),
                                                                           NULL)),
                                NULL);
    assert(object);

    item = gwyfile_object_take(object, "o");
    assert(item);
    assert(gwyfile_item_type(item) == GWYFILE_ITEM_OBJECT);
    assert(strcmp(gwyfile_item_name(item), "o") == 0);

    sub = gwyfile_item_release_object(item);
    assert(sub);
    assert(strcmp(gwyfile_object_name(sub), "Sub") == 0);
    assert(gwyfile_object_get_with_type(sub, "b", GWYFILE_ITEM_BOOL));

    gwyfile_object_free(sub);
    gwyfile_object_free(object);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
