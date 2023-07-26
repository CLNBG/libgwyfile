/*
 * $Id: object_graphcurvemodel_const.c 363 2022-02-10 12:15:04Z yeti-dn $
 *
 * Test GwyGraphCurveModel object constructor and extractor with constant data.
 *
 * I, the copyright holder of this work, release this work into the public domain.  This applies worldwide.  In some
 * countries this may not be legally without any conditions, unless such conditions are required by law.
 * without any conditions, unless such conditions are required by law.
 */
#include "common.h"

int
main(void)
{
    static const double xdata[] = { 1.0, 2.0, 3.0 };
    static const double ydata[] = { -3.14, 4.0, 69.0 };
    const double *xdata3, *ydata3;
    double red, green, blue;
    int32_t ndata, type, line_style, point_type, line_size, point_size;
    char *description;
    GwyfileObject *graphcurvemodel;

    graphcurvemodel = gwyfile_object_new_graphcurvemodel(3,
                                                         "xdata(const)", xdata,
                                                         "ydata(const)", ydata,
                                                         "color.red", 1.0,
                                                         "color.green", 0.5,
                                                         "color.blue", 0.125,
                                                         "type", 2,
                                                         "line_style", 0,
                                                         "point_type", 6,
                                                         "line_size", 2,
                                                         "point_size", 11,
                                                         "description", "Foo",
                                                         NULL);
    assert(graphcurvemodel);
    assert(strcmp(gwyfile_object_name(graphcurvemodel), "GwyGraphCurveModel")
           == 0);
    gwyfile_object_add(graphcurvemodel, gwyfile_item_new_bool("EXTRA_ITEM",
                                                              true));

    assert(gwyfile_object_graphcurvemodel_get(graphcurvemodel, NULL,
                                              "ndata", &ndata,
                                              "color.red", &red,
                                              "color.green", &green,
                                              "color.blue", &blue,
                                              "type", &type,
                                              "line_style", &line_style,
                                              "point_type", &point_type,
                                              "line_size", &line_size,
                                              "point_size", &point_size,
                                              "description", &description,
                                              NULL));
    assert(ndata == 3);
    assert(red == 1.0);
    assert(green == 0.5);
    assert(blue == 0.125);
    assert(type == 2);
    assert(line_style == 0);
    assert(point_type == 6);
    assert(line_size == 2);
    assert(point_size == 11);
    assert(strcmp(description, "Foo") == 0);

    free(description);

    assert(gwyfile_object_graphcurvemodel_get(graphcurvemodel, NULL,
                                              "xdata", &xdata3,
                                              "ydata", &ydata3,
                                              NULL));
    assert(memcmp(xdata3, xdata, 3*sizeof(double)) == 0);
    assert(memcmp(ydata3, ydata, 3*sizeof(double)) == 0);

    gwyfile_object_free(graphcurvemodel);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
