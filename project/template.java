public class template 
{
     public static void main(String[] args)
     {
          System.loadLibrary("sysinfo");
          sysInfo info = new sysInfo();
          int     square = info.intExample(5);
          System.out.println("intExample: " + square);
          String     str = info.stringExample("test");
          System.out.println("stringExample: " + str);

          cpuInfo cpu = new cpuInfo();
          cpu.read();

          System.out.println("CPU " + cpu.getModel() + " has "+
              cpu.socketCount() + " sockets each with "+
              cpu.coresPerSocket() + " cores");
          System.out.println("l1d="+cpu.l1dCacheSize()+
              "l1i="+cpu.l1iCacheSize()+
              "l2="+cpu.l2CacheSize()+
              "l3="+cpu.l3CacheSize());

     }
}
