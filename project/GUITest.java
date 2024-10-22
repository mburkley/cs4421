import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class GUITest extends JFrame implements ActionListener {


    // Declare JButton at class level
    JButton cpuButton;
    JTextArea cpuText;

    // Constructor for GUITest
    GUITest() {
        // Initialize the JButton
        cpuButton = new JButton("CPU");
        cpuButton.setBounds(0, 0, 100, 50);
        cpuButton.addActionListener(this); // Attach ActionListener to the button
        cpuButton.setFocusable(false);//removes the box that appears initially around the writing on the button
        cpuButton.setBackground(new Color(64, 224, 208));
        cpuButton.setFont(new Font("Comic Sans", Font.BOLD, 25));

        cpuText = new JTextArea();
        cpuText.setBounds(50, 100, 250, 250);
        cpuText.setEditable(false);
        cpuText.setFont(new Font("Comic Sans", Font.BOLD, 15));
        cpuText.setBackground(Color.white);

        // Create JFrame (this frame itself since GUITest extends JFrame)
        this.setTitle("Joint Assignment"); // Sets the title to Joint Assignment
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // Allows the window to close properly
        this.setResizable(false); // Makes the window non-resizable
        this.setSize(500, 500); // Set the frame size
        this.setVisible(true); // Make the frame visible

        // Set background color
        this.getContentPane().setBackground(Color.DARK_GRAY);

        // Set layout manager to null for absolute positioning
        this.setLayout(null);

        // Add components to the frame
        this.add(cpuButton);
        this.add(cpuText);
    }

    // Override actionPerformed to handle button clicks
    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == cpuButton) {
            try {
                System.loadLibrary("sysInfo");

                cpuInfo cpu = new cpuInfo();
                cpu.read(0);

                StringBuilder info = new StringBuilder();
                info.append("CPU Model: ").append(cpu.getModel()).append("\n");
                info.append("Sockets: ").append(cpu.socketCount()).append("\n");
                info.append("Cores per Socket: ").append(cpu.coresPerSocket()).append("\n");
                info.append("L1 Cache: Data=").append(cpu.l1dCacheSize()).append(" KB, Instruction=").append(cpu.l1iCacheSize()).append(" KB\n");
                info.append("L2 Cache: ").append(cpu.l2CacheSize()).append(" KB\n");
                info.append("L3 Cache: ").append(cpu.l3CacheSize()).append(" KB\n");

                cpu.read(1);
                info.append("Core 1 Idle Time: ").append(cpu.getIdleTime(1)).append("%\n");

                // Update the JTextArea with the CPU information
                cpuText.setText(info.toString());
            } catch (Exception ex) {
                cpuText.setText("Error retrieving CPU info: " + ex.getMessage());
            }
        }
    }
        // Main method to launch the application
        public static void main(String[]args){
            // Create an instance of GUITest to run the program
            new GUITest();
        }
}


