/*
 * $Id: object_brick_const.c 372 2022-02-10 15:34:30Z yeti-dn $
 *
 * Test GwyBrick object constructor and extractor with constant data.
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
    const double *data3;
    double xreal, yreal, zreal, xoff, yoff, zoff;
    int32_t xres, yres, zres;
    char *xunit, *yunit, *zunit, *wunit;
    GwyfileObject *brick;

    brick = gwyfile_object_new_brick(3, 2, 1, 6.0, 4.0, 2.0,
                                     "data(const)", data,
                                     NULL);
    assert(brick);
    assert(strcmp(gwyfile_object_name(brick), "GwyBrick") == 0);
    gwyfile_object_add(brick, gwyfile_item_new_bool("EXTRA_ITEM", true));

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
    assert(strcmp(xunit, "") == 0);
    assert(strcmp(yunit, "") == 0);
    assert(strcmp(zunit, "") == 0);
    assert(strcmp(wunit, "") == 0);

    free(wunit);
    free(zunit);
    free(yunit);
    free(xunit);

    assert(gwyfile_object_brick_get(brick, NULL, "data", &data3, NULL));
    assert(memcmp(data3, data, 1*2*3*sizeof(double)) == 0);

    gwyfile_object_free(brick);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
