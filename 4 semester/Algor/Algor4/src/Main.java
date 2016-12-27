import java.awt.image.AreaAveragingScaleFilter;
import java.util.ArrayList;

/**
 * Created by Yura on 22.05.2016.
 */
public class Main {
    private static ArrayList<Vertex> vertexes;
    private static ArrayList<Edge> edges;
    private static Vertex start;
    private static Vertex end;
    public static void main(String aghs[]) {
        Generate gn = new Generate();
        vertexes = gn.getVertexes();
        start=gn.getStart();
        end=gn.getEnd();
        ArrayList<ArrayList<Edge>> chains=new ArrayList<>();
        while (true) {
            int min=10;
            ArrayList<Edge> chain = findChain();
            if(chain.size()==0) break;
            chains.add(chain);
            for(Edge e:chain){
                if (min > (e.getLength() - e.getStream())) min = e.getLength() - e.getStream();
            }
            for(Edge e:chain){
                if(e.getStreamDest()==null){
                    e.setStream(min);
                    e.setStreamDest(e.getDest());
                }
                else {
                    if (e.getDest().equals(e.getStreamDest()))
                        e.setStream(e.getStream() + min);
                    else e.setStream(e.getStream() - min);
                }
            }
        }
        for(ArrayList<Edge> cha:chains){
            for(Edge e:cha){
                System.out.printf(e.getName()+"|");
            }
            System.out.println();
        }
        for(Edge e:gn.getEdges()){
            System.out.println(e.getName()+":"+e.getLength()+"("+e.getStream()+")");
        }
        System.out.println("Максимальный поток построен");
        ArrayList<Vertex> v1 = new ArrayList<>();
        ArrayList<Vertex> v2 = new ArrayList<>();
        v1.add(start);
        int iter=0;
        while (true) {
            for (Edge e : v1.get(iter).getEdges()) {
                if (((e.getLength() - e.getStream()) != 0) & (!v1.contains(e.getDest()))) {
                    v1.add(e.getDest());
                }
            }
            iter++;
            if(iter>=v1.size()) break;
        }
        for(Vertex v:vertexes){
            if(!v1.contains(v)) v2.add(v);
        }
        int MaxStream=0;
        ArrayList<Edge> minCut = new ArrayList<>();
        for(Vertex v:v1){
            for(Edge e:v.getEdges()){
                if(v2.contains(e.getDest())) {
                    MaxStream += e.getLength();
                    minCut.add(e);
                }
            }
        }
        System.out.println("Минимальный разрез:"+MaxStream);
        for(Edge e:minCut){
            System.out.println(e.getName()+":"+e.getLength()+"("+e.getStream()+")");
        }
    }
    private static ArrayList<Edge> findChain(){
        ArrayList<Vertex> v = new ArrayList<>();
        ArrayList<Vertex> ban = new ArrayList<>();
        ArrayList<Edge> ed = new ArrayList<>();
        int iter=0;
        boolean flag;
        v.add(start);
        while (!v.get(iter).equals(end)) {
            flag=false;
            for (Edge e : v.get(iter).getEdges()) {
                if ((e.isEnable()) & (!v.contains(e.getDest())) & (!ban.contains(e.getDest()))) {
                    v.add(e.getDest());
                    ed.add(e);
                    iter++;
                    flag=true;
                    break;
                }
            }
            if(!flag) {
                ban.add(v.get(iter));
                v.remove(iter);
                if (v.size()==0) break;
                ed.remove(iter - 1);
                iter--;
            }
        }
        return ed;
    }
}