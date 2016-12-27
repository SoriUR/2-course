import java.lang.*;
class Kontur
{
    float R;
    boolean circ;
    boolean rect;
    boolean trian;
    public Kontur(float a)
    {
        R=a;
    }
    public boolean Check(Tochka t)
    {
        double x = t.getx();
        double y = t.gety();
        circ=(x<0) && (y>0) && (Math.pow(x,2)+Math.pow(y,2)<Math.pow(R/2,2));
        rect=(x<0) && (x>-R) && (y<0) && (t.y>-R);
        trian=(x>0) && (y>0) && (x<R/2) && (y<R/2) && (x+y<R/2);
        if(circ || rect || trian) return true;
        return false;
    }
}
