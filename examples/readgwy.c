/*
 * $Id: readgwy.c 386 2022-02-11 12:13:18Z yeti-dn $
 *
 * This example reads a Gwyddion GWY file and prints information about
 * channels, graphs, volume data and spectra.
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

static void dump_channel_info          (const GwyfileObject *gwyf, int id);
static void dump_graph_info            (const GwyfileObject *gwyf, int id);
static void dump_spectra_info          (const GwyfileObject *gwyf, int id);
static void dump_volume_info           (const GwyfileObject *gwyf, int id);
static void dump_xyz_info              (const GwyfileObject *gwyf, int id);
static void dump_cmap_info             (const GwyfileObject *gwyf, int id);
static void dump_channel_selection_info(const GwyfileItem *item,
                                        void *user_data);

int
main(int argc, char *argv[])
{
    GwyfileObject *gwyf;
    GwyfileError *error = NULL;
    bool using_stdin = false;
    unsigned int n, i;
    int *ids;

    if (argc != 2) {
        printf("readgwy FILE.gwy\n"
               "Read a Gwyddion GWY file and print data summary.\n"
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
        fprintf(stderr, "Cannot read %s: %s\n", using_stdin ? "the standard input" : argv[1], error->message);
        gwyfile_error_clear(&error);
        exit(EXIT_FAILURE);
    }

    /* Dump information about channels, graphs and stuff. */
    if (strcmp(gwyfile_object_name(gwyf), "GwyContainer")) {
        fprintf(stderr, "The top-level object is not a GwyContainer.\n");
        exit(EXIT_FAILURE);
    }

    ids = gwyfile_object_container_enumerate_channels(gwyf, &n);
    if (n) {
        printf("Number of channels: %d\n", n);
        for (i = 0; i < n; i++)
            dump_channel_info(gwyf, ids[i]);
        free(ids);
    }

    ids = gwyfile_object_container_enumerate_graphs(gwyf, &n);
    if (n) {
        printf("Number of graphs: %d\n", n);
        for (i = 0; i < n; i++)
            dump_graph_info(gwyf, ids[i]);
        free(ids);
    }

    ids = gwyfile_object_container_enumerate_spectra(gwyf, &n);
    if (n) {
        printf("Number of spectra: %d\n", n);
        for (i = 0; i < n; i++)
            dump_spectra_info(gwyf, ids[i]);
        free(ids);
    }

    ids = gwyfile_object_container_enumerate_volume(gwyf, &n);
    if (n) {
        printf("Number of volume data: %d\n", n);
        for (i = 0; i < n; i++)
            dump_volume_info(gwyf, ids[i]);
        free(ids);
    }

    ids = gwyfile_object_container_enumerate_xyz(gwyf, &n);
    if (n) {
        printf("Number of XYZ data: %d\n", n);
        for (i = 0; i < n; i++)
            dump_xyz_info(gwyf, ids[i]);
        free(ids);
    }

    ids = gwyfile_object_container_enumerate_curvemaps(gwyf, &n);
    if (n) {
        printf("Number of curve map data: %d\n", n);
        for (i = 0; i < n; i++)
            dump_cmap_info(gwyf, ids[i]);
        free(ids);
    }

    /* Clean-up.  This call recursively frees all the objects and items. */
    gwyfile_object_free(gwyf);

    return 0;
}

