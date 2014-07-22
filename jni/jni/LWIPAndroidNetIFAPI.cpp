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

#include "androidenetif.h"
#include "lwip/netifapi.h"
#include "ipv4/lwip/inet.h"

static JavaVM* g_javaVM (0);

class NetIF
{
public:
    NetIF ()
        : m_initMethodID (0), m_inputMethodID (0)
    {
    }
    virtual ~NetIF ()
    {
    }

    /* REMOVE
    static err_t initCallback (struct netif* netif)
    {
        err_t result (-1);
        if (netif)
        {
            NetIF* interface = (NetIF*)netif->state;
            if (interface && interface->m_initMethodID)
            {
                JNIEnv* env;
                if (g_javaVM->GetEnv ((void**)&env, JNI_VERSION_1_6) == JNI_OK)
                {
                    result = (err_t)env->CallIntMethod (interface->m_netIFObject, interface->m_initMethodID);
                }
            }
        }
        return result;
    }
    */

    static err_t inputCallback (struct pbuf* p, struct netif* netif)
    {
        err_t result (-1);
        if (netif)
        {
            NetIF* interface = (NetIF*)netif->state;
            if (interface && interface->m_inputMethodID)
            {
                JNIEnv* env;
                if (g_javaVM->GetEnv ((void**)&env, JNI_VERSION_1_6) == JNI_OK)
                {
                    jbyteArray buffer;
                    // TODO
                    result = (err_t)env->CallIntMethod (interface->m_netIFObject, interface->m_inputMethodID, buffer);
                }
            }
        }
        return result;
    }

public:
    struct netif m_netInterface;

