/*
 * $Id: object_dataline_owned.c 363 2022-02-10 12:15:04Z yeti-dn $
 *
 * Test GwyDataLine object constructor and extractor with owned data.
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
    double *dataowned, *data2;
    const double *data3;
    double real, off;
    int32_t res;
    char *xunit, *yunit;
    GwyfileObject *dataline;

    dataowned = malloc(3*sizeof(double));
    memcpy(dataowned, data, 3*sizeof(double));
    dataline = gwyfile_object_new_dataline(3, 5.0,
                                           "data", dataowned,
                                           "si_unit_x", "m",
                                           "si_unit_y", "A",
                                           NULL);
    assert(dataline);
    assert(strcmp(gwyfile_object_name(dataline), "GwyDataLine") == 0);
    gwyfile_object_add(dataline, gwyfile_item_new_int32("EXTRA_ITEM", -10));

    assert(gwyfile_object_dataline_get(dataline, NULL,
                                       "res", &res,
                                       "real", &real,
                                       "off", &off,
                                       "si_unit_x", &xunit,
                                       "si_unit_y", &yunit,
                                       NULL));
    assert(res == 3);
    assert(real == 5.0);
    assert(off == 0.0);
    assert(strcmp(xunit, "m") == 0);
    assert(strcmp(yunit, "A") == 0);

    free(yunit);
    free(xunit);

    assert(gwyfile_object_dataline_get(dataline, NULL, "data", &data3, NULL));
    assert(memcmp(data3, data, 3*sizeof(double)) == 0);

    assert(gwyfile_object_dataline_get(dataline, NULL, "data(take)", &data2, NULL));
    assert(memcmp(data2, data, 3*sizeof(double)) == 0);

    assert(gwyfile_object_dataline_get(dataline, NULL, "data", &data3, NULL));
    assert(memcmp(data3, data, 3*sizeof(double)) == 0);

    gwyfile_object_free(dataline);
    free(data2);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
