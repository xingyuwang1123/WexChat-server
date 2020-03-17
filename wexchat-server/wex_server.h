#ifndef WEX_SERVER_H_INCLUDED
#define WEX_SERVER_H_INCLUDED

#include "wex_unixconf.h"
#include "wex_protocol_parser.h"



static wex_confres_t *wex_conf;

//init server,call this function first
int wex_init_server(void);

/*
to run server
param1:listen file description returned by init funciton
*/
void wex_run_server(int listenfd);


void str_echo(void *sockfd);

void wex_quit_server(void);




#endif // WEX_SERVER_H_INCLUDED
