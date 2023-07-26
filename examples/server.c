/*
 * $Id: server.c 396 2023-02-08 14:03:53Z yeti-dn $
 *
 * This example is the server for client.c.  It shows how to answer queries using libgwyfile as a serialisation
 * framework.
 *
 * I, the copyright holder of this work, release this work into the public domain.  This applies worldwide.  In some
 * countries this may not be legally possible; if so: I grant anyone the right to use this work for any purpose,
 * without any conditions, unless such conditions are required by law.
 */
#include "clientserver.h"

static void           connection_handler(int sock);
static GwyfileObject* answer_to_message (GwyfileObject *message);

int
main(int argc, char *argv[])
{
    int portno, socket_desc, client_sock, c = sizeof(struct sockaddr_in);
    struct sockaddr_in server, client;

    if (argc < 2) {
        printf("Usage: server PORTNUMBER\n");
        exit(EXIT_SUCCESS);
    }

    /* Standard network setup. */
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        perror("Cannot create socket");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    portno = atoi(argv[1]);
    server.sin_port = htons(portno);

    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("bind() failed");
        exit(EXIT_FAILURE);
    }

    listen(socket_desc, 3);

    /* Main loop handling client requests.  It runs indefinitely, i.e. until the process is terminated externally. */
    while ((client_sock = accept(socket_desc, (struct sockaddr*)&client, (socklen_t*)&c)) > 0) {
        printf("Connection accepted.\n");
        /* Normally we would do this in a subprocess or thread.  Do not bother in the example. */
        connection_handler(client_sock);
        close(client_sock);
    }

    if (client_sock < 0) {
        perror("accept() failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}

/* Handle a client connection. */
static void
connection_handler(int sock)
{
    GwyfileObject *message, *answer;
    char *recvbuffer = NULL, *sendbuffer = NULL;
    size_t recvbufsize = 0, sendbufsize = 0, recvlen = 0;
    int err;

    /* Receive data from the client.  Use a simple busy wait to block on recv_gwyfile_message2().  */
    while ((message = recv_gwyfile_message2(sock, &recvbuffer, &recvbufsize, &recvlen, &err)) || err == EAGAIN) {
        if (err == EAGAIN)
            continue;
        answer = answer_to_message(message);
        gwyfile_object_free(message);
        /* Random sleep for the spectators.  Otherwise everything happens in an instant. */
        usleep(rand() % 1000000);
        if ((err = send_gwyfile_message(answer, sock, &sendbuffer, &sendbufsize)) < 0) {
            gwyfile_object_free(answer);
            break;
        }
    }

    if (err == 0)
        printf("Communication finished successfully.\n\n");
    else
        fprintf(stderr, "Communication failed.\n\n");

    free(sendbuffer);
    free(recvbuffer);
}

static GwyfileObject*
answer_to_message(GwyfileObject *message)
{
    const char *dont = "I thought I had told you a thousand times that I really do not like ";
    GwyfileObject *answer;
    GwyfileItem *item, *newitem;
    unsigned int nitems, i, len, ll = strlen(dont);
    GwyfileItemType type;
    const char *name, *s;
    char *t;

    /* Send something back depending on what we got.  Mostly various modification of the items in the query. */
    answer = gwyfile_object_new("MSG", NULL);
    nitems = gwyfile_object_nitems(message);
    for (i = 0; i < nitems; i++) {
        item = gwyfile_object_get_nth(message, i);
        type = gwyfile_item_type(item);
        name = gwyfile_item_name(item);
        newitem = NULL;
        if (type == GWYFILE_ITEM_INT32)
            newitem = gwyfile_item_new_int32(name, 2*gwyfile_item_get_int32(item));
        else if (type == GWYFILE_ITEM_DOUBLE)
            newitem = gwyfile_item_new_double(name, -gwyfile_item_get_double(item));
        else if (type == GWYFILE_ITEM_BOOL)
            newitem = gwyfile_item_new_bool(name, !gwyfile_item_get_bool(item));
        else if (type == GWYFILE_ITEM_INT64) {
            char hexbuf[8*2+3];
            snprintf(hexbuf, sizeof(hexbuf), "0x%016lx", (unsigned long)gwyfile_item_get_int64(item));
            newitem = gwyfile_item_new_string_copy(name, hexbuf);
        }
        else if (type == GWYFILE_ITEM_STRING) {
            s = gwyfile_item_get_string(item);
            len = strlen(s);
            t = malloc(len + ll + 1);
            memcpy(t, dont, ll);
            memcpy(t + ll, s, len+1);
            newitem = gwyfile_item_new_string(name, t);
        }
        else if (type == GWYFILE_ITEM_DOUBLE_ARRAY) {
            /* Since @message can be freed before we send back the response, take the ownership of the data array. */
            if (gwyfile_item_owns_data(item)) {
                double *data = gwyfile_item_take_double_array(item);
                unsigned int j, n = gwyfile_item_array_length(item);
                for (j = 0; j < n; j++)
                    data[i] *= 2.0;
                /* This is slightly reckless as we completely transfer ownership and data[] is allowed to be freed
                 * immediately in gwyfile_item_new_double_array(). Nothing in Gwyfile is going to actually accesss (or
                 * free) the data in @item, but the possibly dangling pointer will be lying around. */
                newitem = gwyfile_item_new_double_array(name, data, n);
            }
            else {
                fprintf(stderr, "Cannot take ownership of double array item %s.\n", name);
            }
        }

        if (newitem)
            gwyfile_object_add(answer, newitem);
    }

    return answer;
}

/* vim: set cin et ts=4 sw=4 columns=120 tw=119 cino=>1s,e0,n0,f0,{0,}0,^0,\:1s,=0,g1s,h0,t0,+1s,c3,(0,u0 : */
