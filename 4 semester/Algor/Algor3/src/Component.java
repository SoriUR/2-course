import java.util.ArrayList;

/**
 * Created by Yura on 13.05.2016.
 */
public class Component {
    private ArrayList<Vertex> component;
    private Edge edge;
    public Component(Vertex vertex){
        component=new ArrayList<>();
        Add(vertex);
    }
    private void Add(Vertex vertex){
        component.add(vertex);
        vertex.setComponent(this);
    }
    public void findEdge(){
        Edge minEdge=new Edge(null,null,10000000);
        for(Vertex ver:component){
            for(Edge ed:ver.getEdges()){
                if(!ed.getDest().getComponent().equals(this))
                    if(ed.getLength()<minEdge.getLength()) minEdge=ed;
            }
        }
        edge=minEdge;
    }
    public Edge getEdge(){return edge;}
    public void mergeComp(Component comp){
        for (Vertex ver:comp.getComponent()){
            Add(ver);
        }
    }
    public ArrayList<Vertex> getComponent(){return component;}
}
