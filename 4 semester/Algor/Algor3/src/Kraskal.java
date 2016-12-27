import java.util.ArrayList;
import java.util.Comparator;
import java.util.PriorityQueue;

/**
 * Created by Yura on 14.05.2016.
 */
public class Kraskal {
    private ArrayList<Edge> edges;
    private int size;
    private long timeout;
    public Kraskal(ArrayList<Vertex> vertexes,ArrayList<Edge> edg){
        edges=new ArrayList<>();
        size=vertexes.size();
        for(Vertex vertex:vertexes){
            new Component(vertex);
        }
        timeout=System.currentTimeMillis();
        PriorityQueue<Edge> pq = new PriorityQueue<>(new Comparator(){
            @Override
            public int compare(Object o1, Object o2) {
                Edge e1 = (Edge) o1;
                Edge e2 = (Edge) o2;
                if(e1.getLength()<e2.getLength()) return -1;
                if(e1.getLength()==e2.getLength()) return 0;
                return 1;
            }
        });
        pq.addAll(edg);

        while(size!=1){
            Edge edge = pq.poll();
            if(!edge.getStart().getComponent().equals(edge.getDest().getComponent())) {
                edge.getStart().getComponent().mergeComp(edge.getDest().getComponent());
                size--;
            }
            edg.remove(edge);
        }
        timeout=System.currentTimeMillis()-timeout;
    }
    public long getTime(){
        return timeout;
    }
}
