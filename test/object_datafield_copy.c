/*
 * $Id: object_datafield_copy.c 363 2022-02-10 12:15:04Z yeti-dn $
 *
 * Test GwyDataField object constructor and extractor with copied data.
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
    double *data2;
    const double *data3;
    double xreal, yreal, xoff, yoff;
    int32_t xres, yres;
    char *xyunit, *zunit;
    GwyfileObject *datafield;

    datafield = gwyfile_object_new_datafield(3, 2, 6.0, 4.0,
                                             "data(copy)", data,
                                             "si_unit_xy", "m",
                                             "si_unit_z", "A",
                                             NULL);
    assert(datafield);
    assert(strcmp(gwyfile_object_name(datafield), "GwyDataField") == 0);
    gwyfile_object_add(datafield, gwyfile_item_new_double("EXTRA_ITEM", M_PI));

    assert(gwyfile_object_datafield_get(datafield, NULL,
                                        "xres", &xres,
                                        "yres", &yres,
                                        "xreal", &xreal,
                                        "yreal", &yreal,
                                        "xoff", &xoff,
                                        "yoff", &yoff,
                                        "si_unit_xy", &xyunit,
                                        "si_unit_z", &zunit,
                                        NULL));
    assert(xres == 3);
    assert(yres == 2);
    assert(xreal == 6.0);
    assert(yreal == 4.0);
    assert(xoff == 0.0);
    assert(yoff == 0.0);
    assert(strcmp(xyunit, "m") == 0);
    assert(strcmp(zunit, "A") == 0);

    free(zunit);
    free(xyunit);

    assert(gwyfile_object_datafield_get(datafield, NULL, "data", &data3, NULL));
    assert(memcmp(data3, data, 2*3*sizeof(double)) == 0);

    assert(gwyfile_object_datafield_get(datafield, NULL, "data(take)", &data2, NULL));
    assert(memcmp(data2, data, 2*3*sizeof(double)) == 0);

    assert(gwyfile_object_datafield_get(datafield, NULL, "data", &data3, NULL));
    assert(memcmp(data3, data, 2*3*sizeof(double)) == 0);

    gwyfile_object_free(datafield);
    free(data2);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
