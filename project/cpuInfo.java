public class cpuInfo 
{
    // Refresh the current values and counters - call this before other methods
    public native void read ();

    // Return the number of cores per CPU socket
    public native int coresPerSocket ();

    // Return the number of CPUs in this computer
    public native int socketCount ();

    // Return the model number of the CPU
    public native String getModel ();

    // Return the size in bytes of the L1 data cache
    public native int l1dCacheSize ();

    // Return the size in bytes of the L1 instruction cache
    public native int l1iCacheSize ();

    // Return the size in bytes of the L2 cache
    public native int l2CacheSize ();

    // Return the size in bytes of the L3 cache
    public native int l3CacheSize ();

    // Return the time in "jiffies" or 1/100ths of a second 
    // that the specified core has been in user mode
    public native int getUserTime (int core);

    // Return the time in "jiffies" or 1/100ths of a second 
    // that the specified core has been idle
    public native int getIdleTime (int core);

    // Return the time in "jiffies" or 1/100ths of a second 
    // that the specified core has been in system mode
    public native int getSystemTime (int core);
}
