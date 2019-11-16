 /** @file simple_sock.h
 *  @brief Definitions for WIN/BSD sockets
 *
 *  Definitions to abstract win/posix sockets differences
 * 
 * See:
 *   https://stackoverflow.com/questions/28027937/cross-platform-sockets
 *   http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32  
 * 
 */
#ifndef SIMPLE_SOCK_H_
#define SIMPLE_SOCK_H_

#ifdef _WIN32
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501	/* Windows XP. */
#endif
#include <winsock2.h>
#include <Ws2tcpip.h>
#else
  /* Assume that any non-Windows platform uses POSIX-style sockets instead. */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>		/* Needed for getaddrinfo() and freeaddrinfo() */
#include <unistd.h>		/* Needed for close() */

typedef int SOCKET;
#endif

// init sockets 
int sock_init (void);

// cleanup sockets 
int sock_quit (void);

// close socket
int sock_close (SOCKET sock);

#endif
