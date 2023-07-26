/*
 * $Id: check_double_inf.c 363 2022-02-10 12:15:04Z yeti-dn $
 *
 * Invalid double value (NaN) validity error.
 *
 * I, the copyright holder of this work, release this work into the public domain.  This applies worldwide.  In some
 * countries this may not be legally without any conditions, unless such conditions are required by law.
 * without any conditions, unless such conditions are required by law.
 */
#include "common.h"

#ifndef INFINITY
#define INFINITY (1.0/0.0)
#endif

int
main(void)
{
    static const double doubles[] = { 1.0, -0.0, INFINITY, INFINITY, 3.14 };

    GwyfileObject *object;
    GwyfileErrorList errlist;
    unsigned int i;
    bool ok;

    gwyfile_error_list_init(&errlist);
    assert(errlist.n == 0);
    assert(errlist.errors == NULL);

    object = gwyfile_object_new("TopLevel",
                                gwyfile_item_new_double("good", 0.0),
                                gwyfile_item_new_double("huge", 1e-38),
                                gwyfile_item_new_double("bad", INFINITY),
                                gwyfile_item_new_double_array_const("array", doubles, 5),
                                NULL);
    assert(object);

    ok = gwyfile_check_object(object, GWYFILE_CHECK_FLAG_VALIDITY, NULL);
    assert(!ok);

    ok = gwyfile_check_object(object, GWYFILE_CHECK_FLAG_VALIDITY, &errlist);
    assert(!ok);
    assert(errlist.n == 3);
    for (i = 0; i < errlist.n; i++) {
        GwyfileError *error = errlist.errors[i];

        assert(error);
        assert(error->domain == GWYFILE_ERROR_DOMAIN_VALIDITY);
        assert(error->code == GWYFILE_INVALID_DOUBLE);
    }

    gwyfile_error_list_clear(&errlist);
    assert(errlist.n == 0);
    assert(errlist.errors == NULL);

    gwyfile_object_free(object);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
