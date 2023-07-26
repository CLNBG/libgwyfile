/*
 * $Id: client.c 396 2023-02-08 14:03:53Z yeti-dn $
 *
 * This example is the client for server.c.  It shows how send a query using libgwyfile as a serialisation framework.
 *
 * I, the copyright holder of this work, release this work into the public domain.  This applies worldwide.  In some
 * countries this may not be legally possible; if so: I grant anyone the right to use this work for any purpose,
 * without any conditions, unless such conditions are required by law.
 */
#include "clientserver.h"

const char *servername = "localhost";

static void ask_the_server(GwyfileObject *message, int sock, unsigned int nrepeat);

int
main(int argc, char *argv[])
{
    struct sockaddr_in serv_addr;
    struct hostent *server;
    unsigned int i, array_len = 100000;
    double *array;
    int portno, sock;

    if (argc < 2) {
        printf("Usage: server PORTNUMBER\n");
        exit(EXIT_SUCCESS);
    }
    portno = atoi(argv[1]);

    /* Standard network setup. */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Cannot create socket");
        exit(EXIT_FAILURE);
    }

    server = gethostbyname(servername);
    if (server == NULL) {
        fprintf(stderr, "Cannot resolve hostname %s.\n", servername);
        exit(EXIT_FAILURE);
    }

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(server->h_addr, &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        fprintf(stderr, "Cannot connect to address %s, port %d: %s\n", servername, portno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    array = (double*)malloc(array_len*sizeof(double));
    for (i = 0; i < array_len; i++)
        array[i] = i;

    /* Send queries in bursts (3 and 5).  The server has to handle correctly what is essentially a continuous stream
     * of serialised objects. This is kind of stressing for it because we do not read anything back until we send
     * the entire burst so the server has to buffer it all. If we send too much the server can decide enough is enough
     * and kick us out. */
    ask_the_server(gwyfile_object_new("MSG",
                                      gwyfile_item_new_char("first letter", 'A'),
                                      gwyfile_item_new_bool("ok", false),
                                      gwyfile_item_new_double("value", 3.5),
                                      NULL),
                   sock, 3);
    ask_the_server(gwyfile_object_new("MSG",
                                      gwyfile_item_new_char("second letter", 'B'),
                                      gwyfile_item_new_string_copy("text", "Shark"),
                                      gwyfile_item_new_int64("sum", 1234567890L),
                                      gwyfile_item_new_double_array_const("array", array, array_len),
                                      NULL),
                   sock, 5);

    free(array);

    return 0;
}

static void
ask_the_server(GwyfileObject *message, int sock, unsigned int nrepeat)
{
    unsigned int nitems, i, ir;
    GwyfileObject *answer;
    GwyfileItem *item;
    char *buffer = NULL;
    size_t bufsize = 0, have_bytes = 0;
    int err;

    /* Send all queries over the network without checking for responses.  This works fine for short messages.  Be more
     * careful when sending large data. */
    for (ir = 0; ir < nrepeat; ir++) {
        if (send_gwyfile_message(message, sock, &buffer, &bufsize) < 0)
            exit(EXIT_FAILURE);
    }
    gwyfile_object_free(message);
    printf("Sent request (×%u), waiting for response.\n\n", nrepeat);

    /* Expect as many answeres as we sent out queries. */
    for (ir = 0; ir < nrepeat; ir++) {
        printf("Getting answer #%u.\n", ir);
        /* Make recv_gwyfile_message2() blocking. */
        while (!(answer = recv_gwyfile_message2(sock, &buffer, &bufsize, &have_bytes, &err)) && err == EAGAIN)
            ;
        if (err < 0)
            exit(EXIT_FAILURE);
        assert(answer);

        nitems = gwyfile_object_nitems(answer);
        printf("Answer has %u items\n", nitems);
        for (i = 0; i < nitems; i++) {
            item = gwyfile_object_get_nth(answer, i);
            printf("Item[%u] is called \"%s\" (type %c).\n", i, gwyfile_item_name(item), gwyfile_item_type(item));
        }
        gwyfile_object_free(answer);

        printf("\n");
    }
    free(buffer);
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
