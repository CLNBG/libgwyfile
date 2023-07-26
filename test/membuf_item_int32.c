/*
 * $Id: membuf_item_int32.c 363 2022-02-10 12:15:04Z yeti-dn $
 *
 * Test memory serialisation and deserialisation of basic types.
 *
 * I, the copyright holder of this work, release this work into the public domain.  This applies worldwide.  In some
 * countries this may not be legally without any conditions, unless such conditions are required by law.
 * without any conditions, unless such conditions are required by law.
 */
#include "common.h"

int
main(void)
{
    GwyfileItem *item;
    GwyfileError *error = NULL;
    size_t size, bytes_written, bytes_read;
    char *buffer;

    item = gwyfile_item_new_int32("int32", 42);
    assert(item);

    size = gwyfile_item_size(item);
    assert(size == strlen("int32")+1 + 1 + sizeof(int32_t));

    buffer = malloc(size);
    assert(buffer);

    bytes_written = gwyfile_item_write_memory(item, buffer, size, &error);
    assert(!error);
    assert(bytes_written == size);

    gwyfile_item_free(item);

    item = gwyfile_item_read_memory(buffer, size, &bytes_read, &error);
    assert(!error);
    assert(bytes_read == size);
    assert(gwyfile_item_type(item) == GWYFILE_ITEM_INT32);
    assert(gwyfile_item_get_int32(item) == 42);
    assert(strcmp(gwyfile_item_name(item), "int32") == 0);

    free(buffer);
    gwyfile_item_free(item);

    return 0;
}


/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
