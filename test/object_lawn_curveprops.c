/*
 * $Id: object_lawn_curveprops.c 379 2022-02-10 17:21:03Z yeti-dn $
 *
 * Test GwyLawn object construction and extraction of per-curve properties.
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
        1.0, 3.0, -42.0, 2.0, 3.0, 0.0,   /* curve (0,0), length = 2 */
                                          /* curve (1,0), length = 0 */
                                          /* curve (2,0), length = 0 */
        -14.5, 3.75, 8.0,                 /* curve (3,0), length = 1 */
    };
    static const int32_t curvelengths[] = { 2, 0, 0, 1 };
    const char *const curve_labels[] = { "One", "Two", "The other one" };
    const char *const curve_units[] = { "m", "A", "N" };
    int32_t ncurves, i;
    char **clab2, **cunit2;
    GwyfileObject *lawn;

    lawn = gwyfile_object_new_lawn(1, 4, 3, 2.0, 1.0,
                                   "curvelengths(const)", curvelengths,
                                   "data(const)", data,
                                   "curve_labels", curve_labels,
                                   "si_units_curves", curve_units,
                                   NULL);
    assert(lawn);
    assert(strcmp(gwyfile_object_name(lawn), "GwyLawn") == 0);
    gwyfile_object_add(lawn, gwyfile_item_new_bool("EXTRA_ITEM", true));

    assert(gwyfile_object_lawn_get(lawn, NULL,
                                   "ncurves", &ncurves,
                                   "curve_labels", &clab2,
                                   "si_units_curves", &cunit2,
                                   NULL));
    assert(ncurves == 3);

    assert(clab2);
    for (i = 0; i < ncurves; i++) {
        assert(strcmp(clab2[i], curve_labels[i]) == 0);
        free(clab2[i]);
    }
    free(clab2);

    assert(cunit2);
    for (i = 0; i < ncurves; i++) {
        assert(strcmp(cunit2[i], curve_units[i]) == 0);
        free(cunit2[i]);
    }
    free(cunit2);
    gwyfile_object_free(lawn);

    lawn = gwyfile_object_new_lawn(1, 4, 3, 2.0, 1.0,
                                   "curvelengths(const)", curvelengths,
                                   "data(const)", data,
                                   NULL);
    assert(lawn);
    assert(strcmp(gwyfile_object_name(lawn), "GwyLawn") == 0);
    gwyfile_object_add(lawn, gwyfile_item_new_bool("EXTRA_ITEM", true));

    assert(gwyfile_object_lawn_get(lawn, NULL,
                                   "ncurves", &ncurves,
                                   "curve_labels", &clab2,
                                   "si_units_curves", &cunit2,
                                   NULL));
    assert(ncurves == 3);

    assert(clab2);
    for (i = 0; i < ncurves; i++) {
        assert(strcmp(clab2[i], "") == 0);
        free(clab2[i]);
    }
    free(clab2);

    assert(cunit2);
    for (i = 0; i < ncurves; i++) {
        assert(strcmp(cunit2[i], "") == 0);
        free(cunit2[i]);
    }
    free(cunit2);
    gwyfile_object_free(lawn);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
