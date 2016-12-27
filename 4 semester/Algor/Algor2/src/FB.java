import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

/**
 * Created by Yura on 22.04.2016.
 */
public class FB {
    long timeout=0;
    private Map<Vertex,Integer> d;
    int max=10000000;
    public FB(ArrayList<Vertex> vertexes,int startVertex,ArrayList<Edge> edges){
        timeout=System.currentTimeMillis();
        d=new HashMap<Vertex,Integer>();
        for(Vertex vertex:vertexes){
            d.put(vertex,max);
        }
        d.replace(vertexes.get(startVertex),0);
        boolean ifchange= true;
        for(int i=0;i<d.size()-1;i++){
            if(!ifchange) break;
            ifchange = false;
            for(Edge edge:edges){
                if(d.get(edge.getDest())>(d.get(edge.getStart())+edge.getLength())){
                    d.replace(edge.getDest(),d.get(edge.getStart())+edge.getLength());
                    ifchange=true;
                }
            }
        }
        timeout = System.currentTimeMillis() - timeout;
    }

    public long getTime(){
        return timeout;
    }
}
