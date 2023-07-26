/*
 * $Id: file_error_duplicatename.c 363 2022-02-10 12:15:04Z yeti-dn $
 *
 * Test duplicate item name error.
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
    GwyfileError *error = NULL;
    FILE *fh;

    sprintf(filename, "file_error_duplicatename.%u.gwy", getpid());
    gwyf = gwyfile_object_new("Test",
                              gwyfile_item_new_int32("T", 1),
                              gwyfile_item_new_int32("U", 2),
                              NULL);

    assert(gwyfile_write_file(gwyf, filename, &error));
    assert(!error);
    gwyfile_object_free(gwyf);

    fh = fopen(filename, "rb+");
    assert(fh);
    /* Overwrite both item names.  The serialisation order is not guaranteed
     * by the API. */
    assert(fseek(fh, 13L, SEEK_SET) == 0);
    assert(fwrite("T", 1, 1, fh) == 1);
    assert(fseek(fh, 20L, SEEK_SET) == 0);
    assert(fwrite("T", 1, 1, fh) == 1);
    fclose(fh);

    gwyf = gwyfile_read_file(filename, &error);
    assert(!gwyf);
    assert(error);

    assert(error->domain == GWYFILE_ERROR_DOMAIN_DATA);
    assert(error->code == GWYFILE_ERROR_DUPLICATE_NAME);
    gwyfile_error_clear(&error);

    unlink(filename);

    return 0;
}


/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */