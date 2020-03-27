#ifndef WEX_NEO4J_CONNCTOR_INCLUDED
#define WEX_NEO4J_CONNCTOR_INCLUDED

#include <neo4j-client.h>

typedef void (*wex_result_parser)(neo4j_result_stream_t *results, void *res);

/*
connect to neo4j server,return negative number if failed
*/
int wex_neo4j_connect_to_server(const char *server_address, const char *port, const char *username, const char *pass);

/*
query statement
auery: write cypher statement here
*/
int wex_neo4j_do_query(const char *query);

/*
do query and return a void* result ,you should impement the parser used to inject into your own struct
allocate memory in your parser
*/
int wex_neo4j_do_query_with_result(const char *query, void *result, wex_result_parser parser);

/*
clean the connector when you don't use it anymore
*/
void wex_neo4j_endup(void);

#endif // WEX_NEO4J_CONNCTOR_INCLUDED
