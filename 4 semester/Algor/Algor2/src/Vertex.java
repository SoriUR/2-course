import java.util.ArrayList;

/**
 * Created by Yura on 09.04.2016.
 */
public class Vertex {
    public Vertex(){
        edges= new ArrayList<>();
        way = 10000000;
    }
    private int way;
    private ArrayList<Edge> edges;

    public int getWay(){
        return way;
    }
    public void setWay(int way){
        this.way=way;
    }
    public ArrayList<Edge> getEdges(){
        return edges;
    }
    public void addEdge(Edge edge){
        edges.add(edge);
    }

    public boolean isConnected(Vertex vertex){
        if(edges.contains(vertex)) return true;
        if(vertex.getEdges().contains(this)) return true;
        return false;
    }
}
