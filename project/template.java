public class template 
{
    public static void pcimain(String[] args)
    {
        System.loadLibrary("sysinfo");
        sysInfo info = new sysInfo();

        pciInfo pci = new pciInfo();
        pci.read();
        System.out.println("This machine has "+
            pci.busCount()+" PCI buses ");
        for (int i = 0; i < pci.busCount(); i++) {
            System.out.println("Bus "+i+" has "+
                pci.deviceCount(i)+" devices");
            for (int j = 0; j < 32; j++) {
                if (pci.functionCount (i, j) > 0) {
                    System.out.println("Bus "+i+" device "+j+" has "+
                        pci.functionCount(i, j)+" functions");
                    for (int k = 0; k < 8; k++) {
                        if (pci.functionPresent (i, j, k) > 0) {
                            System.out.println("Bus "+i+" device "+j+" function "+k+
                                " has vendor "+String.format("0x%04X", pci.vendorID(i,j,k))+
                                " and product "+String.format("0x%04X", pci.productID(i,j,k)));
                        }
                    }
                }
            }
        }
    }

    public static void main(String[] args) {
        System.loadLibrary("sysinfo");
        sysInfo info = new sysInfo();

        usbInfo usb = new usbInfo();
        usb.read();
        System.out.println("This machine has "+
            usb.busCount()+" USB buses ");
        for (int i = 1; i <= usb.busCount(); i++) {
            System.out.println("Bus "+i+" has "+
                usb.deviceCount(i)+" devices");
            for (int j = 1; j <= usb.deviceCount(i); j++) {
                System.out.println("Bus "+i+" device "+j+
                    " has vendor "+String.format("0x%04X", usb.vendorID(i,j))+
                    " and product "+String.format("0x%04X", usb.productID(i,j)));
            }
        }
    }

    public static void oldmain(String[] args)
    {
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
