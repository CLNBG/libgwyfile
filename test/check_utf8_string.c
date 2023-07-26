/*
 * $Id: check_utf8_string.c 363 2022-02-10 12:15:04Z yeti-dn $
 *
 * Invalid UTF-8 string value validity error.
 *
 * I, the copyright holder of this work, release this work into the public domain.  This applies worldwide.  In some
 * countries this may not be legally without any conditions, unless such conditions are required by law.
 * without any conditions, unless such conditions are required by law.
 */
#include "common.h"

int
main(void)
{
    static const char *const strings[] = {
        "good", "also good", "b\xaa" "d", "", "wors\xee"
    };

    GwyfileObject *object;
    GwyfileErrorList errlist;
    unsigned int i;
    bool ok;

    gwyfile_error_list_init(&errlist);
    assert(errlist.n == 0);
    assert(errlist.errors == NULL);

    object = gwyfile_object_new("TopLevel",
                                gwyfile_item_new_string_const("valid", "abc"),
                                gwyfile_item_new_string_const("invalid", "abc\xfe"),
                                gwyfile_item_new_string_array_const("array", strings, 5),
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
        assert(error->code == GWYFILE_INVALID_UTF8_STRING);
    }

    gwyfile_error_list_clear(&errlist);
    assert(errlist.n == 0);
    assert(errlist.errors == NULL);

    gwyfile_object_free(object);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
