import java.util.ArrayList;

/**
 * Created by Yura on 09.04.2016.
 */
public class Vertex {
    public Vertex(){
        edges = new ArrayList<>();
    }
    private Component component;
    private ArrayList<Edge> edges;
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
    public void setComponent(Component component){this.component=component;}
    public Component getComponent(){return component;}
}
