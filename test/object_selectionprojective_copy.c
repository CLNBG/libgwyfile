/*
 * $Id: object_selectionprojective_copy.c 364 2022-02-10 12:15:42Z yeti-dn $
 *
 * Test GwySelectionProjective object constructor and extractor with copied data.
 *
 * I, the copyright holder of this work, release this work into the public domain.  This applies worldwide.  In some
 * countries this may not be legally without any conditions, unless such conditions are required by law.
 * without any conditions, unless such conditions are required by law.
 */
#include "common.h"

int
main(void)
{
    enum { n = 2, itemsize = 8 };
    static const double data[itemsize*n] = {
        1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 6.0,
        -42.0, -44.0, -37.0, -26.0, 0.0, 7.125, -1e5, 3.75,
    };
    double *data2;
    const double *data3;
    int32_t nsel;
    GwyfileObject *selection;

    selection = gwyfile_object_new_selectionprojective(n,
                                                       "data(copy)", data,
                                                       NULL);
    assert(selection);
    assert(strcmp(gwyfile_object_name(selection), "GwySelectionProjective") == 0);
    gwyfile_object_add(selection, gwyfile_item_new_double("EXTRA_ITEM", M_PI));

    assert(gwyfile_object_selectionprojective_get(selection, NULL,
                                                  "nsel", &nsel,
                                                  NULL));
    assert(nsel == n);

    assert(gwyfile_object_selectionprojective_get(selection, NULL,
                                                  "data", &data3,
                                                  NULL));
    assert(memcmp(data3, data, n*itemsize*sizeof(double)) == 0);

    assert(gwyfile_object_selectionprojective_get(selection, NULL,
                                                  "data(take)", &data2,
                                                  NULL));
    assert(memcmp(data2, data, n*itemsize*sizeof(double)) == 0);

    assert(gwyfile_object_selectionprojective_get(selection, NULL,
                                                  "data", &data3,
                                                  NULL));
    assert(memcmp(data3, data, n*itemsize*sizeof(double)) == 0);

    gwyfile_object_free(selection);
    free(data2);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
