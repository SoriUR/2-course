import javax.swing.*;
import java.awt.*;
import java.lang.*;

public class Point extends JComponent{
    static double R=DrPanel.Rconst;
    int radius=10;
    public double x;
    public double y;
    Color color;
    JLabel label;
    boolean belong;
    boolean last;
    boolean anim=false;
    //Spy sp = new Spy();
    public Point(int x, int y,JLabel label) {
        this.x = x;
        this.y = y;
        this.label = label;
        Belong();
    }


    public void Belong() {
        last = belong;
        belong = Check();
        if (belong) {
            anim = false;
            radius = 10;
            color = Color.GREEN;

        } else {
            if (last) {
                anim = true;
                radius=DrPanel.Rconst/8;
            }

            color = Color.RED;

        }
        label.setForeground(color);
    }

    boolean circ;
    boolean rect;
    boolean trian;

    public void recalc(){
        x=((x-DrPanel.width/2)*DrPanel.kf)+DrPanel.width/2;
        y=((y-DrPanel.height/2)*DrPanel.kf)+DrPanel.height/2;
        label.setBounds((int)x - 40, (int)y - 23, 80, 20);
    }

    public boolean Check()
    {
        double x= this.x - DrPanel.width/2;
        double y= DrPanel.height/2-this.y;
        circ=(x<0) && (y>0) && (Math.pow(x,2)+Math.pow(y,2)<Math.pow(R/2,2));
        rect=(x<0) && (x>-R) && (y<0) && (y>-R);
        trian=(x>0) && (y>0) && (x<R/2) && (y<R/2) && (x+y<R/2);
        if(circ || rect || trian) return true;
        return false;
    }
}

