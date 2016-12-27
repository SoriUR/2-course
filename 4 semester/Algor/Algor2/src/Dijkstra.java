import java.util.ArrayList;
/**
 * Created by Yura on 11.04.2016.
 */
public class Dijkstra {
    long timeout=0;

    public Dijkstra(ArrayList<Vertex> vertexes,int startVertex) {
        timeout=System.currentTimeMillis();
        Vertex start = vertexes.get(startVertex);
        start.setWay(0);
        Heapp heap = new Heapp(vertexes, start);
        while(start!=null) {
            initiate(start, heap);
            start = heap.getRoot();
        }
        timeout = System.currentTimeMillis() - timeout;
    }

    private void initiate(Vertex start,Heapp heap){
        heap.Delete(start);
        for(Edge edge:start.getEdges()){
            if((start.getWay()+edge.getLength()) < edge.getDest().getWay()) {
                edge.getDest().setWay(start.getWay() + edge.getLength());
                heap.setWay(edge.getDest(), edge.getDest().getWay());
            }
        }
    }

    public long getTime(){
        return timeout;
    }
}
