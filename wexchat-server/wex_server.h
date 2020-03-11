#ifndef WEX_SERVER_H_INCLUDED
#define WEX_SERVER_H_INCLUDED

//init server,call this function first
int wex_init_server(void);

void wex_run_server(int listenfd);

void str_echo(int sockfd);


#endif // WEX_SERVER_H_INCLUDED
