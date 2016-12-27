import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

/**
 * Created by Yura on 13.04.2016.
 */
public class Heapp {
    private int d = 5;
    private ArrayList<Integer> heap;
    private Map<Vertex,Integer> map;
    private Map<Integer,Vertex> kek;
    private int size=0;
    public Heapp(ArrayList<Vertex> vertexes,Vertex firstRoot){
        heap=new ArrayList<>();
        map=new HashMap<>();
        kek=new HashMap<>();
        size=vertexes.size();
        for(int i=0;i<size;i++){
            Insert(vertexes.get(i),i);
        }
        heap.set(map.get(firstRoot),0);
        Up(firstRoot);
    }
    public Vertex getRoot(){
        if(size==1) {
            return null;
        }
        return kek.get(0);
    }

    public void setWay(Vertex vertex,int way){
        heap.set(map.get(vertex),way);
        Up(vertex);
    }

    public void Delete(Vertex vertex){
        int index = map.get(vertex);
        swap(vertex,kek.get(size-1));
        size--;
        Down(kek.get(index));

    }
    private Vertex minChild(Vertex vertex){
        int index=map.get(vertex)*d+1;
        if(index>=size) return  null;
        for(int i = map.get(vertex)*d+2;i<map.get(vertex)*d+d;i++){
            //if(i>=size)return null;
            if(i>=size)break;
                if (heap.get(i) < heap.get(index))
                    index = i;
        }
        return kek.get(index);
    }

    private void Up(Vertex vertex){
        Vertex parent = getParent(vertex);
        while(heap.get(map.get(parent))>heap.get(map.get(vertex))) {
            swap(parent, vertex);
            parent = getParent(vertex);
        }
    }
    private void Down(Vertex vertex) {
        Vertex child = minChild(vertex);
        if (child == null) return;
        while (heap.get(map.get(child)) < heap.get(map.get(vertex))){
            swap(child, vertex);
            child = minChild(vertex);
            if (child == null) return;
        }
    }
    private void Insert(Vertex vertex, int i){
        heap.add(10000000);
        map.put(vertex,i);
        kek.put(i,vertex);
    }
    private void swap(Vertex first,Vertex second){
        int firstWay = heap.get(map.get(first));
        int secondWay = heap.get(map.get(second));
        int firstInd = map.get(first);
        int secondInd = map.get(second);
        heap.set(firstInd,secondWay);
        heap.set(secondInd,firstWay);
        map.replace(first,secondInd);
        map.replace(second,firstInd);
        kek.replace(firstInd,second);
        kek.replace(secondInd,first);
    }
    private Vertex getParent(Vertex vertex){
        int chInd=map.get(vertex);
        int n=(chInd-1)/d;
        return kek.get(n);
    }
}
