package com.digitalsorcery.jni.lwip;

import com.digitalsorcery.jni.lwip.Errors;

public class NetIF {
    protected long objectHandle = 0L;
    public void _setObjectHandle (long handle) {
        objectHandle = handle;
    }
    public long _getObjectHandle () {
        return objectHandle;
    }

    // This method *MUST* be overwritten.
    // Called when the network interface is initialized.
    public int initInterface () {
        return Errors.ERR_UNIMPL;
    }

    // This method *MUST* be overwritten.
    // Called when a new packet is received.
    public int readData (byte[] buffer) {
        return Errors.ERR_UNIMPL;
    }
}
