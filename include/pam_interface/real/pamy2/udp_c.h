#ifndef UDP_C_FILE
#define UDP_C_FILE

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

// code declared in /src/udp_communication.cpp

/**
 * Data structure encapsulating all attributes required
 * to manipulate a socket
 */
struct c_socket
{
    sockaddr_in addr;
    int descriptor;
    int rcv_buffer_size;
    uint size = sizeof(sockaddr_in);
};

/**
 * Create a connection and fill the attributes of socket_
 * @param socket_ the structure to fill
 * @param IP IP of the computer to connect to
 * @param port port of the udp socket of the computer to connect to
 * @param recv_buffer_size size (in bits) of the UDP telegram that will be
 * received by the socket
 */
int c_init_socket(c_socket* socket_,
                  const char* ip,
                  uint port,
                  int recv_buffer_size);

/**
 * Send a UDP telegram to the socket. The socket must have been initialized
 * by the c_init_socket function.
 * @param socket_ the UDP socket
 * @param message pointer to the telegram that has to be sent
 * @param message_size size (in bits) of the telegram that will be sent
 */
ssize_t c_send(c_socket* socket_, void* message, int message_size);

/**
 * Read the oldest UDP telegram still available in the queue.
 * The socket must have been initialized via a call to the
 * c_init_socket function.
 * @param socket_ the UDP socket.
 * @param pointer to the memory slot in which the telegram data will be
 * copied.
 * @param message_size size (in bits) of the telegram that will be read.
 */
ssize_t c_receive(c_socket* socket_, void* message, int message_size);

#endif
