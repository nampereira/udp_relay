 /** @file udp_relay.h
 *  @brief Definitions for simple udp relay
 *
 *  Definitions for simple  WIN/BSD sockets
 * 
 * See:
 *   https://stackoverflow.com/questions/28027937/cross-platform-sockets
 *   http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32  
 *
 */
#ifndef UDP_RELAY_H_
#define UDP_RELAY_H_

#define DEBUG

#if defined(DEBUG)
#define DEBUG_PRINT(fmt, args...) fprintf(stderr, "DEBUG: %s:%d:%s(): " fmt, \
    __FILE__, __LINE__, __func__, ##args)
#else
#define DEBUG_PRINT(fmt, args...)	/* don't do anything in release builds */
#endif

// get current time in ms; should work on linux and windows
uint64_t system_current_time_millis ();

#endif