    jobject m_netIFObject;
    jmethodID m_initMethodID;
    jmethodID m_inputMethodID;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Package: com.digitalsorcery.jni.lwip
 * Class:   NetIFAPI
 * Method:  addInterface
 */
JNIEXPORT int JNICALL
Java_com_digitalsorcery_jni_lwip_NetIFAPI_addInterface (JNIEnv* env, jobject obj, jobject netif, jobject ipaddr, jobject netmask, jobject gw)
{
    if (!g_javaVM)
        env->GetJavaVM (&g_javaVM);

    NetIF* interface = new NetIF ();
    interface->m_netIFObject = env->NewGlobalRef (netif);
    interface->m_initMethodID = env->GetMethodID (env->GetObjectClass (netif), "initInterface", "()I");
    interface->m_inputMethodID = env->GetMethodID (env->GetObjectClass (netif), "readData", "([B)I");
    env->CallVoidMethod (netif, env->GetMethodID (env->GetObjectClass (netif), "_setObjectHandle", "(J)V"), (jlong)(intptr_t)interface);

    ip_addr_t ipAddress;
    jmethodID ipaddr_getHostAddress_methodId = env->GetMethodID (env->GetObjectClass (ipaddr), "getHostAddress", "()Ljava/lang/String;");
    jstring ipaddr_hostAddress = (jstring)env->CallObjectMethod (ipaddr, ipaddr_getHostAddress_methodId);
    const char* ipaddr_nativeHostAddress = env->GetStringUTFChars (ipaddr_hostAddress, 0);
    inet_aton (ipaddr_nativeHostAddress, &ipAddress);
    env->ReleaseStringUTFChars (ipaddr_hostAddress, ipaddr_nativeHostAddress);

    ip_addr_t netmaskAddress;
    jmethodID netmask_getHostAddress_methodId = env->GetMethodID (env->GetObjectClass (netmask), "getHostAddress", "()Ljava/lang/String;");
    jstring netmask_hostAddress = (jstring)env->CallObjectMethod (netmask, netmask_getHostAddress_methodId);
    const char* netmask_nativeHostAddress = env->GetStringUTFChars (netmask_hostAddress, 0);
    inet_aton (netmask_nativeHostAddress, &netmaskAddress);
    env->ReleaseStringUTFChars (netmask_hostAddress, netmask_nativeHostAddress);

    ip_addr_t gatewayAddress;
    jmethodID gw_getHostAddress_methodId = env->GetMethodID (env->GetObjectClass (gw), "getHostAddress", "()Ljava/lang/String;");
    jstring gw_hostAddress = (jstring)env->CallObjectMethod (gw, gw_getHostAddress_methodId);
    const char* gw_nativeHostAddress = env->GetStringUTFChars (gw_hostAddress, 0);
    inet_aton (gw_nativeHostAddress, &gatewayAddress);
    env->ReleaseStringUTFChars (gw_hostAddress, gw_nativeHostAddress);

    return (int)netifapi_netif_add (&interface->m_netInterface, &ipAddress, &netmaskAddress, &gatewayAddress, (void*)interface, androidenetif_init, NetIF::inputCallback);
}

/**
 * Package: com.digitalsorcery.jni.lwip
 * Class:   NetIFAPI
 * Method:  setInterfaceAddress
 */
JNIEXPORT int JNICALL
Java_com_digitalsorcery_jni_lwip_NetIFAPI_setInterfaceAddress (JNIEnv* env, jobject obj, jobject netif, jobject ipaddr, jobject netmask, jobject gw)
{
    if (!g_javaVM)
        env->GetJavaVM (&g_javaVM);

    NetIF* interface = (NetIF*)(intptr_t) env->CallLongMethod (netif, env->GetMethodID (env->GetObjectClass (netif), "_getObjectHandle", "()J"));
    if (interface)
    {
        ip_addr_t ipAddress;
        jmethodID ipaddr_getHostAddress_methodId = env->GetMethodID (env->GetObjectClass (ipaddr), "getHostAddress", "()Ljava/lang/String;");
        jstring ipaddr_hostAddress = (jstring)env->CallObjectMethod (ipaddr, ipaddr_getHostAddress_methodId);
        const char* ipaddr_nativeHostAddress = env->GetStringUTFChars (ipaddr_hostAddress, 0);
        inet_aton (ipaddr_nativeHostAddress, &ipAddress);
        env->ReleaseStringUTFChars (ipaddr_hostAddress, ipaddr_nativeHostAddress);

        ip_addr_t netmaskAddress;
        jmethodID netmask_getHostAddress_methodId = env->GetMethodID (env->GetObjectClass (netmask), "getHostAddress", "()Ljava/lang/String;");
        jstring netmask_hostAddress = (jstring)env->CallObjectMethod (netmask, netmask_getHostAddress_methodId);
        const char* netmask_nativeHostAddress = env->GetStringUTFChars (netmask_hostAddress, 0);
        inet_aton (netmask_nativeHostAddress, &netmaskAddress);
        env->ReleaseStringUTFChars (netmask_hostAddress, netmask_nativeHostAddress);

        ip_addr_t gatewayAddress;
        jmethodID gw_getHostAddress_methodId = env->GetMethodID (env->GetObjectClass (gw), "getHostAddress", "()Ljava/lang/String;");
        jstring gw_hostAddress = (jstring)env->CallObjectMethod (gw, gw_getHostAddress_methodId);
        const char* gw_nativeHostAddress = env->GetStringUTFChars (gw_hostAddress, 0);
        inet_aton (gw_nativeHostAddress, &gatewayAddress);
        env->ReleaseStringUTFChars (gw_hostAddress, gw_nativeHostAddress);

        return (int)netifapi_netif_set_addr (&interface->m_netInterface, &ipAddress, &netmaskAddress, &gatewayAddress);
    }

    return -1;
}

/**
 * Package: com.digitalsorcery.jni.lwip
 * Class:   NetIFAPI
 * Method:  removeInterface
 */
JNIEXPORT int JNICALL
Java_com_digitalsorcery_jni_lwip_NetIFAPI_removeInterface (JNIEnv* env, jobject obj, jobject netif)
{
    if (!g_javaVM)
        env->GetJavaVM (&g_javaVM);

    NetIF* interface = (NetIF*)(intptr_t) env->CallLongMethod (netif, env->GetMethodID (env->GetObjectClass (netif), "_getObjectHandle", "()J"));
    if (interface)
    {
        return (int)netifapi_netif_remove (&interface->m_netInterface);
    }

    return -1;
}

/**
 * Package: com.digitalsorcery.jni.lwip
 * Class:   NetIFAPI
 * Method:  setInterfaceUp
 */
JNIEXPORT int JNICALL
Java_com_digitalsorcery_jni_lwip_NetIFAPI_setInterfaceUp (JNIEnv* env, jobject obj, jobject netif)
{
    if (!g_javaVM)
        env->GetJavaVM (&g_javaVM);

    NetIF* interface = (NetIF*)(intptr_t) env->CallLongMethod (netif, env->GetMethodID (env->GetObjectClass (netif), "_getObjectHandle", "()J"));
    if (interface)
    {
        return (int)netifapi_netif_set_up (&interface->m_netInterface);
    }

    return -1;
}

/**
 * Package: com.digitalsorcery.jni.lwip
 * Class:   NetIFAPI
 * Method:  setInterfaceDown
 */
JNIEXPORT int JNICALL
Java_com_digitalsorcery_jni_lwip_NetIFAPI_setInterfaceDown (JNIEnv* env, jobject obj, jobject netif)
{
    if (!g_javaVM)
        env->GetJavaVM (&g_javaVM);

    NetIF* interface = (NetIF*)(intptr_t) env->CallLongMethod (netif, env->GetMethodID (env->GetObjectClass (netif), "_getObjectHandle", "()J"));
    if (interface)
    {
        return (int)netifapi_netif_set_down (&interface->m_netInterface);
    }

    return -1;
}

/**
 * Package: com.digitalsorcery.jni.lwip
 * Class:   NetIFAPI
 * Method:  setInterfaceDefault
 */
JNIEXPORT int JNICALL
Java_com_digitalsorcery_jni_lwip_NetIFAPI_setInterfaceDefault (JNIEnv* env, jobject obj, jobject netif)
{
    if (!g_javaVM)
        env->GetJavaVM (&g_javaVM);

    NetIF* interface = (NetIF*)(intptr_t) env->CallLongMethod (netif, env->GetMethodID (env->GetObjectClass (netif), "_getObjectHandle", "()J"));
    if (interface)
    {
        return (int)netifapi_netif_set_default (&interface->m_netInterface);
    }

    return -1;
}

/**
 * Package: com.digitalsorcery.jni.lwip
 * Class:   NetIFAPI
 * Method:  dhcpStart
 */
JNIEXPORT int JNICALL
Java_com_digitalsorcery_jni_lwip_NetIFAPI_dhcpStart (JNIEnv* env, jobject obj, jobject netif)
{
#if LWIP_DHCP
    if (!g_javaVM)
        env->GetJavaVM (&g_javaVM);

    NetIF* interface = (NetIF*)(intptr_t) env->CallLongMethod (netif, env->GetMethodID (env->GetObjectClass (netif), "_getObjectHandle", "()J"));
    if (interface)
    {
        return (int)netifapi_dhcp_start (&interface->m_netInterface);
    }
#endif

    return -1;
}

/**
 * Package: com.digitalsorcery.jni.lwip
 * Class:   NetIFAPI
 * Method:  dhcpStop
 */
JNIEXPORT int JNICALL
Java_com_digitalsorcery_jni_lwip_NetIFAPI_dhcpStop (JNIEnv* env, jobject obj, jobject netif)
{
#if LWIP_DHCP
    if (!g_javaVM)
        env->GetJavaVM (&g_javaVM);

    NetIF* interface = (NetIF*)(intptr_t) env->CallLongMethod (netif, env->GetMethodID (env->GetObjectClass (netif), "_getObjectHandle", "()J"));
    if (interface)
    {
        return (int)netifapi_dhcp_stop (&interface->m_netInterface);
    }
#endif

    return -1;
}

/**
 * Package: com.digitalsorcery.jni.lwip
 * Class:   NetIFAPI
 * Method:  autoIPStart
 */
JNIEXPORT int JNICALL
Java_com_digitalsorcery_jni_lwip_NetIFAPI_autoIPStart (JNIEnv* env, jobject obj, jobject netif)
{
#if LWIP_AUTOIP
    if (!g_javaVM)
        env->GetJavaVM (&g_javaVM);

    NetIF* interface = (NetIF*)(intptr_t) env->CallLongMethod (netif, env->GetMethodID (env->GetObjectClass (netif), "_getObjectHandle", "()J"));
    if (interface)
    {
        return (int)netifapi_autoip_start (&interface->m_netInterface);
    }
#endif

    return -1;
}

/**
 * Package: com.digitalsorcery.jni.lwip
 * Class:   NetIFAPI
 * Method:  autoIPStop
 */
JNIEXPORT int JNICALL
Java_com_digitalsorcery_jni_lwip_NetIFAPI_autoIPStop (JNIEnv* env, jobject obj, jobject netif)
{
#if LWIP_AUTOIP
    if (!g_javaVM)
        env->GetJavaVM (&g_javaVM);

    NetIF* interface = (NetIF*)(intptr_t) env->CallLongMethod (netif, env->GetMethodID (env->GetObjectClass (netif), "_getObjectHandle", "()J"));
    if (interface)
    {
        return (int)netifapi_autoip_stop (&interface->m_netInterface);
    }
#endif

    return -1;
}

#ifdef __cplusplus
}
#endif
