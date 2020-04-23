#ifndef WEX_LOGIC_INTERFACE_H_INCLUDED
#define WEX_LOGIC_INTERFACE_H_INCLUDED

/*
we hand server data to logic layer here
*/

#include "wex_protocol_parser.h"

/*
method: protocol method
content: protocol content
return the processed data by logic layer
*/
char *wex_logic_doenter(const char *method, char *content, size_t length, int socket);


#endif // WEX_LOGIC_INTERFACE_H_INCLUDED
