/*
 * $Id: object_graphmodel_curves.c 363 2022-02-10 12:15:04Z yeti-dn $
 *
 * Common includes for tests.
 *
 * I, the copyright holder of this work, release this work into the public domain.  This applies worldwide.  In some
 * countries this may not be legally without any conditions, unless such conditions are required by law.
 * without any conditions, unless such conditions are required by law.
 */
#include "common.h"

int
main(void)
{
    static const double xdata[] = { 1.0 };
    static const double ydata[] = { 2.0 };
    static const double xdata2[] = { 1.5, 3.5 };
    static const double ydata2[] = { 4.0, 6.0 };
    int32_t ncurves;
    char *title, *top_label, *bottom_label, *left_label, *right_label,
         *xunit, *yunit;
    GwyfileObject *graphmodel, *curve0, *curve1;
    GwyfileObject **curves, **modelcurves;

    curves = malloc(2*sizeof(GwyfileObject*));

    curves[0] = gwyfile_object_new_graphcurvemodel(1,
                                                   "xdata(const)", xdata,
                                                   "ydata(const)", ydata,
                                                   NULL);
    assert(curves[0]);
    assert(strcmp(gwyfile_object_name(curves[0]), "GwyGraphCurveModel") == 0);
    curve0 = curves[0];

    curves[1] = gwyfile_object_new_graphcurvemodel(2,
                                                   "xdata(const)", xdata2,
                                                   "ydata(const)", ydata2,
                                                   NULL);
    assert(curves[1]);
    assert(strcmp(gwyfile_object_name(curves[1]), "GwyGraphCurveModel") == 0);
    curve1 = curves[1];

    graphmodel = gwyfile_object_new_graphmodel(2,
                                               "curves", curves,
                                               "title", "Title",
                                               "top_label", "top",
                                               "left_label", "left",
                                               "right_label", "right",
                                               "bottom_label", "bottom",
                                               "x_unit", "m",
                                               "y_unit", "m^{-1}",
                                               NULL);
    assert(graphmodel);
    assert(strcmp(gwyfile_object_name(graphmodel), "GwyGraphModel") == 0);

    assert(gwyfile_object_graphmodel_get(graphmodel, NULL,
                                         "ncurves", &ncurves,
                                         "title", &title,
                                         "top_label", &top_label,
                                         "left_label", &left_label,
                                         "right_label", &right_label,
                                         "bottom_label", &bottom_label,
                                         "x_unit", &xunit,
                                         "y_unit", &yunit,
                                         NULL));
    assert(ncurves == 2);
    assert(strcmp(title, "Title") == 0);
    assert(strcmp(left_label, "left") == 0);
    assert(strcmp(right_label, "right") == 0);
    assert(strcmp(bottom_label, "bottom") == 0);
    assert(strcmp(top_label, "top") == 0);
    assert(strcmp(xunit, "m") == 0);
    assert(strcmp(yunit, "m^{-1}") == 0);

    free(yunit);
    free(xunit);
    free(left_label);
    free(top_label);
    free(bottom_label);
    free(right_label);
    free(title);

    assert(gwyfile_object_graphmodel_get(graphmodel, NULL,
                                         "curves", &modelcurves,
                                         NULL));
    assert(modelcurves);
    assert(modelcurves[0] == curve0);
    assert(modelcurves[1] == curve1);

    gwyfile_object_free(graphmodel);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
