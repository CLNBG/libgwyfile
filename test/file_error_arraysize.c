/*
 * $Id: file_error_arraysize.c 363 2022-02-10 12:15:04Z yeti-dn $
 *
 * Test array size error.
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
    const double data[1] = { 0.0 };
    GwyfileObject *gwyf;
    GwyfileError *error = NULL;
    FILE *fh;

    sprintf(filename, "file_error_arraysize.%u.gwy", getpid());
    gwyf = gwyfile_object_new("Test",
                              gwyfile_item_new_double_array_const("T", data, 1),
                              NULL);

    assert(gwyfile_write_file(gwyf, filename, &error));
    assert(!error);
    gwyfile_object_free(gwyf);

    fh = fopen(filename, "rb+");
    assert(fh);
    assert(fseek(fh, 16L, SEEK_SET) == 0);
    assert(fwrite("\x00", 1, 1, fh) == 1);
    fclose(fh);

    gwyf = gwyfile_read_file(filename, &error);
    assert(!gwyf);
    assert(error);

    assert(error->domain == GWYFILE_ERROR_DOMAIN_DATA);
    assert(error->code == GWYFILE_ERROR_ARRAY_SIZE);
    gwyfile_error_clear(&error);

    unlink(filename);

    return 0;
}


/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
