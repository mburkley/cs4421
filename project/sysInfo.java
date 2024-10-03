
public class sysInfo 
{
     public native int intMethod(int n);
     public native String stringMethod(String s);
     public static void main(String[] args)
     {
          System.loadLibrary("sysinfo");
          sysInfo info = new sysInfo();
          int     square = info.intMethod(5);
          System.out.println("intMethod: " + square);
          String     str = info.stringMethod("test");
          System.out.println("stringMethod: " + str);
     }
}
