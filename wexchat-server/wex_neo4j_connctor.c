#include "wex_neo4j_connctor.h"

#include <neo4j-client.h>
#include <errno.h>
#include <stdio.h>

static neo4j_connection_t *connection = NULL;

int wex_neo4j_connect_to_server(const char *server_address, const char *port, const char *username, const char *pass) {
    neo4j_client_init();
    //concat string
    char dest_string[208];
    dest_string[0] = '\0';
    strcat(dest_string, "neo4j://");
    strcat(dest_string, username);
    strcat(dest_string, ":");
    strcat(dest_string, pass);
    strcat(dest_string, "@");
    strcat(dest_string, server_address);
    strcat(dest_string, ":");
    strcat(dest_string, port);
    /* use NEO4J_INSECURE when connecting to disable TLS */
    connection = neo4j_connect(dest_string, NULL, NEO4J_INSECURE);
    if (connection == NULL)
    {
        return -1;
    }
    return 0;
}

int wex_neo4j_do_query(const char *query) {
    neo4j_result_stream_t *results =
            neo4j_run(connection, query, neo4j_null);
    if (results == NULL)
    {
        return -1;
    }
    neo4j_close_results(results);
    return 0;
}

int wex_neo4j_do_query_with_result(const char *query, void *result, wex_result_parser parser) {
    neo4j_result_stream_t *results =
            neo4j_run(connection, query, neo4j_null);
    if (results == NULL)
    {
        return -1;
    }
    //do here
    parser(results, result);
    neo4j_close_results(results);
    return 0;
}


/*
    neo4j_result_stream_t *results =
            neo4j_run(connection, "create (n:User {name:'33333',password:'123456'})", neo4j_null);
    if (results == NULL)
    {
        neo4j_perror(stderr, errno, "Failed to run statement");
        return EXIT_FAILURE;
    }
    neo4j_result_t *result = NULL;
    while((result = neo4j_fetch_next(results)) != NULL) {

//        if (result == NULL)
//        {
//            neo4j_perror(stderr, errno, "Failed to fetch result");
//            return EXIT_FAILURE;
//        }

        neo4j_value_t value = neo4j_result_field(result, 0);
        char buf[128];
        printf("%s\n", neo4j_tostring(value, buf, sizeof(buf)));
        neo4j_value_t value2 = neo4j_result_field(result, 1);
        char buf2[128];
        printf("%s\n", neo4j_tostring(value2, buf2, sizeof(buf2)));
    }
*/

void wex_neo4j_endup(void) {
    neo4j_close(connection);
    neo4j_client_cleanup();
}

//int main(int argc, char *argv[])
//{
//    int ret = wex_neo4j_connect_to_server("localhost", "7687", "neo4j", "137730");
//    if (ret < 0)
//        printf("err in connect\n");
//    ret = wex_neo4j_do_query("create (n:User {name:'qweqfcdsfs',password:'123456'})");
//    if (ret < 0)
//        printf("err in query\n");
//    wex_neo4j_endup();
//    return EXIT_SUCCESS;
//}
