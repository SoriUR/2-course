import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.lang.*;
import java.util.HashSet;

public class DrPanel extends JPanel {
    static int Rconst = 200;
    public static int num=0;
    public static double R = Rconst;
    static int radius = 10;
    public static int width;
    public static int height;
    static double kf=1;
    static double del=1;
    public static Graphics gr;
    public static boolean Tim=false;
    public HashSet<Point> Mpoints = new HashSet<>();
    public static ButPanel bp;
    public DrPanel(ButPanel bp) {
        this.bp=bp;
        this.setBackground(Color.getHSBColor(62, 72, 100));
            this.addMouseListener(new MouseAdapter() {
                @Override
                public void mouseClicked(MouseEvent e) {
                   super.mouseClicked(e);
                   addPoint(e.getX(), e.getY());
                }
            });
        }

    void addPoint(int x, int y) {
        JLabel label = new JLabel("{" +Double.valueOf(Math.round((x-width/2)/del)).toString()+";"+Double.valueOf(Math.round(((height/2-y)/del))).toString()+"}");
        Point p = new Point(x, y, label);
        if(p.belong)num++;
        if(!Mpoints.contains(p)) {
            Mpoints.add(p);
            add(label);
            this.repaint();
        }
    }


    public void setRadius(int a) {
        kf = R/a;
        del = Rconst/a;
        R = a;
        num=0;
        for(Point p: Mpoints){
            p.recalc();
            p.Belong();
            if(p.belong)num++;
        }
        Tim = true;
    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        gr = g;
        width = getWidth();
        height = getHeight();
        DrawLines(g);
        DrawGraph(g);
        for (Point point : Mpoints) {
            point.repaint();
            new Thread(new Animation(point,g,this)).start();
            point.Belong();
            if (point.anim) {
                if (point.radius > radius) {
                    point.radius -= 1;
                    try {
                        Thread.sleep(10);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
            g.setColor(point.color);
            point.label.setBounds((int) point.x - 40, (int) point.y - 23-point.radius, 80, 20);
            g.fillOval((int) point.x - point.radius / 2, (int) point.y - point.radius / 2, point.radius, point.radius);
            }

    }

    void DrawLines(Graphics g){
        g.setColor(Color.BLACK);
        gr.drawLine(0, height / 2, width, height / 2);
        gr.drawLine(width / 2, 0, width / 2, height);
    }
    void DrawGraph(Graphics g){
        g.setColor(Color.BLUE);
        g.fillRect(width / 2 - Rconst, height / 2, Rconst, Rconst);
        g.fillPolygon(xPoints(), yPoints(), 3);
        g.fillArc(width / 2 - Rconst / 2, height / 2 - Rconst / 2, Rconst, Rconst, 90, 90);
    }

    int[] xPoints(){
        int mas[]={width/2,width/2+Rconst/2,width/2};
        return mas;
    }
    int[] yPoints(){
        int mas[]={height/2,height/2,height/2-Rconst/2};
        return mas;
    }

    public class Animation implements Runnable {
        Point point;
        DrPanel dr;
        Graphics g;
        public Animation(Point p,Graphics g,DrPanel dr){
            point=p;
            this.g = g;
            this.dr= dr;
        }

        public void run(){
            dr.repaint();

        }

    }
}
