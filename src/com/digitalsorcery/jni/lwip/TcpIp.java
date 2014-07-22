package com.digitalsorcery.jni.lwip;

public class TcpIp {
    /**
     * Name:        initializeTcpIp
     *
     * Description: Initializes the TCP/IP interface.
     *
     * Returns:     None.
     */
    public static native void initializeTcpIp ();

    static {
        System.loadLibrary ("lwip-android-jni");
    }
}
