import java.util.ArrayList;

/**
 * Created by Yura on 25.04.2016.
 */
public class Main {
    public static void main(String args[]){
        int m=0;
        ArrayList<Long> kt= new ArrayList<>();
        ArrayList<Long> bt = new ArrayList<>();
        while(m!=10000000) {
            m+=100000;
            Generate g1, g2;
            long time = System.currentTimeMillis();
            g1 = new Generate(time, m);
            g2 = g1;
            long krasTime = new Kraskal(g2.getVertexes(),g2.getEdges()).getTime();
            long borTime = new Boruv(g1.getVertexes()).getTime();
            kt.add(krasTime);
            bt.add(borTime);
            System.out.println(m+":"+borTime+"|"+krasTime);
            if(m==2000000) {
                for (Long l : kt) {
                    System.out.println(l);
                }
                System.out.println("-------------------");
                for (Long l : bt) {
                    System.out.println(l);
                }
            }
        }
    }

}
