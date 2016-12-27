import java.util.ArrayList;

/**
 * Created by Yura on 22.05.2016.
 */
public class Generate {
    private ArrayList<Vertex> vertexes;
    private ArrayList<Edge> edges;
    private Vertex a;
    private Vertex f;
    public ArrayList<Vertex> getVertexes(){
        return vertexes;
    }
    public ArrayList<Edge> getEdges(){return edges;}
    public Vertex getStart(){return a;}
    public Vertex getEnd(){return f;}
    public Generate(){
        vertexes=new ArrayList<>();
        edges = new ArrayList<>();
        a = new Vertex("a");
        Vertex b = new Vertex("b");
        Vertex c = new Vertex("c");
        Vertex d = new Vertex("d");
        Vertex e = new Vertex("e");
        f = new Vertex("f");
        Edge ab = new Edge(b,4,"ab");
        Edge ae = new Edge(e,3,"ae");
        Edge ac = new Edge(c,2,"ac");
        Edge bc = new Edge(c,2,"bc");
        Edge cb = new Edge(b,2,"cb");
        Edge bd = new Edge(d,2,"bd");
        Edge db = new Edge(b,2,"db");
        Edge be = new Edge(e,1,"be");
        Edge eb = new Edge(b,1,"eb");
        Edge de = new Edge(e,5,"de");
        Edge ed = new Edge(d,5,"ed");
        Edge df = new Edge(f,3,"df");
        Edge ef = new Edge(f,6,"ef");
        Edge ce = new Edge(e,5,"ce");
        Edge ec = new Edge(c,5,"ec");
        a.addEdge(ab);
        a.addEdge(ae);
        a.addEdge(ac);
        b.addEdge(bc);
        b.addEdge(bd);
        b.addEdge(be);
        c.addEdge(ce);
        c.addEdge(cb);
        d.addEdge(de);
        d.addEdge(df);
        d.addEdge(db);
        e.addEdge(eb);
        e.addEdge(ed);
        e.addEdge(ef);
        e.addEdge(ec);
        edges.add(ab);
        edges.add(ae);
        edges.add(ac);
        edges.add(bc);
        edges.add(bd);
        edges.add(be);
        edges.add(ce);
        edges.add(cb);
        edges.add(de);
        edges.add(df);
        edges.add(db);
        edges.add(eb);
        edges.add(ed);
        edges.add(ef);
        edges.add(ec);
        vertexes.add(a);
        vertexes.add(b);
        vertexes.add(c);
        vertexes.add(d);
        vertexes.add(e);
        vertexes.add(f);
    }
}
