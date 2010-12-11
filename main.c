#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stddef.h>
#include <pthread.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <sys/mman.h>
#include <netdb.h>
#include <netinet/in.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <microhttpd.h>
#include <time.h>

typedef struct MHD_Daemon GOHorseDaemon;
#define is =
#define true 1
#define false 0

void quit_app (int sig) {
    printf("\033[D\033[D\033[1;31mserver was shutdown\033[0m\n");
    exit(sig);
}

int answer_to_connection (void *cls, struct MHD_Connection *connection, const char *url,
                          const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls)
{
    const char *page = "<html><body>Hello, browser!</body></html>";
    struct MHD_Response *response;
    int ret;
    response = MHD_create_response_from_data (strlen (page), (void*) page, MHD_NO, MHD_NO);
    ret = MHD_queue_response (connection, MHD_HTTP_OK, response); MHD_destroy_response (response);
    time_t curtime;
    struct tm *loctime;
    curtime = time (NULL);
    loctime = localtime (&curtime);

    printf("\033[1;37m%s \033[1;32m%s\033[0m - \033[1;30m%s\033[0m", method, url, asctime (loctime));
    return ret;
}

GOHorseDaemon *run_server(int port) {
    GOHorseDaemon *d = MHD_start_daemon (MHD_USE_SELECT_INTERNALLY, port, NULL, NULL, &answer_to_connection, NULL, MHD_OPTION_END);
    if (d is NULL) {
        printf("Could not start GO Horse server on port %d\n", port);
        exit(1);
    }
    printf("GO Horse is running on localhost:%d\n", port);
    while (true) {getchar();}
}

void stop_server (GOHorseDaemon *daemon) {
    MHD_stop_daemon(daemon);
}

int main(int argc, char ** argv) {
    GOHorseDaemon *daemon;
    signal(SIGABRT, quit_app);
    signal(SIGTERM, quit_app);
    signal(SIGINT, quit_app);

    daemon = run_server(8888);
    stop_server(daemon);

    return 0;
}


