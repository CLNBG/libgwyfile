/*
 * $Id: object_copy_if_owned.c 363 2022-02-10 12:15:04Z yeti-dn $
 *
 * Test object copying.
 *
 * I, the copyright holder of this work, release this work into the public domain.  This applies worldwide.  In some
 * countries this may not be legally without any conditions, unless such conditions are required by law.
 * without any conditions, unless such conditions are required by law.
 */
#include "common.h"

int
main(void)
{
    static int32_t int32_array_static[] = { 1, 2, 43, -3 };
    static int64_t int64_array_static[] = { -1, 0, 65535 };
    static double double_array_static[] = { M_PI, 2.0 };

    GwyfileObject *object, *copy;
    GwyfileError *error = NULL;
    int32_t *int32_array_dynamic;
    int64_t *int64_array_dynamic;
    double *double_array_dynamic;
    size_t size, bytes_written;
    void *buffer, *copybuffer;

    int32_array_dynamic = malloc(3*sizeof(int32_t));
    assert(int32_array_dynamic);
    int32_array_dynamic[0] = 5;
    int32_array_dynamic[1] = -2;
    int32_array_dynamic[2] = 255;

    int64_array_dynamic = malloc(3*sizeof(int64_t));
    assert(int64_array_dynamic);
    int64_array_dynamic[0] = 0;
    int64_array_dynamic[1] = 1;
    int64_array_dynamic[2] = 69;

    double_array_dynamic = malloc(1*sizeof(double));
    assert(double_array_dynamic);
    double_array_dynamic[0] = -0.5;

    object = gwyfile_object_new("Test",
                                gwyfile_item_new_bool("bool", true),
                                gwyfile_item_new_char("char", 'X'),
                                gwyfile_item_new_int32("int32", 42),
                                gwyfile_item_new_int64("int64", 1234567890ULL),
                                gwyfile_item_new_double("double", M_PI),
                                gwyfile_item_new_string_const("static-string", "Whale"),
                                gwyfile_item_new_string_copy("owned-string", "Shark"),
                                gwyfile_item_new_int32_array_const("static-int32s", int32_array_static, 4),
                                gwyfile_item_new_int32_array("owned-int32s", int32_array_dynamic, 3),
                                gwyfile_item_new_int64_array_const("static-int64s", int64_array_static, 3),
                                gwyfile_item_new_int64_array("owned-int64s", int64_array_dynamic, 3),
                                gwyfile_item_new_double_array_const("static-doubles", double_array_static, 2),
                                gwyfile_item_new_double_array("owned-doubles", double_array_dynamic, 1),
                                gwyfile_item_new_object("obj",
                                                        gwyfile_object_new("Nested",
                                                                           gwyfile_item_new_string_const("static-string", "Whale"),
                                                                           gwyfile_item_new_string_copy("owned-string", "Shark"),
                                                                           NULL)),
                                NULL);
    assert(object);

    size = gwyfile_object_size(object);
    buffer = malloc(size);
    assert(buffer);
    bytes_written = gwyfile_object_write_memory(object, buffer, size, &error);
    assert(!error);
    assert(bytes_written == size);

    copy = gwyfile_object_copy(object, GWYFILE_COPY_IF_OWNED);
    gwyfile_object_free(object);

    assert(gwyfile_object_size(copy) == size);
    copybuffer = malloc(size);
    assert(copybuffer);
    bytes_written = gwyfile_object_write_memory(copy, copybuffer, size, &error);
    assert(!error);
    assert(bytes_written == size);

    gwyfile_object_free(copy);

    assert(memcmp(buffer, copybuffer, size) == 0);
    free(buffer);
    free(copybuffer);

    return 0;
}


/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
