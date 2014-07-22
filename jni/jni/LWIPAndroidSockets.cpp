/*
 * Copyright (c) 2014 Digital Sorcery, LLC.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * Author: Kory Herzinger <digisorcery@gmail.com>
 *
 */

#include <jni.h>
#include <android/log.h>

#include "lwip/sockets.h"

#ifdef __cplusplus
extern "C" {
#endif

// int lwip_accept(int s, struct sockaddr *addr, socklen_t *addrlen);

// int lwip_bind(int s, const struct sockaddr *name, socklen_t namelen);

/**
 * Package: com.digitalsorcery.jni.lwip
 * Class:   Sockets
 * Method:  shutdown
 */
JNIEXPORT int JNICALL
Java_com_digitalsorcery_jni_lwip_Sockets_shutdown (JNIEnv* env, jobject obj, jint s, jint how)
{
    return lwip_shutdown (s, how);
}

// int lwip_getpeername (int s, struct sockaddr *name, socklen_t *namelen);

// int lwip_getsockname (int s, struct sockaddr *name, socklen_t *namelen);

// int lwip_getsockopt (int s, int level, int optname, void *optval, socklen_t *optlen);

// int lwip_setsockopt (int s, int level, int optname, const void *optval, socklen_t optlen);

/**
 * Package: com.digitalsorcery.jni.lwip
 * Class:   Sockets
 * Method:  close
 */
JNIEXPORT int JNICALL
Java_com_digitalsorcery_jni_lwip_Sockets_close (JNIEnv* env, jobject obj, jint s)
{
    return lwip_close (s);
}

// int lwip_connect(int s, const struct sockaddr *name, socklen_t namelen);

/**
 * Package: com.digitalsorcery.jni.lwip
 * Class:   Sockets
 * Method:  listen
 */
JNIEXPORT int JNICALL
Java_com_digitalsorcery_jni_lwip_Sockets_listen (JNIEnv* env, jobject obj, jint s, jint backlog)
{
    return lwip_listen (s, backlog);
}

// int lwip_recv(int s, void *mem, size_t len, int flags);

// int lwip_read(int s, void *mem, size_t len);

// int lwip_recvfrom(int s, void *mem, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen);

// int lwip_send(int s, const void *dataptr, size_t size, int flags);

// int lwip_sendto(int s, const void *dataptr, size_t size, int flags, const struct sockaddr *to, socklen_t tolen);

/**
 * Package: com.digitalsorcery.jni.lwip
 * Class:   Sockets
 * Method:  socket
 */
JNIEXPORT int JNICALL
Java_com_digitalsorcery_jni_lwip_Sockets_socket (JNIEnv* env, jobject obj, jint domain, jint type, jint protocol)
{
    return lwip_socket (domain, type, protocol);
}

// int lwip_write(int s, const void *dataptr, size_t size);

// int lwip_select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset, struct timeval *timeout);

// int lwip_ioctl(int s, long cmd, void *argp);

// int lwip_fcntl(int s, int cmd, int val);

#ifdef __cplusplus
}
#endif
