 /** @file udp_relay.h
 *  @brief Simple UDP Relay
 *
 *  Relays UDP packets from one port to another and down-samples packets sent
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "udp_relay.h"
#include "simple_sock.h"

#include <sys/timeb.h>

#define DEBUG			// if we want to print debug info

#define LST_PORT    1511	// Port we listen
#define DST_PORT    15111	// Port we send to
#define DST_IP_ADDR "127.0.0.1"	// IP we send to

#define TARGET_SEND_INTERVAL_ms 30	// relay send interval; will not send faster than this

int
main (void)
{
  unsigned int socketfd;	// listening socket
  struct sockaddr_in listen_addr;	// listening addr
  struct sockaddr_in pkt_addr;	// out addr
  struct in_addr recv_ip_addr;	// peer addr
  int addr_len;			// store addr len
  int pkt_len_bytes;		// store pkt len
  char pkt_buffer[9000];	// pkt buffer; 9000 is the size of a jumbo frame

  uint64_t last_send_ms = 0;	// when we sent the last pkt
  uint64_t elapsed_ms = 0;	// store time difference from last pkt 

  sock_init ();

  // create lintening socket
  socketfd = socket (AF_INET, SOCK_DGRAM, 0);
  listen_addr.sin_family = AF_INET;
  listen_addr.sin_port = htons (LST_PORT);
  listen_addr.sin_addr.s_addr = htonl (INADDR_ANY);
  bind (socketfd, (struct sockaddr *) &listen_addr, sizeof (listen_addr));

  // init pkt addr 
  pkt_addr.sin_family = AF_INET;
  addr_len = sizeof (pkt_addr);

  while (1)
    {
      // receive pkt
      pkt_len_bytes = recvfrom (socketfd, buffer, sizeof (buffer), 0, (struct sockaddr *) &pkt_addr, &addr_len);

      // at least TARGET_SEND_INTERVAL_ms must have passed since last pkt sent
      elapsed_ms = system_current_time_millis () - last_send_ms;
      if (elapsed_ms < TARGET_SEND_INTERVAL_ms) continue;		// don't send this one

      // we are relaying this pkt;  change the port and dest IP
      pkt_addr.sin_port = htons (DST_PORT);
      pkt_addr.sin_addr.s_addr = inet_addr (DST_IP_ADDR);

      DEBUG_PRINT ("Src: %s; Dst: %s\n", inet_ntoa (recv_ip_addr),
		   inet_ntoa (pkt_addr.sin_addr));

      // send pkt
      sendto (socketfd, buffer, pkt_len_bytes, 0,
	      (struct sockaddr *) &pkt_addr, sizeof (pkt_addr));

      // update last send time
      last_send_ms = system_current_time_millis ();
    }

  // close socket
  sock_close (socketfd);

  // cleanup sockets 
  sock_quit ();

  return 0;
}

// get current time in ms; should work on linux and windows
uint64_t
system_current_time_millis ()
{
#if defined(_WIN32) || defined(_WIN64)
  struct _timeb timebuffer;
  _ftime (&timebuffer);
  return (uint64_t) (((timebuffer.time * 1000) + timebuffer.millitm));
#else
  struct timeb timebuffer;
  ftime (&timebuffer);
  return (uint64_t) (((timebuffer.time * 1000) + timebuffer.millitm));
#endif
}
