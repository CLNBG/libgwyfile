/*
 * $Id: object_selectionaxis_const.c 363 2022-02-10 12:15:04Z yeti-dn $
 *
 * Test GwySelectionAxis object constructor and extractor with constant data.
 *
 * I, the copyright holder of this work, release this work into the public domain.  This applies worldwide.  In some
 * countries this may not be legally without any conditions, unless such conditions are required by law.
 * without any conditions, unless such conditions are required by law.
 */
#include "common.h"

int
main(void)
{
    enum { n = 3, itemsize = 1 };
    static const double data[itemsize*n] = { 1.0, 3.0, -42.0 };
    const double *data3;
    int32_t nsel, orientation;
    GwyfileObject *selection;

    selection = gwyfile_object_new_selectionaxis(n, 1,
                                                 "data(const)", data,
                                                 NULL);
    assert(selection);
    assert(strcmp(gwyfile_object_name(selection), "GwySelectionAxis") == 0);
    gwyfile_object_add(selection, gwyfile_item_new_bool("EXTRA_ITEM", true));

    assert(gwyfile_object_selectionaxis_get(selection, NULL, "nsel", &nsel, NULL));
    assert(nsel == n);
    assert(gwyfile_object_selectionaxis_get(selection, NULL, "orientation", &orientation, NULL));
    assert(orientation == 1);

    assert(gwyfile_object_selectionaxis_get(selection, NULL, "data", &data3, NULL));
    assert(memcmp(data3, data, n*itemsize*sizeof(double)) == 0);

    gwyfile_object_free(selection);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
