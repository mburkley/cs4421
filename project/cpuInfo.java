public class cpuInfo 
{
     public native void read ();
     public native int coresPerSocket ();
     public native int socketCount ();
     public native String getModel ();
     public native int l1dCacheSize ();
     public native int l1iCacheSize ();
     public native int l2CacheSize ();
     public native int l3CacheSize ();
}
