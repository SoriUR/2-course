import javax.swing.*;
import java.awt.*;

public class Frame extends JFrame {
    public ButPanel getBP(){
        return panel2;
    }

    public DrPanel getDr(){
        return panel1;
    }
    DrPanel panel1;
    ButPanel panel2;

    public Frame() {
        JFrame f = new JFrame("Lab4");

        f.setSize(1400, 900);
        f.setLocationRelativeTo(null);
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.setResizable(false);
        f.setLayout(new BorderLayout());
        panel1 = new DrPanel(panel2);
        panel2 = new ButPanel(panel1);
        panel1.setSize(100,100);
        f.add(panel1,BorderLayout.CENTER);
        f.add(panel2,BorderLayout.PAGE_END);
        f.setVisible(true);
        return;
    }
}