import java.util.ArrayList;

/**
 * Created by Yura on 10.04.2016.
 */
public class Main {
     public static void main(String args[]){
         int m=0;
         Generate g1,g2;
         ArrayList<Long> dt = new ArrayList<>();
         ArrayList<Long> ft = new ArrayList<>();
         while(m!=10000000) {
             m+=100000;
             long time = System.currentTimeMillis();
             g1 = new Generate(time, m);
             g2 = g1;
             long dtime=new Dijkstra(g1.getVertexes(), 4).getTime();
             long fbtime=new FB(g2.getVertexes(), 4,g2.getEdges()).getTime();
             dt.add(dtime);
             ft.add(fbtime);
        }
         for(Long l:dt){
             System.out.println(l);
         }
         System.out.println("----------------------------------");
         for(Long l:ft){
             System.out.println(l);
         }
    }
}
