/*
 * $Id: object_lawn_sizecheck.c 388 2022-02-11 13:23:43Z yeti-dn $
 *
 * Test GwyLawn object data size check.
 *
 * I, the copyright holder of this work, release this work into the public domain.  This applies worldwide.  In some
 * countries this may not be legally without any conditions, unless such conditions are required by law.
 * without any conditions, unless such conditions are required by law.
 */
#include "common.h"

int
main(void)
{
    static const double data[] = {
                                     /* curve (0,0), length = 0 */
        1.0, 3.0, -42.0, 2.0, 0.0,   /* curve (1,0), length = 5 */
        -14.5, 3.75,                 /* curve (0,1), length = 2 */
        0.0, 0.5, -7.0,              /* curve (1,1), length = 3 */
    };
    static const int32_t curvelengths[] = { 0, 5, 2, 3 };
    static const int32_t badcurvelengths1[] = { 1, 5, 2, 3 };
    static const int32_t badcurvelengths2[] = { 0, 5, 1, 3 };
    static const int32_t badcurvelengths3[] = { 5, 3, 2 };
    int32_t xres, yres, ncurves;
    GwyfileObject *object;

    object = gwyfile_object_new("GwyLawn",
                                gwyfile_item_new_int32("xres", 2),
                                gwyfile_item_new_int32("yres", 3),
                                gwyfile_item_new_int32("ncurves", 1),
                                gwyfile_item_new_int32_array_copy("curvelengths", curvelengths, 4),
                                gwyfile_item_new_double_array_copy("data", data, 10),
                                NULL);
    assert(object);
    assert(strcmp(gwyfile_object_name(object), "GwyLawn") == 0);

    assert(!gwyfile_object_lawn_get(object, NULL,
                                    "xres", &xres,
                                    "yres", &yres,
                                    "ncurves", &ncurves,
                                    NULL));

    gwyfile_object_free(object);

    object = gwyfile_object_new("GwyLawn",
                                gwyfile_item_new_int32("xres", 2),
                                gwyfile_item_new_int32("yres", 2),
                                gwyfile_item_new_int32("ncurves", 1),
                                gwyfile_item_new_int32_array_copy("curvelengths", badcurvelengths1, 4),
                                gwyfile_item_new_double_array_copy("data", data, 10),
                                NULL);
    assert(object);
    assert(strcmp(gwyfile_object_name(object), "GwyLawn") == 0);

    assert(!gwyfile_object_lawn_get(object, NULL,
                                    "xres", &xres,
                                    "yres", &yres,
                                    "ncurves", &ncurves,
                                    NULL));

    gwyfile_object_free(object);

    object = gwyfile_object_new("GwyLawn",
                                gwyfile_item_new_int32("xres", 2),
                                gwyfile_item_new_int32("yres", 2),
                                gwyfile_item_new_int32("ncurves", 1),
                                gwyfile_item_new_int32_array_copy("curvelengths", badcurvelengths2, 4),
                                gwyfile_item_new_double_array_copy("data", data, 10),
                                NULL);
    assert(object);
    assert(strcmp(gwyfile_object_name(object), "GwyLawn") == 0);

    assert(!gwyfile_object_lawn_get(object, NULL,
                                    "xres", &xres,
                                    "yres", &yres,
                                    "ncurves", &ncurves,
                                    NULL));

    gwyfile_object_free(object);

    object = gwyfile_object_new("GwyLawn",
                                gwyfile_item_new_int32("xres", 2),
                                gwyfile_item_new_int32("yres", 2),
                                gwyfile_item_new_int32("ncurves", 1),
                                gwyfile_item_new_int32_array_copy("curvelengths", badcurvelengths3, 3),
                                gwyfile_item_new_double_array_copy("data", data, 10),
                                NULL);
    assert(object);
    assert(strcmp(gwyfile_object_name(object), "GwyLawn") == 0);

    assert(!gwyfile_object_lawn_get(object, NULL,
                                    "xres", &xres,
                                    "yres", &yres,
                                    "ncurves", &ncurves,
                                    NULL));

    gwyfile_object_free(object);

    object = gwyfile_object_new("GwyLawn",
                                gwyfile_item_new_int32("xres", 2),
                                gwyfile_item_new_int32("yres", 2),
                                gwyfile_item_new_int32("ncurves", 2),
                                gwyfile_item_new_int32_array_copy("curvelengths", curvelengths, 4),
                                gwyfile_item_new_double_array_copy("data", data, 10),
                                NULL);
    assert(object);
    assert(strcmp(gwyfile_object_name(object), "GwyLawn") == 0);

    assert(!gwyfile_object_lawn_get(object, NULL,
                                    "xres", &xres,
                                    "yres", &yres,
                                    "ncurves", &ncurves,
                                    NULL));

    gwyfile_object_free(object);

    object = gwyfile_object_new("GwyLawn",
                                gwyfile_item_new_int32("yres", 2),
                                gwyfile_item_new_int32("ncurves", 1),
                                gwyfile_item_new_int32_array_copy("curvelengths", curvelengths, 4),
                                gwyfile_item_new_double_array_copy("data", data, 10),
                                NULL);
    assert(object);
    assert(strcmp(gwyfile_object_name(object), "GwyLawn") == 0);

    assert(!gwyfile_object_lawn_get(object, NULL,
                                    "xres", &xres,
                                    "yres", &yres,
                                    "ncurves", &ncurves,
                                    NULL));

    gwyfile_object_free(object);

    object = gwyfile_object_new("GwyLawn",
                                gwyfile_item_new_int32("xres", 2),
                                gwyfile_item_new_int32("ncurves", 1),
                                gwyfile_item_new_int32_array_copy("curvelengths", curvelengths, 4),
                                gwyfile_item_new_double_array_copy("data", data, 10),
                                NULL);
    assert(object);
    assert(strcmp(gwyfile_object_name(object), "GwyLawn") == 0);

    assert(!gwyfile_object_lawn_get(object, NULL,
                                    "xres", &xres,
                                    "yres", &yres,
                                    "ncurves", &ncurves,
                                    NULL));

    gwyfile_object_free(object);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
