import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;



public class GUI implements ActionListener {
    public static void main(String[]args) {

        JButton cpuButton = new JButton("CPU");
        cpuButton.setBounds(0, 0, 100, 50);

        JFrame frame = new JFrame(); //Creates an instance of a frame
        frame.setTitle("Joint Assignment"); //sets the title to Joint assignment
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); //allows it to be closed using the x
        frame.setResizable(false); //makes it so that the window cannot be put into fullscreen
        frame.setSize(500, 500); //makes a 500x500 frame
        frame.setVisible(true); // makes the frame visible

        frame.getContentPane().setBackground(Color.DARK_GRAY); //sets background colour to dark grey

        frame.setLayout(null);

        frame.add(cpuButton);
    }

    @Override
    public void actionPerformed(ActionEvent e) {




    }
}


