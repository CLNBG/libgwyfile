/*
 * $Id: check_identifier_type.c 363 2022-02-10 12:15:04Z yeti-dn $
 *
 * Warning about object name (type) not being a C identifier.
 *
 * I, the copyright holder of this work, release this work into the public domain.  This applies worldwide.  In some
 * countries this may not be legally without any conditions, unless such conditions are required by law.
 * without any conditions, unless such conditions are required by law.
 */
#include "common.h"

int
main(void)
{
    GwyfileObject *object;
    GwyfileErrorList errlist;
    unsigned int i;
    bool ok;

    gwyfile_error_list_init(&errlist);
    assert(errlist.n == 0);
    assert(errlist.errors == NULL);

    object = gwyfile_object_new
                 ("TopLevel-",
                  gwyfile_item_new_int32("valid", 41),
                  gwyfile_item_new_double("d", 43.0),
                  gwyfile_item_new_object
                      ("obj", gwyfile_object_new("Nested", NULL)),
                  gwyfile_item_new_object
                      ("obj2",
                       gwyfile_object_new
                           ("DeeplyNested",
                            gwyfile_item_new_object
                                ("obj", gwyfile_object_new("2A", NULL)),
                            NULL)),
                  gwyfile_item_new_object
                      ("invalid", gwyfile_object_new("#", NULL)),
                  NULL);
    assert(object);

    ok = gwyfile_check_object(object, GWYFILE_CHECK_FLAG_VALIDITY, NULL);
    assert(ok);

    ok = gwyfile_check_object(object, GWYFILE_CHECK_FLAG_WARNING, NULL);
    assert(!ok);

    ok = gwyfile_check_object(object, GWYFILE_CHECK_FLAG_WARNING, &errlist);
    assert(!ok);
    assert(errlist.n == 3);
    for (i = 0; i < errlist.n; i++) {
        GwyfileError *error = errlist.errors[i];

        assert(error);
        assert(error->domain == GWYFILE_ERROR_DOMAIN_WARNING);
        assert(error->code == GWYFILE_WARNING_TYPE_IDENTIFIER);
    }

    gwyfile_error_list_clear(&errlist);
    assert(errlist.n == 0);
    assert(errlist.errors == NULL);

    gwyfile_object_free(object);

    return 0;
}


/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