/* Gather and print information about channel #id. */
static void
dump_channel_info(const GwyfileObject *gwyf, int id)
{
    char key[32];
    int32_t xres, yres;
    double xreal, yreal;
    char *xyunit = NULL, *zunit = NULL;
    GwyfileItem *item, *auxitem;
    GwyfileObject *object;
    GwyfileError *error = NULL;
    bool have_mask = false, have_show = false;

    /* Examine the main data field object. */
    snprintf(key, sizeof(key), "/%d/data", id);
    item = gwyfile_object_get(gwyf, key);

    object = gwyfile_item_get_object(item);
    if (!gwyfile_object_datafield_get(object, &error,
                                      "xres", &xres, "yres", &yres, "xreal", &xreal, "yreal", &yreal,
                                      "si_unit_xy", &xyunit, "si_unit_z", &zunit,
                                      NULL)) {
        fprintf(stderr, "Failed to read %s as datafield: %s.\n", gwyfile_item_name(item), error->message);
        gwyfile_error_clear(&error);
        return;
    }

    /* Check the presence of mask. */
    snprintf(key, sizeof(key), "/%d/mask", id);
    if ((auxitem = gwyfile_object_get_with_type(gwyf, key, GWYFILE_ITEM_OBJECT))) {
        object = gwyfile_item_get_object(auxitem);
        if (gwyfile_object_datafield_get(object, NULL, NULL))
            have_mask = true;
    }

    /* Check the presence of presentation. */
    snprintf(key, sizeof(key), "/%d/show", id);
    if ((auxitem = gwyfile_object_get_with_type(gwyf, key, GWYFILE_ITEM_OBJECT))) {
        object = gwyfile_item_get_object(auxitem);
        if (gwyfile_object_datafield_get(object, NULL, NULL))
            have_show = true;
    }

    /* Print a summary. */
    printf("#%d %s: %dx%d px, %gx%g [%s], value [%s]%s%s\n",
           id, gwyfile_item_name(item), xres, yres, xreal, yreal, xyunit, zunit,
           have_mask ? " +mask" : "",
           have_show ? " +show" : "");
    free(xyunit);
    free(zunit);

    snprintf(key, sizeof(key), "/%d/select/", id);
    gwyfile_object_foreach(gwyf, dump_channel_selection_info, key);
}

static void
dump_channel_selection_info(const GwyfileItem *item,
                            void *user_data)
{
    GwyfileObject *object;
    const char *prefix = (const char*)user_data;
    uint32_t nsel;

    if (strncmp(gwyfile_item_name(item), prefix, strlen(prefix)) || gwyfile_item_type(item) != GWYFILE_ITEM_OBJECT)
        return;

    object = gwyfile_item_get_object(item);
    if (gwyfile_object_selectionpoint_get(object, NULL, "nsel", &nsel, NULL)
        || gwyfile_object_selectioncross_get(object, NULL, "nsel", &nsel, NULL)
        || gwyfile_object_selectionline_get(object, NULL, "nsel", &nsel, NULL)
        || gwyfile_object_selectionrectangle_get(object, NULL, "nsel", &nsel, NULL)
        || gwyfile_object_selectionellipse_get(object, NULL, "nsel", &nsel, NULL)
        || gwyfile_object_selectionlattice_get(object, NULL, "nsel", &nsel, NULL)
        || gwyfile_object_selectionaxis_get(object, NULL, "nsel", &nsel, NULL)
        || gwyfile_object_selectionpath_get(object, NULL, "nsel", &nsel, NULL)) {
        printf("  %s, nsel %d\n",
               gwyfile_item_name(item) + strlen(prefix), nsel);
    }
}

/* Gather and print information about graph #id. */
static void
dump_graph_info(const GwyfileObject *gwyf, int id)
{
    char key[32];
    int32_t ncurves;
    GwyfileItem *item;
    GwyfileObject *object;
    GwyfileError *error = NULL;
    char *title;

    /* Examine the main graph model object. */
    snprintf(key, sizeof(key), "/0/graph/graph/%d", id);
    item = gwyfile_object_get(gwyf, key);

    object = gwyfile_item_get_object(item);
    if (!gwyfile_object_graphmodel_get(object, &error, "ncurves", &ncurves, "title", &title, NULL)) {
        fprintf(stderr, "Failed to read %s as graph model: %s.\n", gwyfile_item_name(item), error->message);
        gwyfile_error_clear(&error);
        return;
    }

    /* Print a summary. */
    printf("#%d %s: %d curves “%s”\n",
           id, gwyfile_item_name(item), ncurves, title);
    free(title);
}

/* Gather and print information about spectra #id. */
static void
dump_spectra_info(const GwyfileObject *gwyf, int id)
{
    char key[32];
    int32_t ndata;
    GwyfileItem *item;
    GwyfileObject *object;
    GwyfileError *error = NULL;
    char *title;

    /* Examine the main spectra object. */
    snprintf(key, sizeof(key), "/sps/%d", id);
    item = gwyfile_object_get(gwyf, key);

    object = gwyfile_item_get_object(item);
    if (!gwyfile_object_spectra_get(object, &error, "ndata", &ndata, "title", &title, NULL)) {
        fprintf(stderr, "Failed to read %s as spectra: %s.\n", gwyfile_item_name(item), error->message);
        gwyfile_error_clear(&error);
        return;
    }

    /* Print a summary. */
    printf("#%d %s: %d spectra curves “%s”\n",
           id, gwyfile_item_name(item), ndata, title);
    free(title);
}

