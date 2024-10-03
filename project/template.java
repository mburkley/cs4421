// package cs4421;

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
          System.out.println("CPU " + cpu.getModel() + " has "+
              cpu.coreCount() + " cores");
     }
}
