import java.util.ArrayList;

/**
 * Created by Yura on 19.03.2016.
 */
public class HashSell {
    HashSell LeftChild;
    HashSell RightChild;
    ArrayList<String> list=new ArrayList<String>();
    int Key;

    public HashSell(HashSell lc,HashSell rc,int k,String str){
        list.add(str);
        LeftChild =lc;
        RightChild=rc;
        Key=k;
    }
}
