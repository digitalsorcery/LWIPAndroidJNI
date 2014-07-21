LOCAL_PATH := $(call my-dir)

############################################################
# Build LWIP statically
############################################################

include $(CLEAR_VARS)

LWIP_SRC := lwip-1.4.1/src
LWIP_API_SRC := $(LWIP_SRC)/api
LWIP_CORE_SRC := $(LWIP_SRC)/core
LWIP_INCLUDE := $(LWIP_SRC)/include
LWIP_NETIF_SRC := $(LWIP_SRC)/netif

LOCAL_C_INCLUDES := $(LWIP_INCLUDE)

LOCAL_MODULE := lwip-android

LWIP_API_SRC_FILES := $(LWIP_API_SRC)/api_lib.c $(LWIP_API_SRC)/api_msg.c $(LWIP_API_SRC)/err.c \
    $(LWIP_API_SRC)/netbuf.c $(LWIP_API_SRC)/netdb.c $(LWIP_API_SRC)/netifapi.c \
    $(LWIP_API_SRC)/sockets.c $(LWIP_API_SRC)/tcpip.c

LWIP_IPV4_SRC := $(LWIP_CORE_SRC)/ipv4
LWIP_CORE_IPV4_SRC_FILES := $(LWIP_IPV4_SRC)/autoip.c $(LWIP_IPV4_SRC)/icmp.c $(LWIP_IPV4_SRC)/igmp.c \
    $(LWIP_IPV4_SRC)/inet_chksum.c $(LWIP_IPV4_SRC)/inet.c $(LWIP_IPV4_SRC)/ip_addr.c \
    $(LWIP_IPV4_SRC)/ip_frag.c $(LWIP_IPV4_SRC)/ip.c

LWIP_IPV6_SRC := $(LWIP_CORE_SRC)/ipv6
LWIP_CORE_IPV6_SRC_FILES := $(LWIP_IPV6_SRC)/icmp6.c $(LWIP_IPV6_SRC)/inet6.c \
    $(LWIP_IPV6_SRC)/ip6_addr.c $(LWIP_IPV6_SRC)/ip6.c

LWIP_SNMP_SRC := $(LWIP_CORE_SRC)/snmp
LWIP_CORE_SNMP_SRC_FILES := $(LWIP_SNMP_SRC)/asn1_dec.c $(LWIP_SNMP_SRC)/asn1_enc.c $(LWIP_SNMP_SRC)/mib_structs.c \
    $(LWIP_SNMP_SRC)/mib2.c $(LWIP_SNMP_SRC)/msg_in.c $(LWIP_SNMP_SRC)/msg_out.c

LWIP_CORE_SRC_FILES := $(LWIP_CORE_SRC)/def.c $(LWIP_CORE_SRC)/dhcp.c $(LWIP_CORE_SRC)/dns.c $(LWIP_CORE_SRC)/init.c \
    $(LWIP_CORE_SRC)/mem.c $(LWIP_CORE_SRC)/memp.c $(LWIP_CORE_SRC)/netif.c $(LWIP_CORE_SRC)/pbuf.c $(LWIP_CORE_SRC)/raw.c \
    $(LWIP_CORE_SRC)/stats.c $(LWIP_CORE_SRC)/sys.c $(LWIP_CORE_SRC)/tcp_in.c $(LWIP_CORE_SRC)/tcp_out.c \
    $(LWIP_CORE_SRC)/tcp.c $(LWIP_CORE_SRC)/timers.c $(LWIP_CORE_SRC)/udp.c \
    $(LWIP_CORE_IPV4_SRC_FILES) $(LWIP_CORE_IPV6_SRC_FILES) $(LWIP_CORE_SNMP_SRC_FILES)

LWIP_PPP_SRC := $(LWIP_NETIF_SRC)/ppp
LWIP_NETIF_PPP_SRC_FILES := $(LWIP_PPP_SRC)/auth.c $(LWIP_PPP_SRC)/chap.c $(LWIP_PPP_SRC)/chpms.c $(LWIP_PPP_SRC)/fsm.c \
    $(LWIP_PPP_SRC)/ipcp.c $(LWIP_PPP_SRC)/lcp.c $(LWIP_PPP_SRC)/magic.c $(LWIP_PPP_SRC)/md5.c $(LWIP_PPP_SRC)/pap.c \
    $(LWIP_PPP_SRC)/ppp_oe.c $(LWIP_PPP_SRC)/ppp.c $(LWIP_PPP_SRC)/randm.c $(LWIP_PPP_SRC)/vj.c

LWIP_NETIF_SRC_FILES := $(LWIP_NETIF_SRC)/etharp.c $(LWIP_NETIF_SRC)/ethernetif.c $(LWIP_NETIF_SRC)/slipif.c \
    $(LWIP_NETIF_PPP_SRC_FILES)

LOCAL_SRC_FILES := \
    $(LWIP_API_SRC_FILES) \
    $(LWIP_CORE_SRC_FILES) \
    $(LWIP_NETIF_SRC_FILES)

include $(BUILD_STATIC_LIBRARY)

############################################################
# Build LWIP JNI Wrapper
############################################################

include $(CLEAR_VARS)

LOCAL_MODULE := lwip-android-jni

LOCAL_SRC_FILES := jni/LWIPAndroidAPI.cpp \
    jni/LWIPAndroidNetBuf.cpp \
    jni/LWIPAndroidNetDB.cpp \
    jni/LWIPAndroidNetIFAPI.cpp \
    jni/LWIPAndroidSockets.cpp \
    jni/LWIPAndroidSys.cpp

LOCAL_STATIC_LIBRARIES := lwip-android

include $(BUILD_SHARED_LIBRARY)
