/*
 * $Id: membuf_object_read_too_short.c 363 2022-02-10 12:15:04Z yeti-dn $
 *
 * Test error handling when reading truncated memory buffers.
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
    GwyfileError *error = NULL;
    size_t i, size, bytes_written, bytes_read;
    char *buffer;

    object = gwyfile_object_new("Test",
                                gwyfile_item_new_bool("bool", true),
                                gwyfile_item_new_char("char", 'X'),
                                gwyfile_item_new_int32("int32", 42),
                                gwyfile_item_new_int64("int64", 1234567890ULL),
                                gwyfile_item_new_double("double", M_PI),
                                gwyfile_item_new_string_copy("string", "Shark"),
                                NULL);
    assert(object);
    size = gwyfile_object_size(object);

    buffer = malloc(size);
    assert(buffer);

    bytes_written = gwyfile_object_write_memory(object, buffer, size, &error);
    assert(!error);
    assert(bytes_written == size);

    gwyfile_object_free(object);

    for (i = 0; i < size; i++) {
        object = gwyfile_object_read_memory(buffer, i, &bytes_read, &error);
        assert(bytes_read == 0);
        assert(error);
        assert(error->domain == GWYFILE_ERROR_DOMAIN_DATA);
        assert(error->code == GWYFILE_ERROR_TRUNCATED);
        gwyfile_error_clear(&error);
    }

    free(buffer);

    return 0;
}


/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
