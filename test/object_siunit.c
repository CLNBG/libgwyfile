/*
 * $Id: object_siunit.c 363 2022-02-10 12:15:04Z yeti-dn $
 *
 * Test GwySIUnit constructor and extractor.
 *
 * I, the copyright holder of this work, release this work into the public domain.  This applies worldwide.  In some
 * countries this may not be legally without any conditions, unless such conditions are required by law.
 * without any conditions, unless such conditions are required by law.
 */
#include "common.h"

int
main(void)
{
    char *unitstr;
    GwyfileObject *siunit;

    siunit = gwyfile_object_new_siunit("m");
    assert(siunit);
    assert(strcmp(gwyfile_object_name(siunit), "GwySIUnit") == 0);
    gwyfile_object_add(siunit, gwyfile_item_new_bool("EXTRA_ITEM", true));

    assert(gwyfile_object_siunit_get(siunit, NULL, "unitstr", &unitstr, NULL));
    assert(strcmp(unitstr, "m") == 0);

    free(unitstr);

    gwyfile_object_free(siunit);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
