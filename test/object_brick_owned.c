/*
 * $Id: object_brick_owned.c 363 2022-02-10 12:15:04Z yeti-dn $
 *
 * Test GwyBrick object constructor and extractor with owned data.
 *
 * I, the copyright holder of this work, release this work into the public domain.  This applies worldwide.  In some
 * countries this may not be legally without any conditions, unless such conditions are required by law.
 * without any conditions, unless such conditions are required by law.
 */
#include "common.h"

int
main(void)
{
    static const double data[] = { 1.0, 3.0, -42.0, 2.0, 3.0, 0.0 };
    double *dataowned, *data2;
    const double *data3;
    double xreal, yreal, zreal, xoff, yoff, zoff;
    int32_t xres, yres, zres;
    char *xunit, *yunit, *zunit, *wunit;
    GwyfileObject *brick;

    dataowned = malloc(1*2*3*sizeof(double));
    memcpy(dataowned, data, 1*2*3*sizeof(double));
    brick = gwyfile_object_new_brick(3, 2, 1, 6.0, 4.0, 2.0,
                                     "data", dataowned,
                                     "si_unit_x", "m",
                                     "si_unit_y", "A",
                                     "si_unit_z", "s",
                                     "si_unit_w", "deg",
                                     NULL);
    assert(brick);
    assert(strcmp(gwyfile_object_name(brick), "GwyBrick") == 0);
    gwyfile_object_add(brick, gwyfile_item_new_int32("EXTRA_ITEM", -10));

    assert(gwyfile_object_brick_get(brick, NULL,
                                    "xres", &xres,
                                    "yres", &yres,
                                    "zres", &zres,
                                    "xreal", &xreal,
                                    "yreal", &yreal,
                                    "zreal", &zreal,
                                    "xoff", &xoff,
                                    "yoff", &yoff,
                                    "zoff", &zoff,
                                    "si_unit_x", &xunit,
                                    "si_unit_y", &yunit,
                                    "si_unit_z", &zunit,
                                    "si_unit_w", &wunit,
                                    NULL));
    assert(xres == 3);
    assert(yres == 2);
    assert(zres == 1);
    assert(xreal == 6.0);
    assert(yreal == 4.0);
    assert(zreal == 2.0);
    assert(xoff == 0.0);
    assert(yoff == 0.0);
    assert(zoff == 0.0);
    assert(strcmp(xunit, "m") == 0);
    assert(strcmp(yunit, "A") == 0);
    assert(strcmp(zunit, "s") == 0);
    assert(strcmp(wunit, "deg") == 0);

    free(wunit);
    free(zunit);
    free(yunit);
    free(xunit);

    assert(gwyfile_object_brick_get(brick, NULL, "data", &data3, NULL));
    assert(memcmp(data3, data, 1*2*3*sizeof(double)) == 0);

    assert(gwyfile_object_brick_get(brick, NULL, "data(take)", &data2, NULL));
    assert(memcmp(data2, data, 1*2*3*sizeof(double)) == 0);

    assert(gwyfile_object_brick_get(brick, NULL, "data", &data3, NULL));
    assert(memcmp(data3, data, 1*2*3*sizeof(double)) == 0);

    gwyfile_object_free(brick);
    free(data2);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
