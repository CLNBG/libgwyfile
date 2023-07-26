/*
 * $Id: object_lawn_nodata.c 392 2022-02-11 15:38:59Z yeti-dn $
 *
 * Test GwyLawn object with all curves empty.
 *
 * I, the copyright holder of this work, release this work into the public domain.  This applies worldwide.  In some
 * countries this may not be legally without any conditions, unless such conditions are required by law.
 * without any conditions, unless such conditions are required by law.
 */
#include "common.h"

int
main(void)
{
    static const int32_t curvelengths[] = { 0, 0 };
    int32_t xres, yres, ncurves;
    GwyfileObject *object;

    object = gwyfile_object_new_lawn(1, 2, 3, 1.0, 1.0,
                                     "curvelengths(copy)", curvelengths,
                                     NULL);
    assert(object);
    assert(strcmp(gwyfile_object_name(object), "GwyLawn") == 0);

    assert(gwyfile_object_lawn_get(object, NULL,
                                   "xres", &xres,
                                   "yres", &yres,
                                   "ncurves", &ncurves,
                                   NULL));

    assert(xres == 1);
    assert(yres == 2);
    assert(ncurves == 3);

    gwyfile_object_free(object);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