/* Gather and print information about volume data #id. */
static void
dump_volume_info(const GwyfileObject *gwyf, int id)
{
    char key[32];
    int32_t xres, yres, zres;
    double xreal, yreal, zreal;
    char *xunit = NULL, *yunit = NULL, *zunit = NULL, *wunit = NULL;
    GwyfileItem *item;
    GwyfileObject *object;
    GwyfileError *error = NULL;

    /* Examine the main brick object. */
    snprintf(key, sizeof(key), "/brick/%d", id);
    item = gwyfile_object_get(gwyf, key);

    object = gwyfile_item_get_object(item);
    if (!gwyfile_object_brick_get(object, &error,
                                  "xres", &xres, "yres", &yres, "zres", &zres,
                                  "xreal", &xreal, "yreal", &yreal, "zreal", &zreal,
                                  "si_unit_x", &xunit, "si_unit_y", &yunit, "si_unit_z", &zunit, "si_unit_w", &wunit,
                                  NULL)) {
        fprintf(stderr, "Failed to read %s as brick: %s.\n", gwyfile_item_name(item), error->message);
        gwyfile_error_clear(&error);
        return;
    }

    /* Print a summary. */
    printf("#%d %s: %dx%dx%d px, %gx%gx%g [%s]x[%s]x[%s], value [%s]\n",
           id, gwyfile_item_name(item), xres, yres, zres, xreal, yreal, zreal, xunit, yunit, zunit, wunit);
    free(yunit);
    free(xunit);
    free(zunit);
    free(wunit);
}

/* Gather and print information about XYZ data #id. */
static void
dump_xyz_info(const GwyfileObject *gwyf, int id)
{
    char key[32];
    int32_t n;
    GwyfileItem *item;
    GwyfileObject *object;
    GwyfileError *error = NULL;

    /* Examine the main surface object. */
    snprintf(key, sizeof(key), "/xyz/%d", id);
    item = gwyfile_object_get(gwyf, key);

    object = gwyfile_item_get_object(item);
    if (!gwyfile_object_surface_get(object, &error, "n", &n, NULL)) {
        fprintf(stderr, "Failed to read %s as surface: %s.\n", gwyfile_item_name(item), error->message);
        gwyfile_error_clear(&error);
        return;
    }

    /* Print a summary. */
    printf("#%d %s: %d xyz points\n", id, gwyfile_item_name(item), n);
}

/* Gather and print information about curve map data #id. */
static void
dump_cmap_info(const GwyfileObject *gwyf, int id)
{
    char key[32];
    int32_t xres, yres, ncurves, nsegments, i;
    char *xyunit, **curveunits, **curvelabels;
    double xreal, yreal;
    GwyfileItem *item;
    GwyfileObject *object;
    GwyfileError *error = NULL;

    /* Examine the main surface object. */
    snprintf(key, sizeof(key), "/lawn/%d", id);
    item = gwyfile_object_get(gwyf, key);

    object = gwyfile_item_get_object(item);
    if (!gwyfile_object_lawn_get(object, &error,
                                 "xres", &xres, "yres", &yres,
                                 "xreal", &xreal, "yreal", &yreal,
                                 "si_unit_xy", &xyunit,
                                 "ncurves", &ncurves,
                                 "nsegments", &nsegments,
                                 "si_units_curves", &curveunits,
                                 "curve_labels", &curvelabels,
                                 NULL)) {
        fprintf(stderr, "Failed to read %s as lawn : %s.\n", gwyfile_item_name(item), error->message);
        gwyfile_error_clear(&error);
        return;
    }

    /* Print a summary. */
    printf("#%d %s: %dx%d px, %gx%g [%s], %d curves (",
           id, gwyfile_item_name(item), xres, yres, xreal, yreal, xyunit, ncurves);
    for (i = 0; i < ncurves; i++) {
        if (strlen(curvelabels[i]))
            printf("%s ", curvelabels[i]);
        printf("[%s]", curveunits[i]);
        if (i+1 < ncurves)
            printf(", ");
        free(curveunits[i]);
        free(curvelabels[i]);
    }
    free(curveunits);
    free(curvelabels);
    printf("), %d segments\n", nsegments);

    free(xyunit);
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
