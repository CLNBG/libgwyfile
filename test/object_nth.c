/*
 * $Id: object_nth.c 363 2022-02-10 12:15:04Z yeti-dn $
 *
 * Test iteration over object items using n-th item accessor.
 *
 * I, the copyright holder of this work, release this work into the public domain.  This applies worldwide.  In some
 * countries this may not be legally without any conditions, unless such conditions are required by law.
 * without any conditions, unless such conditions are required by law.
 */
#include "common.h"

int
main(void)
{
    static struct {
        const char *name;
        GwyfileItemType type;
        unsigned int seen;
    } items[] = {
        { "bool",       GWYFILE_ITEM_BOOL,   0, },
        { "char",       GWYFILE_ITEM_CHAR,   0, },
        { "int32",      GWYFILE_ITEM_INT32,  0, },
        { "anotherint", GWYFILE_ITEM_INT32,  0, },
        { "thirdone",   GWYFILE_ITEM_INT32,  0, },
        { "str",        GWYFILE_ITEM_STRING, 0, },
    };
    enum { nitems = sizeof(items)/sizeof(items[0]) };

    GwyfileObject *object;
    GwyfileItem *item;
    unsigned int n, i, j;

    object = gwyfile_object_new("Test",
                                gwyfile_item_new_bool("bool", true),
                                gwyfile_item_new_char("char", 'X'),
                                gwyfile_item_new_int32("int32", 42),
                                gwyfile_item_new_int32("anotherint", 43),
                                gwyfile_item_new_int32("thirdone", -6),
                                gwyfile_item_new_string_const("str", "Shark"),
                                NULL);

    n = gwyfile_object_nitems(object);
    assert(n == nitems);

    for (i = 0; i < n; i++) {
        item = gwyfile_object_get_nth(object, i);
        for (j = 0; j < nitems; j++) {
            if (strcmp(gwyfile_item_name(item), items[j].name) == 0 && gwyfile_item_type(item) == items[j].type) {
                items[j].seen++;
                break;
            }
        }
    }
    for (j = 0; j < nitems; j++) {
        assert(items[j].seen == 1);
    }

    gwyfile_object_free(object);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
