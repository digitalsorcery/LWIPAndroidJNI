package com.digitalsorcery.jni.lwip;

public class Sockets {
    public static int SHUT_RD = 0;
    public static int SHUT_WR = 1;
    public static int SHUT_RDWR = 2;

    public static int AF_UNSPEC = 0;
    public static int AF_INET = 2;

    public static int SOCK_STREAM = 1;
    public static int SOCK_DGRAM = 2;
    public static int SOCK_RAW = 3;

    // TODO: accept

    // TODO: bind

    /**
     * Name:        shutdown
     *
     * Description: The shutdown() call causes all or part of a full-duplex connection on the socket
     *              associated with sockfd to be shut down. If how is SHUT_RD, further receptions will
     *              be disallowed. If how is SHUT_WR, further transmissions will be disallowed. If how
     *              is SHUT_RDWR, further receptions and transmissions will be disallowed.
     *
     * Returns:     On success, zero is returned. On error, -1 is returned and errno is set appropriately.
     */
    public static native int shutdown (int sockfd, int how);

    // TODO: getpeername

    // TODO: getsockname

    // TODO: getsockopt

    // TODO: setsockopt

    /**
     * Name:        close
     *
     * Description: The close() call closes a file descriptor, so that it no longer refers to any file and
     *              may be reused. Any record locks (see fcntl(2)) held on the file it was associated with,
     *              and owned by the process, are removed (regardless of the file descriptor that was used
     *              to obtain the lock).
     *
     *              If fd is the last file descriptor referring to the underlying open file description
     *              (see open(2)), the resources associated with the open file description are freed; if the
     *              descriptor was the last reference to a file which has been removed using unlink(2), the
     *              file is deleted.
     *
     * Returns:     On success, zero is returned. On error, -1 is returned and errno is set appropriately.
     */
    public static native int close (int fd);

    // TODO: connect

    /**
     * Name:        listen
     *
     * Description: listen() marks the socket referred to by sockfd as a passive socket, that is, as a socket
     *              that will be used to accept incoming connection requests using accept(2).
     *
     *              The sockfd argument is a file descriptor that refers to a socket of type SOCK_STREAM or
     *              SOCK_SEQPACKET.
     *
     *              The backlog argument defines the maximum length to which the queue of pending connections
     *              for sockfd may grow. If a connection request arrives when the queue is full, the client may
     *              receive an error with an indication of ECONNREFUSED or, if the underlying protocol supports
     *              retransmission, the request may be ignored so that a later reattempt at connection succeeds.
     *
     * Returns:     On success, zero is returned. On error, -1 is returned and errno is set appropriately.
     */
    public static native int listen (int sockfd, int backlog);

    // TODO: recv

    // TODO: read

    // TODO: recvfrom

    // TODO: send

    // TODO: sendto

    /**
     * Name:        socket
     *
     * Description: socket() creates an endpoint for communication and returns a descriptor.
     *
     *              The domain argument specifies a communication domain; this selects the protocol family which
     *              will be used for communication.
     *
     *              The socket has the indicated type, which specifies the communication semantics.
     *
     *              TODO
     *
     * Returns:     On success, a file descriptor for the new socket is returned. On error, -1 is returned,
     *              and errno is set appropriately.
     */
    public static native int socket (int domain, int type, int protocol);

    // TODO: write

    // TODO: select

    // TODO: ioctl

    // TODO: fcntl

    static {
        System.loadLibrary ("lwip-android-jni");
    }
}
