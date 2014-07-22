package com.digitalsorcery.jni.lwip;

public class Errors {
    static public int ERR_OK = 0;           // No error, everything OK
    static public int ERR_MEM = -1;         // Out of memory error
    static public int ERR_BUF = -2;         // Buffer error
    static public int ERR_TIMEOUT = -3;     // Timeout
    static public int ERR_RTE = -4;         // Routing problem
    static public int ERR_INPROGRESS = -5;  // Operation in progress
    static public int ERR_VAL = -6;         // Illegal value
    static public int ERR_WOULDBLOCK = -7;  // Operation would block
    static public int ERR_USE = -8;         // Address in use
    static public int ERR_ISCONN = -9;      // Already connected
    static public int ERR_ABRT = -10;       // Connection aborted
    static public int ERR_RST = -11;        // Connection reset
    static public int ERR_CLSD = -12;       // Connection closed
    static public int ERR_CONN = -13;       // Not connected
    static public int ERR_ARG = -14;        // Illegal argument
    static public int ERR_IF = -15;         // Low-level netif error
    static public int ERR_UNIMPL = -127;    // Unimplemented

    static public boolean isFatal (int err) {
        return ((err) < ERR_ISCONN) ? true : false;
    }
}
