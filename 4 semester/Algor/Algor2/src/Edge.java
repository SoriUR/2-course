/**
 * Created by Yura on 09.04.2016.
 */
public class Edge {
    private Vertex destination;
    private int length;
    private Vertex start;
    public Edge(Vertex vertex,int len,Vertex st){
        destination=vertex;
        start=st;
        length=len;
    }

    public int getLength(){
        return length;
    }
    public Vertex getDest(){
        return destination;
    }
    public Vertex getStart(){return start;}
}
