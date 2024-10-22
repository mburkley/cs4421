import javax.swing.*;
import java.awt.*;

public class GuiTemplate {
    public static void main(String[]args) {
        JFrame frame = new JFrame(); //Creates an instance of a frame
        frame.setTitle("Joint Assignment"); //sets the title to Joint assignment
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); //allows it to be closed using the x
        frame.setResizable(false); //makes it so that the window cannot be put into fullscreen
        frame.setSize(500, 500); //makes a 500x500 frame
        frame.setVisible(true); // makes the frame visible

        frame.getContentPane().setBackground(Color.DARK_GRAY); //sets background colour to dark grey

        frame.setLayout(null);

    }
}
