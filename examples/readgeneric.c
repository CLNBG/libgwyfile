/*
 * $Id: readgeneric.c 343 2020-07-10 09:36:51Z yeti-dn $
 *
 * This example reads a general GWY file and prints its structure.  It is
 * similar to gwydump, albeit simpler.
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

#define INDENT "  "

#ifdef _WIN32
#define llformat "I64"
#else
#define llformat "ll"
#endif

static struct {
    GwyfileItemType type;
    const char *name;
}
typenames[] = {
    { GWYFILE_ITEM_BOOL,         "Bool",        },
    { GWYFILE_ITEM_CHAR,         "Char",        },
    { GWYFILE_ITEM_INT32,        "Int32",       },
    { GWYFILE_ITEM_INT64,        "Int64",       },
    { GWYFILE_ITEM_DOUBLE,       "Double",      },
    { GWYFILE_ITEM_STRING,       "String",      },
    { GWYFILE_ITEM_OBJECT,       "Object",      },
    { GWYFILE_ITEM_CHAR_ARRAY,   "CharArray",   },
    { GWYFILE_ITEM_INT32_ARRAY,  "Int32Array",  },
    { GWYFILE_ITEM_INT64_ARRAY,  "Int64Array",  },
    { GWYFILE_ITEM_DOUBLE_ARRAY, "DoubleArray", },
    { GWYFILE_ITEM_STRING_ARRAY, "StringArray", },
    { GWYFILE_ITEM_OBJECT_ARRAY, "ObjectArray", },
};

static void dump_object_recursively(GwyfileObject *object,
                                    int level);
static void dump_item_recursively  (const GwyfileItem *item,
                                    void *user_data);

int
main(int argc, char *argv[])
{
    GwyfileObject *gwyf;
    GwyfileError *error = NULL;
    bool using_stdin = false;

    if (argc != 2) {
        printf("readgeneric FILE.gwy\n"
               "Read a generic GWY file and print its structure.\n"
               "Pass \"-\" as the filename to read the standard input.\n");
        exit(argc == 1 ? EXIT_SUCCESS : EXIT_FAILURE);
    }

    /* Read a GWY file. */
    if (strcmp(argv[1], "-") == 0) {
        using_stdin = true;
        gwyf = gwyfile_fread(stdin, SIZE_MAX, &error);
    }
    else
        gwyf = gwyfile_read_file(argv[1], &error);

    if (!gwyf) {
        fprintf(stderr, "Cannot read %s: %s\n", using_stdin ? "the standard input" : argv[1], error->message);
        gwyfile_error_clear(&error);
        exit(EXIT_FAILURE);
    }

    /* Dump its structure. */
    dump_object_recursively(gwyf, 0);

    /* Clean-up.  This call recursively frees all the objects and items. */
    gwyfile_object_free(gwyf);

    return 0;
}

static void
dump_object_recursively(GwyfileObject *object, int level)
{
    int i;

    for (i = 0; i < level; i++)
        printf(INDENT);

    /* Object name. */
    printf("Object \"%s\"\n", gwyfile_object_name(object));

    /* Use gwyfile_object_foreach() to iterate over items. */
    level++;
    gwyfile_object_foreach(object, dump_item_recursively, &level);
}

static void
dump_item_recursively(const GwyfileItem *item,
                      void *user_data)
{
    GwyfileItemType type = gwyfile_item_type(item);
    int *plevel = (int*)user_data;
    int i, level = *plevel;
    unsigned int k, array_length;

    for (i = 0; i < level; i++)
        printf(INDENT);

    /* Item name. */
    printf("Item \"%s\"", gwyfile_item_name(item));

    /* Look up human-readable item type in typenames[]. */
    for (k = 0; k < sizeof(typenames)/sizeof(typenames[0]); k++) {
        if (typenames[k].type == type) {
            printf(" type=%s", typenames[k].name);
            break;
        }
    }

    /* Array length for arrays. */
    if ((array_length = gwyfile_item_array_length(item))) {
        printf(" length=%u", array_length);
    }

    if (type == GWYFILE_ITEM_BOOL)
        printf(" %s", gwyfile_item_get_bool(item) ? "true" : "false");
    else if (type == GWYFILE_ITEM_CHAR)
        printf(" 0x%02x", gwyfile_item_get_char(item));
    else if (type == GWYFILE_ITEM_INT32)
        printf(" %i", gwyfile_item_get_int32(item));
    else if (type == GWYFILE_ITEM_INT64)
        printf(" %" llformat "i", (long long int)gwyfile_item_get_int64(item));
    else if (type == GWYFILE_ITEM_DOUBLE)
        printf(" %g", gwyfile_item_get_double(item));
    /* We could print other value types here but priting them properly would
     * unnecessarily complicate this example. */

    printf("\n");

    if (type == GWYFILE_ITEM_OBJECT)
        dump_object_recursively(gwyfile_item_get_object(item), level+1);
    else if (type == GWYFILE_ITEM_OBJECT_ARRAY) {
        GwyfileObject *const *objs = gwyfile_item_get_object_array(item);
        for (k = 0; k < array_length; k++)
            dump_object_recursively(objs[k], level+1);
    }
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
