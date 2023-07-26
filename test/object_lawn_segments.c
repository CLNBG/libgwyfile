/*
 * $Id: object_lawn_segments.c 400 2023-04-18 09:04:23Z yeti-dn $
 *
 * Test GwyLawn object construction and extraction of segmentation.
 *
 * I, the copyright holder of this work, release this work into the public domain.  This applies worldwide.  In some
 * countries this may not be legally without any conditions, unless such conditions are required by law.
 * without any conditions, unless such conditions are required by law.
 */
#include "common.h"

int
main(void)
{
    static const double data[] = {
        1.0, 3.0, -42.0, 2.0, 3.0, 0.0,   /* curve (0,0), length = 6 */
                                          /* curve (1,0), length = 0 */
                                          /* curve (2,0), length = 0 */
        -14.5, 3.75, 8.0,                 /* curve (3,0), length = 3 */
    };
    static const int32_t curvelengths[] = { 6, 0, 0, 3 };
    /* NB: There are two ints per segment (beginning, end) and we have two segments per curve, meaning FOUR times the
     * number of pixels. */
    static const int32_t segmentation[] = {
        0, 3, 2, 5,
        0, 0, 0, 0,
        0, 0, 0, 0,
        1, 2, 2, 3
    };
    const char *const segment_labels[] = { "Frist", "Second", "Extra" };
    int32_t ncurves, nsegments, i;
    char **seglab2;
    int32_t *seg2;
    const int32_t *seg3;
    GwyfileObject *lawn;

    lawn = gwyfile_object_new_lawn(1, 4, 1, 1.0, 1.5,
                                   "curvelengths(const)", curvelengths,
                                   "data(const)", data,
                                   "nsegments", 2,
                                   "segments(copy)", segmentation,
                                   "segment_labels", segment_labels,
                                   NULL);
    assert(lawn);
    assert(strcmp(gwyfile_object_name(lawn), "GwyLawn") == 0);
    gwyfile_object_add(lawn, gwyfile_item_new_bool("EXTRA_ITEM", true));

    assert(gwyfile_object_lawn_get(lawn, NULL,
                                   "ncurves", &ncurves,
                                   "nsegments", &nsegments,
                                   "segment_labels", &seglab2,
                                   NULL));
    assert(ncurves == 1);
    assert(nsegments == 2);

    assert(gwyfile_object_lawn_get(lawn, NULL, "segments", &seg3, NULL));
    assert(memcmp(seg3, segmentation, sizeof(segmentation)) == 0);

    assert(gwyfile_object_lawn_get(lawn, NULL, "segments(take)", &seg2, NULL));
    assert(memcmp(seg2, segmentation, sizeof(segmentation)) == 0);

    assert(gwyfile_object_lawn_get(lawn, NULL, "segments", &seg3, NULL));
    assert(memcmp(seg3, segmentation, sizeof(segmentation)) == 0);

    free(seg2);

    assert(seglab2);
    for (i = 0; i < nsegments; i++) {
        assert(strcmp(seglab2[i], segment_labels[i]) == 0);
        free(seglab2[i]);
    }
    free(seglab2);

    gwyfile_object_free(lawn);

    return 0;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
