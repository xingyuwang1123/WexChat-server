#include "wex_unixconf.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include "wexlog.h"


ssize_t readline(int fd, void *vptr, ssize_t maxlen)
{
	ssize_t n, rc;
	char c, *ptr;

	ptr = vptr;
	for (n = 1; n < maxlen; n++)
	{
		again:
		if ((rc = read(fd, &c, 1)) == 1)
		{
			*ptr++ = c;
			if (c == '\n') {
                *(ptr-1) = '\0';
                break;
			}

		}
		else if (rc == 0)
		{
			*ptr = 0;
			return(n - 1);
		}
		else
		{
			if (errno == EINTR)
				goto again;
			return(-1);
		}
	}
	*ptr = 0;
	return(n);
}


wex_confres_t *wex_loadconf(const char *filepath, wex_conf_type type) {
    wex_confres_t *res = malloc(sizeof(wex_confres_t));
    res->conf_count = 0;
    res->conf_map = shashmap_init(hashcode_str, equals_str);
    int fd = -1;
    char buf[MAXLINE];
    ssize_t n;
    if ((fd = open(filepath, O_RDONLY | O_CLOEXEC)) < 0) {
        //perror("open");
        //exit(-1);
        wexlog(wex_log_error_with_perror, "open");
    }
    while((n = readline(fd, buf, MAXLINE)) > 0) {
        //skip #
        if(buf[0] == '#' || buf[0] == '\n' || buf[0] == '\r') {
            continue;
        }
        char *namebuf = malloc(sizeof(char) * (MAXLINE/2));
        char *attrbuf = malloc(sizeof(char) * (MAXLINE/2));
        char *token = strtok(buf, "=");
        if (token != NULL) {
        //if second attr exists , put them into queue
            strncpy(namebuf, token, MAXLINE/2);
            strncpy(attrbuf, strtok(NULL, "="), MAXLINE/2);\
            shashmap_put(res->conf_map, namebuf, attrbuf);
        }
        else {
            //printf("error in reading configuration.\n");
            //exit(1);
            wexlog(wex_log_error, "error in reading configuration.");
        }
    }
    close(fd);
    return res;
}

void wex_free_conf(wex_confres_t *conf) {
    shashmap_free(conf->conf_map);
    free(conf);
}



//test main
//int main () {
//    wex_confres_t *res = wex_loadconf(CONF_FILEPATH, 1);
//    printf("configure1:%s\n", shashmap_get(res->conf_map, "SERVER_PORT"));
//    printf("configure2:%s\n", shashmap_get(res->conf_map, "MAX_THREAD_QUEUE_COUNT"));
//    printf("configure3:%s\n", shashmap_get(res->conf_map, "MAX_THREAD_QUEUE_SIZE"));
//    wex_free_conf(res);
//    return 0;
//}
