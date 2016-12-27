/**
 * Created by Yura on 19.03.2016.
 */
public class HashTable {
    static int Collision=0;
    static int Compare=0;
    static HashSell root;
    public HashTable(String str){
        root = new HashSell(null,null,getKey(str),str);
    }

    private static int getKey(String str){
        return str.substring(str.length()-1,str.length()).charAt(0);
    }

    static void Add(HashSell sell,String str){
        int newItem=getKey(str);
        if(newItem>sell.Key)
        {
            if(sell.RightChild!=null) {
                Add(sell.RightChild, str);
            }
            else{
                sell.RightChild=new HashSell(null,null,getKey(str),str);
            }
        }
        else {
            if (newItem < sell.Key) {
                if (sell.LeftChild != null) {
                    Add(sell.LeftChild, str);
                } else {
                    sell.LeftChild = new HashSell(null, null, getKey(str),str);
                }
            }
            else {
                    Collision++;
                    sell.list.add(str);
            }
        }
    }
    static void Search(HashSell sell,String str){
        int item = getKey(str);
        if(item>sell.Key){
            Search(sell.RightChild,str);
        }
        else{
            if(item<sell.Key) {
                Search(sell.LeftChild, str);
            }
            else
            {
                for(String i:sell.list){
                    Compare++;
                    if(str.equals(i)){
                        System.out.println(i);
                        return;
                    }
                }
            }
        }
    }
}
