/*
 * $Id: membuf_item_object.c 363 2022-02-10 12:15:04Z yeti-dn $
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
    GwyfileItem *item, *subitem;
    GwyfileObject *object;
    GwyfileError *error = NULL;
    size_t size, bytes_written, bytes_read;
    char *buffer;

    item = gwyfile_item_new_object
               ("object",
                gwyfile_object_new
                    ("Object",
                     gwyfile_item_new_int32("int", 42),
                     gwyfile_item_new_string_copy("str", "Shark"),
                     NULL));
    assert(item);
    size = gwyfile_item_size(item);

    buffer = malloc(size);
    assert(buffer);

    bytes_written = gwyfile_item_write_memory(item, buffer, size, &error);
    assert(!error);
    assert(bytes_written == size);

    gwyfile_item_free(item);

    item = gwyfile_item_read_memory(buffer, size, &bytes_read, &error);
    assert(!error);
    assert(bytes_read == size);
    assert(gwyfile_item_type(item) == GWYFILE_ITEM_OBJECT);
    assert(strcmp(gwyfile_item_name(item), "object") == 0);

    object = gwyfile_item_get_object(item);
    assert(object);
    assert(strcmp(gwyfile_object_name(object), "Object") == 0);

    subitem = gwyfile_object_get_with_type(object, "int", GWYFILE_ITEM_INT32);
    assert(subitem);
    assert(gwyfile_item_type(subitem) == GWYFILE_ITEM_INT32);
    assert(strcmp(gwyfile_item_name(subitem), "int") == 0);
    assert(gwyfile_item_get_int32(subitem) == 42);

    subitem = gwyfile_object_get_with_type(object, "str", GWYFILE_ITEM_STRING);
    assert(subitem);
    assert(gwyfile_item_type(subitem) == GWYFILE_ITEM_STRING);
    assert(strcmp(gwyfile_item_name(subitem), "str") == 0);
    assert(strcmp(gwyfile_item_get_string(subitem), "Shark") == 0);

    free(buffer);
    gwyfile_item_free(item);

    return 0;
}


/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
