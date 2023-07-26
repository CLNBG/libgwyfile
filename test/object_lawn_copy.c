/*
 * $Id: object_lawn_copy.c 378 2022-02-10 16:43:07Z yeti-dn $
 *
 * Test GwyLawn object constructor and extractor with copied data.
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
    double *data2;
    int32_t *clen2;
    const double *data3;
    const int32_t *clen3;
    double xreal, yreal, xoff, yoff;
    int32_t xres, yres, ncurves, nsegments;
    char *xyunit;
    GwyfileObject *lawn;

    lawn = gwyfile_object_new_lawn(2, 2, 1, 3.0, 4.0,
                                   "curvelengths(copy)", curvelengths,
                                   "data(copy)", data,
                                   "si_unit_xy", "s",
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
    assert(xres == 2);
    assert(yres == 2);
    assert(ncurves == 1);
    assert(xreal == 3.0);
    assert(yreal == 4.0);
    assert(xoff == 0.0);
    assert(yoff == 0.0);
    assert(strcmp(xyunit, "s") == 0);

    free(xyunit);

    assert(gwyfile_object_lawn_get(lawn, NULL, "curvelengths", &clen3, NULL));
    assert(memcmp(clen3, curvelengths, sizeof(curvelengths)) == 0);

    assert(gwyfile_object_lawn_get(lawn, NULL, "data", &data3, NULL));
    assert(memcmp(data3, data, sizeof(data)) == 0);

    assert(gwyfile_object_lawn_get(lawn, NULL, "curvelengths(take)", &clen2, NULL));
    assert(memcmp(clen2, curvelengths, sizeof(curvelengths)) == 0);

    assert(gwyfile_object_lawn_get(lawn, NULL, "data(take)", &data2, NULL));
    assert(memcmp(data2, data, sizeof(data)) == 0);

    assert(gwyfile_object_lawn_get(lawn, NULL, "curvelengths", &clen3, NULL));
    assert(memcmp(clen3, curvelengths, sizeof(curvelengths)) == 0);

    assert(gwyfile_object_lawn_get(lawn, NULL, "data", &data3, NULL));
    assert(memcmp(data3, data, sizeof(data)) == 0);

    gwyfile_object_free(lawn);
    free(data2);
    free(clen2);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
