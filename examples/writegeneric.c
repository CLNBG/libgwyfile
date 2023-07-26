/*
 * $Id: writegeneric.c 343 2020-07-10 09:36:51Z yeti-dn $
 *
 * This example shows how to write a simple generic GWY file "test.gwy"
 * containing all kinds of basic datatypes.
 *
 * I, the copyright holder of this work, release this work into the public
 * domain.  This applies worldwide.  In some countries this may not be legally
 * possible; if so: I grant anyone the right to use this work for any purpose,
 * without any conditions, unless such conditions are required by law.
 */
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include "gwyfile.h"

/* Array length. */
#define AL(x) (sizeof(x)/sizeof((x)[0]))

enum {
    OBJECTS_DATA_LEN = 2,
    STRINGS_DATA_LEN = 3,
};

static char char_data[21];
static int32_t int32_data[6];
static int64_t int64_data[15];
static double double_data[13];

int
main(void)
{
    GwyfileObject *gwyf, **objects_data;
    GwyfileError *error = NULL;
    char **strings_data;
    unsigned int i;

    /* Build the file structure.  We use the _copy functions here so the
     * arrays will not be consumed.  */
    gwyf = gwyfile_object_new("MyStruct",
                              gwyfile_item_new_bool("bool", true),
                              gwyfile_item_new_char("char", 'X'),
                              gwyfile_item_new_int32("int32", 42),
                              gwyfile_item_new_int64("int64", 1234567890ULL),
                              gwyfile_item_new_double("double", 3.14),
                              gwyfile_item_new_string_copy("string", "Shark"),
                              gwyfile_item_new_char_array_copy("chars", char_data, AL(char_data)),
                              gwyfile_item_new_int32_array_copy("int32s", int32_data, AL(int32_data)),
                              gwyfile_item_new_int64_array_copy("int64s", int64_data, AL(int64_data)),
                              gwyfile_item_new_double_array_copy("doubles", double_data, AL(double_data)),
                              NULL);

    /* Create a string array.  This is a bit more involved.  Note the array
     * strings_data[] will be also consumed. */
    strings_data = (char**)malloc(sizeof(char*)*STRINGS_DATA_LEN);
    for (i = 0; i < STRINGS_DATA_LEN; i++) {
        strings_data[i] = (char*)malloc(8);
        snprintf(strings_data[i], 8, "string%u", i);
    }
    gwyfile_object_add(gwyf, gwyfile_item_new_string_array("strings", strings_data, STRINGS_DATA_LEN));

    /* Create an object array.  This is a bit more involved.  Note the array
     * objects_data[] will be also consumed. */
    objects_data = (GwyfileObject**)malloc(sizeof(GwyfileObject*)*OBJECTS_DATA_LEN);
    for (i = 0; i < OBJECTS_DATA_LEN; i++)
        objects_data[i] = gwyfile_object_new("MySubStruct", gwyfile_item_new_int32("i", i), NULL);
    gwyfile_object_add(gwyf, gwyfile_item_new_object_array("objects", objects_data, OBJECTS_DATA_LEN));

    /* Write the top-level object to a file. */
    if (!gwyfile_write_file(gwyf, "test.gwy", &error)) {
        fprintf(stderr, "Cannot write test.gwy: %s\n", error->message);
        gwyfile_error_clear(&error);
        exit(EXIT_FAILURE);
    }

    /* Clean-up.  With the default ownership transfer rules, this call nicely
     * frees all the created objects and items. */
    gwyfile_object_free(gwyf);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
