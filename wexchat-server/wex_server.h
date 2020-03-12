#ifndef WEX_SERVER_H_INCLUDED
#define WEX_SERVER_H_INCLUDED

//init server,call this function first
int wex_init_server(void);

/*
to run server
param1:listen file description returned by init funciton
*/
void wex_run_server(int listenfd);


void str_echo(void *sockfd);

void quit_server(void);


#endif // WEX_SERVER_H_INCLUDED
