#include <cstdio>
#include <cstdlib>
#include <cstring>

// ~/c/wsserver/Debug

#include "ws.h"

void onopen( ws_cli_conn_t* client ){
  char *addr  = ws_getaddress(client);
  char *port = ws_getport(client);
  printf("connection opened, addr: %s, port: %s\n", addr, port);
}

void onclose( ws_cli_conn_t* client ){
  ( (void) client );
  char *addr = ws_getaddress(client);
  printf("connection closed, addr: %s\n", addr);
}


void onmessage( ws_cli_conn_t* client, const unsigned char* msg, uint64_t size,
                int type ){
  ( (void) client );
  ( (void) msg );
  ( (void) size );
  ( (void) type );
  ws_sendframe_bcast(8910, (const char *)msg, size, type);
  printf("broadcasting: '%.32s'\n", msg );
}

int main( int argc, char *args[] ){
  printf( "Hello world!\n" );
  struct ws_server server;
  server.host = "192.168.68.89";
  server.port = 8910;
  server.thread_loop = 0;
  server.timeout_ms = 3000;
  server.evs.onopen = &onopen;
  server.evs.onclose = &onclose;
  server.evs.onmessage = &onmessage;

  ws_socket(&server);

  printf( "Goodbye!\n");
}
