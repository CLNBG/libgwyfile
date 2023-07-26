/*
 * $Id: file_error_toodeepnesting.c 363 2022-02-10 12:15:04Z yeti-dn $
 *
 * Test too deep nesting error.
 *
 * I, the copyright holder of this work, release this work into the public domain.  This applies worldwide.  In some
 * countries this may not be legally without any conditions, unless such conditions are required by law.
 * without any conditions, unless such conditions are required by law.
 */
#include "common.h"

static char filename[256];

int
main(void)
{
    GwyfileObject *gwyf;
    GwyfileItem *item;
    GwyfileError *error = NULL;
    uint32_t i;

    sprintf(filename, "file_error_toodeepnesting.%u.gwy", getpid());
    gwyf = gwyfile_object_new("Test", NULL);

    for (i = 0; i < 201; i++) {
        item = gwyfile_item_new_object("T", gwyf);
        gwyf = gwyfile_object_new("T", item, NULL);
    }

    assert(gwyfile_write_file(gwyf, filename, &error));
    assert(!error);
    gwyfile_object_free(gwyf);

    gwyf = gwyfile_read_file(filename, &error);
    assert(!gwyf);
    assert(error);

    assert(error->domain == GWYFILE_ERROR_DOMAIN_DATA);
    assert(error->code == GWYFILE_ERROR_TOO_DEEP_NESTING);
    gwyfile_error_clear(&error);

    unlink(filename);

    return 0;
}


/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
