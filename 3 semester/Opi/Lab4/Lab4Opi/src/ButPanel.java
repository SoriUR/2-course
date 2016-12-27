import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ButPanel extends JPanel {
    JButton addB;
    JList list;
    public JSpinner spin;
    boolean fl=false;
    final DefaultListModel model = new DefaultListModel();
    public DrPanel a;
    int yValue =0;
    public ButPanel(DrPanel a){

        this.a=a;
        this.setLayout(new GridLayout());

        model.addElement(-170);
        model.addElement(30);
        model.addElement(230);
        spin = new JSpinner();
        spin.setValue(200);
        spin.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
               // System.out.println("pan");
                //a.setRadius((int)spin.getValue());
                //a.repaint();
            }
        });
        JLabel yl = new JLabel("Choose Y:");
            yl.setHorizontalAlignment(SwingConstants.CENTER);
        JLabel xl = new JLabel("Choose X:");
            xl.setHorizontalAlignment(SwingConstants.CENTER);
        JLabel rl = new JLabel("Set R:");
            rl.setHorizontalAlignment(SwingConstants.CENTER);
        JLabel el = new JLabel();
            el.setHorizontalAlignment(SwingConstants.CENTER);

        list = new JList(model);

        JCheckBox y1 = new JCheckBox("-250");
        JCheckBox y2 = new JCheckBox("-50");
        JCheckBox y3 = new JCheckBox("150");

        y1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(y1.isSelected()==true) {
                    yValue =DrPanel.height/2-Integer.parseInt(y1.getText());
                    y2.setSelected(false);
                    y3.setSelected(false);
                }
            }
        });
        y2.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(y2.isSelected()==true) {
                    yValue =DrPanel.height/2-Integer.parseInt(y2.getText());
                    y1.setSelected(false);
                    y3.setSelected(false);
                }
            }
        });
        y3.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(y3.isSelected()==true) {
                    yValue =DrPanel.height/2-Integer.valueOf(y3.getText());
                    y2.setSelected(false);
                    y1.setSelected(false);
                }
            }
        });


        addB = new JButton("Add point");
        addB.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                el.setText("");
                if((list.getSelectedValue()==null)||(!y1.isSelected() && !y2.isSelected() &&!y3.isSelected())) el.setText("Input error");
                else {
                a.addPoint(DrPanel.width/2+(int)list.getSelectedValue(),yValue);
                }
            }
        });

        add(xl);
        add(list);
        add(yl);
        add(y1);
        add(y2);
        add(y3);
        add(rl);
        add(spin);
        add(el);
        add(addB);
    }
}
