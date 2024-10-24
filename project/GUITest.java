import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class GUITest extends JFrame implements ActionListener {

    // Declare JButton and JTextArea at class level
    JButton cpuButton;
    JTextArea cpuText;
    JButton usbButton;
    JButton pciButton;

    GUITest() {
    // Constructor for GUITest

        // Initialize the JButton

        cpuText = new JTextArea();
        cpuText.setBounds(100, 0, 400, 500);
        cpuText.setEditable(false);
        cpuText.setFont(new Font("Comic Sans", Font.BOLD, 15));
        cpuText.setBackground(Color.white);

        cpuButton = new JButton("CPU");
        cpuButton.setBounds(0, 0, 100, 100);
        cpuButton.addActionListener(this); // Attach ActionListener to the button
        cpuButton.setFocusable(false); // Removes the box that appears initially around the writing on the button
        cpuButton.setBackground(new Color(64, 224, 208));
        cpuButton.setFont(new Font("Comic Sans", Font.BOLD, 25));

        usbButton = new JButton("USB");
        usbButton.setBounds(0, 100, 100, 100);
        usbButton.addActionListener(this);
        usbButton.setFocusable(false);
        usbButton.setBackground(new Color(64, 224, 208));
        usbButton.setFont(new Font("Comic Sans", Font.BOLD, 25));

        pciButton = new JButton("PCI");
        pciButton.setBounds(0,200,100,100);
        pciButton.addActionListener(this);
        pciButton.setFocusable(false);
        pciButton.setBackground(new Color(64,224,208));
        pciButton.setFont(new Font("Comic Sans", Font.BOLD, 25));

        // Set up the JFrame
        this.setTitle("Joint Assignment"); // Set the title
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // Close on exit
        this.setResizable(false);
        this.setSize(500, 500); // Set the frame size
        this.setVisible(true); // Make the frame visible

        // Set background color
        this.getContentPane().setBackground(Color.DARK_GRAY);

        this.setLayout(null);

        // Add components to the frame
        this.add(cpuButton);
        this.add(cpuText);
        this.add(usbButton);
        this.add(pciButton);
    }

    // Override actionPerformed to handle button clicks
    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == cpuButton) {
            try {

            System.loadLibrary("sysInfo");




                cpuInfo cpu = new cpuInfo();
                cpu.read(0);

                // Prepare the CPU info for display
                StringBuilder info = new StringBuilder();
                info.append("CPU Model: ").append(cpu.getModel()).append("\n");
                info.append("Sockets: ").append(cpu.socketCount()).append("\n");
                info.append("Cores per Socket: ").append(cpu.coresPerSocket()).append("\n");
                info.append("L1 Cache: Data=").append(cpu.l1dCacheSize()).append(" KB, Instruction=").append(cpu.l1iCacheSize()).append(" KB\n");
                info.append("L2 Cache: ").append(cpu.l2CacheSize()).append(" KB\n");
                info.append("L3 Cache: ").append(cpu.l3CacheSize()).append(" KB\n");

                // Additional CPU reading for core 1
                cpu.read(1);
                info.append("Core 1 Idle Time: ").append(cpu.getIdleTime(1)).append("%\n");

                // Update the JTextArea with the CPU information
                cpuText.setText(info.toString());
            } catch (Exception ex) {
                // Correct the error handling and string formatting
                cpuText.setText("Error retrieving CPU info: " + ex.getMessage());
            }
        }
    }

    // Main method to launch the application
    public static void main(String[] args) {
        System.out.println("hi");
        new GUITest();


    }
}

