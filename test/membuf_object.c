/*
 * $Id: membuf_object.c 363 2022-02-10 12:15:04Z yeti-dn $
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
    GwyfileObject *object;
    GwyfileItem *item;
    GwyfileError *error = NULL;
    size_t size, bytes_written, bytes_read;
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

    object = gwyfile_object_read_memory(buffer, size, &bytes_read, &error);
    assert(!error);
    assert(bytes_read == size);

    free(buffer);

    item = gwyfile_object_get_with_type(object, "bool", GWYFILE_ITEM_BOOL);
    assert(item);
    assert(gwyfile_item_type(item) == GWYFILE_ITEM_BOOL);
    assert(gwyfile_item_get_bool(item) == true);

    item = gwyfile_object_get_with_type(object, "char", GWYFILE_ITEM_CHAR);
    assert(item);
    assert(gwyfile_item_type(item) == GWYFILE_ITEM_CHAR);
    assert(gwyfile_item_get_char(item) == 'X');

    item = gwyfile_object_get_with_type(object, "int32", GWYFILE_ITEM_INT32);
    assert(item);
    assert(gwyfile_item_type(item) == GWYFILE_ITEM_INT32);
    assert(gwyfile_item_get_int32(item) == 42);

    item = gwyfile_object_get_with_type(object, "int64", GWYFILE_ITEM_INT64);
    assert(item);
    assert(gwyfile_item_type(item) == GWYFILE_ITEM_INT64);
    assert(gwyfile_item_get_int64(item) == 1234567890ULL);

    item = gwyfile_object_get_with_type(object, "double", GWYFILE_ITEM_DOUBLE);
    assert(item);
    assert(gwyfile_item_type(item) == GWYFILE_ITEM_DOUBLE);
    assert(gwyfile_item_get_double(item) == M_PI);

    item = gwyfile_object_get_with_type(object, "string", GWYFILE_ITEM_STRING);
    assert(item);
    assert(gwyfile_item_type(item) == GWYFILE_ITEM_STRING);
    assert(strcmp(gwyfile_item_get_string(item), "Shark") == 0);

    gwyfile_object_free(object);

    return 0;
}


/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
