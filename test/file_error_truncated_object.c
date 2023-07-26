/*
 * $Id: file_error_truncated_object.c 363 2022-02-10 12:15:04Z yeti-dn $
 *
 * Test truncation error for object read from file.
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
    char *buffer;
    size_t size, i, bytes_written;
    FILE *fh;

    sprintf(filename, "file_error_truncated_object.%u.gwy", getpid());
    gwyf = gwyfile_object_new("Test",
                              gwyfile_item_new_bool("b", false),
                              gwyfile_item_new_string_const("s", "blah"),
                              NULL);
    size = gwyfile_object_size(gwyf);
    assert(size);

    buffer = malloc(size + 4);
    assert(buffer);

    memcpy(buffer, "GWYP", 4);
    bytes_written = gwyfile_object_write_memory(gwyf, buffer + 4, size, &error);
    assert(!error);
    assert(bytes_written == size);
    gwyfile_object_free(gwyf);

    for (i = 0; i < size + 4; i++) {
        fh = fopen(filename, "wb");
        assert(fh);
        assert(fwrite(buffer, 1, i, fh) == i);
        fclose(fh);

        gwyf = gwyfile_read_file(filename, &error);
        assert(!gwyf);
        assert(error);

        assert(error->domain == GWYFILE_ERROR_DOMAIN_DATA);
        assert(error->code == GWYFILE_ERROR_TRUNCATED);
        gwyfile_error_clear(&error);
    }
    free(buffer);

    unlink(filename);

    return 0;
}


/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
