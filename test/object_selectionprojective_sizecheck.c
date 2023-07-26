/*
 * $Id: object_selectionprojective_sizecheck.c 365 2022-02-10 12:51:29Z yeti-dn $
 *
 * Test GwySelectionProjective object data size check.
 *
 * I, the copyright holder of this work, release this work into the public domain.  This applies worldwide.  In some
 * countries this may not be legally without any conditions, unless such conditions are required by law.
 * without any conditions, unless such conditions are required by law.
 */
#include "common.h"

int
main(void)
{
    static const double data[] = { 1.0, 3.0, -42.0, 1.75, 0.0, 2.0, -5.0, 14.5, 0.25, -1.0, 12.0, 6.0 };
    int32_t nsel;
    GwyfileObject *object;

    object = gwyfile_object_new("GwySelectionProjective",
                                gwyfile_item_new_double_array_copy("data", data, 12),
                                NULL);
    assert(object);
    assert(strcmp(gwyfile_object_name(object), "GwySelectionProjective") == 0);
    assert(!gwyfile_object_selectionprojective_get(object, NULL,
                                                   "nsel", &nsel,
                                                   NULL));

    gwyfile_object_free(object);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
