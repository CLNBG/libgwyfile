/*
 * $Id: writegwy.c 343 2020-07-10 09:36:51Z yeti-dn $
 *
 * This example shows how to write a simple Gwyddion GWY file "test.gwy"
 * containing one image with a line selection and one graph with a couple of
 * curves.
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

/* rand() is not good but it exists even in Win32 and suffices here. */
#define rng() (rand()/(double)RAND_MAX - 0.5)

static double* create_image_data(int xres, int yres);
static double* create_curve_xdata(int xres, double xreal);
static double* create_curve_ydata(const double *imagedata,
                                  int xres, int row);

int
main(void)
{
    GwyfileObject *gwyf, *datafield, **curves, *graph, *selection;
    GwyfileError *error = NULL;
    double *imagedata, *xdata, *ydata;
    double seldata[8];
    int xres = 256, yres = 256;

    /* Build the file structure in a bottom-up manner: take image data, create
     * GwyDataFields, then the top-level GwyContainer. */
    imagedata = create_image_data(xres, yres);
    datafield = gwyfile_object_new_datafield(xres, yres, 1.6e-9, 1.6e-9,
                                             "data", imagedata,
                                             "si_unit_xy", "m",
                                             "si_unit_z", "A",
                                             NULL);
    /* Create some graph curves and put them to a graph.  Note the graph
     * consumes the curves array.  */
    curves = (GwyfileObject**)malloc(2*sizeof(GwyfileObject*));

    xdata = create_curve_xdata(xres, 1.6e-9);
    ydata = create_curve_ydata(imagedata, xres, yres/4);
    curves[0] = gwyfile_object_new_graphcurvemodel(xres,
                                                   "xdata", xdata,
                                                   "ydata", ydata,
                                                   "type", 1,
                                                   "color.red", 0.9,
                                                   "description", "Profile 1",
                                                   NULL);

    xdata = create_curve_xdata(xres, 1.6e-9);
    ydata = create_curve_ydata(imagedata, xres, 3*yres/4);
    curves[1] = gwyfile_object_new_graphcurvemodel(xres,
                                                   "xdata", xdata,
                                                   "ydata", ydata,
                                                   "type", 2,
                                                   "color.green", 0.8,
                                                   "description", "Profile 2",
                                                   NULL);

    graph = gwyfile_object_new_graphmodel(2,
                                          "curves", curves,
                                          "title", "Profiles",
                                          "x_unit", "m",
                                          "y_unit", "A",
                                          NULL);

    /* Create a simple selection with two lines. */
    seldata[0] = 0.1e-9;
    seldata[1] = 0.2e-9;
    seldata[2] = 1.5e-9;
    seldata[3] = 0.3e-9;

    seldata[4] = 0.3e-9;
    seldata[5] = 0.4e-9;
    seldata[6] = 0.5e-9;
    seldata[7] = 1.1e-9;

    selection = gwyfile_object_new_selectionline(2, "data(copy)", seldata, NULL);

    /* Put the first channel at "/0/data" and the first graph as
     * "/0/graph/graph/1" as usual in Gwyddion. */
    gwyf = gwyfile_object_new("GwyContainer",
                              gwyfile_item_new_object("/0/data", datafield),
                              gwyfile_item_new_object("/0/graph/graph/1", graph),
                              gwyfile_item_new_object("/0/select/line", selection),
                              NULL);

    /* Write the top-level GwyContainer to a file. */
    if (!gwyfile_write_file(gwyf, "test.gwy", &error)) {
        fprintf(stderr, "Cannot write test.gwy: %s\n", error->message);
        gwyfile_error_clear(&error);
        exit(EXIT_FAILURE);
    }

    /* Clean-up.  With the default ownership transfer rules, this call nicely
     * frees all the created objects and items, even imagedata itself. */
    gwyfile_object_free(gwyf);

    return 0;
}

/* Create a ‘simulated’ image of dimensions xres×yres. */
static double*
create_image_data(int xres, int yres)
{
    double *data = (double*)malloc(xres*yres*sizeof(double));
    int i, j, k;

    k = 0;
    for (i = 0; i < yres; i++) {
        for (j = 0; j < xres; j++, k++) {
            data[k] = rng() + 0.08*sin(i/10.0)*cos(j/5.0)
                      + ((i ? data[k-xres] : 0.0) + (j ? data[k-1] : 0.0))*(i && j ? 0.48 : 0.8);
        }
    }
    for (k = 0; k < xres*yres; k++)
        data[k] *= 1.2e-11;

    return data;
}

static double*
create_curve_xdata(int xres, double xreal)
{
    double *xdata = (double*)malloc(xres*sizeof(double));
    int i;

    for (i = 0; i < xres; i++)
        xdata[i] = (i + 0.5)/xres*xreal;

    return xdata;
}

static double*
create_curve_ydata(const double *imagedata, int xres, int row)
{
    double *ydata = (double*)malloc(xres*sizeof(double));
    memcpy(ydata, imagedata + xres*row, xres*sizeof(double));
    return ydata;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
