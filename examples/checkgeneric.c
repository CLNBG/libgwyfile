/*
 * $Id: checkgeneric.c 318 2020-06-05 17:04:48Z yeti-dn $
 *
 * This example reads a generic GWY file and checks it for some violations of
 * the GWY file format specification.
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

int
main(int argc, char *argv[])
{
    GwyfileObject *gwyf;
    GwyfileErrorList errlist;
    GwyfileError *error = NULL;
    bool using_stdin = false;
    unsigned int i;

    gwyfile_error_list_init(&errlist);

    if (argc != 2) {
        printf("checkgeneric FILE.gwy\n"
               "Read a generic GWY file and check it for problems.\n"
               "Pass \"-\" as the filename to read the standard input.\n");
        exit(argc == 1 ? EXIT_SUCCESS : EXIT_FAILURE);
    }

    /* Read a Gwyddion GWY file. */
    if (strcmp(argv[1], "-") == 0) {
        using_stdin = true;
        gwyf = gwyfile_fread(stdin, SIZE_MAX, &error);
    }
    else
        gwyf = gwyfile_read_file(argv[1], &error);

    if (!gwyf) {
        fprintf(stderr, "Cannot read %s: %s\n",
                using_stdin ? "the standard input" : argv[1], error->message);
        gwyfile_error_clear(&error);
        exit(EXIT_FAILURE);
    }

    /* Check validity. */
    if (gwyfile_check_object(gwyf, GWYFILE_CHECK_FLAG_VALIDITY, &errlist)) {
        printf("No validity problems found.\n");
    }
    else {
        printf("Validity problems:\n");
        for (i = 0; i < errlist.n; i++) {
            error = errlist.errors[i];
            printf("%s (%u)\n", error->message, error->code);
        }
    }
    gwyfile_error_list_clear(&errlist);

    /* Check warnings. */
    if (gwyfile_check_object(gwyf, GWYFILE_CHECK_FLAG_WARNING, &errlist)) {
        printf("No warnings found.\n");
    }
    else {
        printf("Warnings:\n");
        for (i = 0; i < errlist.n; i++) {
            error = errlist.errors[i];
            printf("%s (%u)\n", error->message, error->code);
        }
    }
    gwyfile_error_list_clear(&errlist);

    /* Clean-up.  This call recursively frees all the objects and items. */
    gwyfile_object_free(gwyf);

    return 0;
}

/* vim: set cin et ts=4 sw=4 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
