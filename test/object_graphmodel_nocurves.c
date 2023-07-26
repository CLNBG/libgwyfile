/*
 * $Id: object_graphmodel_nocurves.c 363 2022-02-10 12:15:04Z yeti-dn $
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
    int32_t ncurves;
    char *title, *top_label, *bottom_label, *left_label, *right_label,
         *xunit, *yunit;
    double xmin, xmax, ymin, ymax;
    bool x_min_set, y_min_set, x_max_set, y_max_set,
         x_is_logarithmic, y_is_logarithmic;
    GwyfileObject *graphmodel;
    GwyfileObject **modelcurves;

    graphmodel = gwyfile_object_new_graphmodel(0,
                                               "x_min", -5.0,
                                               "x_max", 5.0,
                                               "y_min", -10.0,
                                               "y_max", 10.0,
                                               "y_min_set", true,
                                               "y_max_set", true,
                                               "x_is_logarithmic", true,
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
                                         "x_min", &xmin,
                                         "x_max", &xmax,
                                         "y_min", &ymin,
                                         "y_max", &ymax,
                                         "x_min_set", &x_min_set,
                                         "x_max_set", &x_max_set,
                                         "y_min_set", &y_min_set,
                                         "y_max_set", &y_max_set,
                                         "x_is_logarithmic", &x_is_logarithmic,
                                         "y_is_logarithmic", &y_is_logarithmic,
                                         NULL));
    assert(ncurves == 0);
    assert(strcmp(title, "") == 0);
    assert(strcmp(left_label, "") == 0);
    assert(strcmp(right_label, "") == 0);
    assert(strcmp(bottom_label, "") == 0);
    assert(strcmp(top_label, "") == 0);
    assert(strcmp(xunit, "") == 0);
    assert(strcmp(yunit, "") == 0);
    assert(xmin == -5.0);
    assert(xmax == 5.0);
    assert(ymin == -10.0);
    assert(ymax == 10.0);
    assert(x_min_set == false);
    assert(x_max_set == false);
    assert(y_min_set == true);
    assert(y_max_set == true);
    assert(x_is_logarithmic == true);
    assert(y_is_logarithmic == false);

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
    assert(modelcurves == NULL);

    gwyfile_object_free(graphmodel);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
