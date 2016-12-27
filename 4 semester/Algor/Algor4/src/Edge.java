/**
 * Created by Yura on 22.05.2016.
 */
public class Edge {
    private Vertex destination;
    private int length;
    private int stream;
    private String name;
    private Vertex streamDest;
    public Edge(Vertex dest, int len,String n){
        destination=dest;
        length=len;
        stream=0;
        name=n;
    }
    public String getName(){return name;}
    public int getStream(){return stream;}
    public void setStream(int stream){this.stream=stream;}
    public int getLength(){
        return length;
    }
    public Vertex getDest(){
        return destination;
    }
    public Vertex getStreamDest(){return streamDest;}
    public void setStreamDest(Vertex sd){streamDest=sd;}
    public boolean isEnable(){
        if(streamDest==null) return true;
        if((destination.equals(streamDest))&(stream<length)) return true;
        if((!destination.equals(streamDest))&(stream>0)) return true;
        return false;
    }
}
