import java.util.ArrayList;
import java.util.Random;
/**
 * Created by Yura on 09.04.2016.
 */
public class Generate {
    private Random random;
    private int n =10000+1;
    private int m;
    private int q=1;
    private int r=1000000;
    ArrayList<Vertex> vertexes;
    ArrayList<Edge> edges;
    public Generate(long gen, int ms){
        m=ms;
        random = new Random(gen);
        vertexes=new ArrayList<>(n);
        edges=new ArrayList<>(m);
        for(int i=0;i<n;i++){
            vertexes.add(new Vertex());
        }
        int k=0;
        int len;
        int first;
        int second;
        while(k<m){
            first=random.nextInt(n);
            second=random.nextInt(n);
            if(first!=second)
                if(!vertexes.get(first).isConnected(vertexes.get(second))){
                    len=random.nextInt(r) + q;
                    k++;
                    Edge e = new Edge(vertexes.get(first),vertexes.get(second),len);
                    vertexes.get(first).addEdge(e);
                    edges.add(e);
                }
        }
    }
    public ArrayList<Vertex> getVertexes(){
        return  vertexes;
    }
    public ArrayList<Edge> getEdges(){return edges;}
}
