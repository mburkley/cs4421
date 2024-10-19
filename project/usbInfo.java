/*
 *  USB information class for JNI
 *
 *  Copyright (c) 2024 Mark Burkley (mark.burkley@ul.ie)
 */

public class usbInfo 
{
    // Refresh the current values and counters - call this before other methods
    public native void read ();

    // Return the number of USB buses
    public native int busCount ();

    // Return the number of devices on a USB bus
    public native int deviceCount (int bus);

    // Return the vendor ID of a USB device
    public native int vendorID (int bus, int device);

    // Return the product ID of a USB device
    public native int productID (int bus, int device);
}

