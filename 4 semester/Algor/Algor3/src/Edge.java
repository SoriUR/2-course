/**
 * Created by Yura on 09.04.2016.
 */
public class Edge {
    private Vertex destination;
    private Vertex start;
    private int length;
    public Edge(Vertex st,Vertex dest, int len){
        start=st;
        destination=dest;
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
