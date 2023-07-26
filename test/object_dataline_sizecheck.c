/*
 * $Id: object_dataline_sizecheck.c 365 2022-02-10 12:51:29Z yeti-dn $
 *
 * Test GwyDataLine object data size check.
 *
 * I, the copyright holder of this work, release this work into the public domain.  This applies worldwide.  In some
 * countries this may not be legally without any conditions, unless such conditions are required by law.
 * without any conditions, unless such conditions are required by law.
 */
#include "common.h"

int
main(void)
{
    static const double data[] = { 1.0, 3.0, -42.0 };
    int32_t res;
    GwyfileObject *object;

    object = gwyfile_object_new("GwyDataLine",
                                gwyfile_item_new_int32("res", 2),
                                gwyfile_item_new_double_array_copy("data", data, 3),
                                NULL);
    assert(object);
    assert(strcmp(gwyfile_object_name(object), "GwyDataLine") == 0);
    assert(!gwyfile_object_dataline_get(object, NULL,
                                        "res", &res,
                                        NULL));

    gwyfile_object_free(object);

    object = gwyfile_object_new("GwyDataLine",
                                gwyfile_item_new_double_array_copy("data", data, 3),
                                NULL);
    assert(object);
    assert(strcmp(gwyfile_object_name(object), "GwyDataLine") == 0);
    assert(!gwyfile_object_dataline_get(object, NULL,
                                        "res", &res,
                                        NULL));

    gwyfile_object_free(object);

    object = gwyfile_object_new("GwyDataLine",
                                gwyfile_item_new_int32("res", 2),
                                NULL);
    assert(object);
    assert(strcmp(gwyfile_object_name(object), "GwyDataLine") == 0);
    assert(!gwyfile_object_dataline_get(object, NULL,
                                        "res", &res,
                                        NULL));

    gwyfile_object_free(object);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
