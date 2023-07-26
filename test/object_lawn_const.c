/*
 * $Id: object_lawn_const.c 378 2022-02-10 16:43:07Z yeti-dn $
 *
 * Test GwyLawn object constructor and extractor with constant data.
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
        1.0, 3.0, -42.0, 2.0, 3.0, 0.0,   /* curve (0,0), length = 3 */
                                          /* curve (1,0), length = 0 */
        -14.5, 3.75,                      /* curve (2,0), length = 1 */
    };
    static const int32_t curvelengths[] = { 3, 0, 1 };
    const double *data3;
    const int32_t *clen3;
    double xreal, yreal, xoff, yoff;
    int32_t xres, yres, ncurves, nsegments;
    char *xyunit;
    GwyfileObject *lawn;

    lawn = gwyfile_object_new_lawn(3, 1, 2, 6.0, 2.0,
                                   "curvelengths(const)", curvelengths,
                                   "data(const)", data,
                                   NULL);
    assert(lawn);
    assert(strcmp(gwyfile_object_name(lawn), "GwyLawn") == 0);
    gwyfile_object_add(lawn, gwyfile_item_new_bool("EXTRA_ITEM", true));

    assert(gwyfile_object_lawn_get(lawn, NULL,
                                   "xres", &xres,
                                   "yres", &yres,
                                   "ncurves", &ncurves,
                                   "nsegments", &nsegments,
                                   "xreal", &xreal,
                                   "yreal", &yreal,
                                   "xoff", &xoff,
                                   "yoff", &yoff,
                                   "si_unit_xy", &xyunit,
                                   NULL));
    assert(xres == 3);
    assert(yres == 1);
    assert(ncurves == 2);
    assert(xreal == 6.0);
    assert(yreal == 2.0);
    assert(xoff == 0.0);
    assert(yoff == 0.0);
    assert(strcmp(xyunit, "") == 0);

    free(xyunit);

    assert(gwyfile_object_lawn_get(lawn, NULL, "curvelengths", &clen3, NULL));
    assert(memcmp(clen3, curvelengths, sizeof(curvelengths)) == 0);

    assert(gwyfile_object_lawn_get(lawn, NULL, "data", &data3, NULL));
    assert(memcmp(data3, data, sizeof(data)) == 0);

    gwyfile_object_free(lawn);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
