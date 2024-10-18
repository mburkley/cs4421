public class template 
{
    public static void main(String[] args)
    {
        System.loadLibrary("sysinfo");
        sysInfo info = new sysInfo();

        cpuInfo cpu = new cpuInfo();
        cpu.read(0);

        System.out.println("CPU " + cpu.getModel() + " has "+
        cpu.socketCount() + " sockets each with "+
        cpu.coresPerSocket() + " cores");
        System.out.println("l1d="+cpu.l1dCacheSize()+
        ", l1i="+cpu.l1iCacheSize()+
        ", l2="+cpu.l2CacheSize()+
        ", l3="+cpu.l3CacheSize());


        while(true)
        {
            cpu.read(1);
            System.out.println("core 3 idle="+cpu.getIdleTime(3)+"%");
        }
    }
}
