import java.util.ArrayList;

/**
 * Created by Yura on 22.05.2016.
 */
public class Vertex {
    private String name;
    public Vertex(String n){
        edges = new ArrayList<>();
        name=n;
    }
    private ArrayList<Edge> edges;
    public ArrayList<Edge> getEdges(){
        return edges;
    }
    public void addEdge(Edge edge){
        edges.add(edge);
    }
}
