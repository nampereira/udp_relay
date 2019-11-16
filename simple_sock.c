 /** @file simple_sock.h
 *  @brief WIN/BSD sockets
 *
 *  Abstract win/posix sockets differences
 * 
 * See:
 *   https://stackoverflow.com/questions/28027937/cross-platform-sockets
 *   http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32  
 *
 *   *link with Ws2_32 lib on Windows
 */
#include "simple_sock.h"

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
#endif

int
sock_init (void)
{
#ifdef _WIN32
  WSADATA wsa_data;
  return WSAStartup (MAKEWORD (1, 1), &wsa_data);
#else
  return 0;
#endif
}

int
sock_quit (void)
{
#ifdef _WIN32
  return WSACleanup ();
#else
  return 0;
#endif
}

/* Note: For POSIX, typedef SOCKET as an int. */
int
sock_close (SOCKET sock)
{

  int status = 0;

#ifdef _WIN32
  status = shutdown (sock, SD_BOTH);
  if (status == 0)
    {
      status = closesocket (sock);
    }
#else
  status = shutdown (sock, SHUT_RDWR);
  if (status == 0)
    {
      status = close (sock);
    }
#endif

  return status;
}
