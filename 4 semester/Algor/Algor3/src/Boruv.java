import java.util.ArrayList;

/**
 * Created by Yura on 30.04.2016.
 */
public class Boruv {
    private ArrayList<Component> spisok;
    private long timeout;
    public Boruv(ArrayList<Vertex> vertexes) {
        timeout = System.currentTimeMillis();
        spisok = new ArrayList<>();
        for (Vertex vertex : vertexes) {
            Component c = new Component(vertex);
            spisok.add(c);
        }
        while (spisok.size()!=1) {
            for (Component c : spisok)
                c.findEdge();
            int iter = 0;
            while (iter < spisok.size()) {
                Component c = spisok.get(iter);
                if (!c.getEdge().getStart().getComponent().equals(c.getEdge().getDest().getComponent())) {
                    c.getEdge().getDest().getComponent().mergeComp(c);
                    spisok.remove(c);
                } else {
                    iter++;
                }
            }
        }
        timeout = System.currentTimeMillis()-timeout;
    }
    public long getTime(){
        return timeout;
    }
}

