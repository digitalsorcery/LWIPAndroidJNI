package com.digitalsorcery.jni.lwip;

import com.digitalsorcery.jni.lwip.NetIF;
import java.net.InetAddress;

public class NetIFAPI {
    /**
     * Name:        addInterface
     *
     * Description: Adds a network interface to the stack.
     *
     * Returns:     On success, zero is returned. On error, a negative number is returned as defined in
     *              com.digitalsorcery.jni.lwip.Errors.
     */
    public static native int addInterface (NetIF netif, InetAddress ipaddr, InetAddress netmask, InetAddress gw);

    /**
     * Name:        setInterfaceAddress
     *
     * Description: Sets addresses for a network interface.
     *
     * Returns:     On success, zero is returned. On error, a negative number is returned as defined in
     *              com.digitalsorcery.jni.lwip.Errors.
     */
    public static native int setInterfaceAddress (NetIF netif, InetAddress ipaddr, InetAddress netmask, InetAddress gw);

    /**
     * Name:        removeInterface
     *
     * Description: Removes a network interface from the stack.
     *
     * Returns:     On success, zero is returned. On error, a negative number is returned as defined in
     *              com.digitalsorcery.jni.lwip.Errors.
     */
    public static native int removeInterface (NetIF netif);

    /**
     * Name:        setInterfaceUp
     *
     * Description:
     *
     * Returns:     On success, zero is returned. On error, a negative number is returned as defined in
     *              com.digitalsorcery.jni.lwip.Errors.
     */
    public static native int setInterfaceUp (NetIF netif);

    /**
     * Name:        setInterfaceDown
     *
     * Description:
     *
     * Returns:     On success, zero is returned. On error, a negative number is returned as defined in
     *              com.digitalsorcery.jni.lwip.Errors.
     */
    public static native int setInterfaceDown (NetIF netif);

    /**
     * Name:        setInterfaceDefault
     *
     * Description:
     *
     * Returns:     On success, zero is returned. On error, a negative number is returned as defined in
     *              com.digitalsorcery.jni.lwip.Errors.
     */
    public static native int setInterfaceDefault (NetIF netif);

    /**
     * Name:        dhcpStart
     *
     * Description:
     *
     * Returns:     On success, zero is returned. On error, a negative number is returned as defined in
     *              com.digitalsorcery.jni.lwip.Errors.
     */
    public static native int dhcpStart (NetIF netif);

    /**
     * Name:        dhcpStop
     *
     * Description:
     *
     * Returns:     On success, zero is returned. On error, a negative number is returned as defined in
     *              com.digitalsorcery.jni.lwip.Errors.
     */
    public static native int dhcpStop (NetIF netif);

    /**
     * Name:        autoIPStart
     *
     * Description:
     *
     * Returns:     On success, zero is returned. On error, a negative number is returned as defined in
     *              com.digitalsorcery.jni.lwip.Errors.
     */
    public static native int autoIPStart (NetIF netif);

    /**
     * Name:        autoIPStop
     *
     * Description:
     *
     * Returns:     On success, zero is returned. On error, a negative number is returned as defined in
     *              com.digitalsorcery.jni.lwip.Errors.
     */
    public static native int autoIPStop (NetIF netif);

    static {
        System.loadLibrary ("lwip-android-jni");
    }
}
