import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

/**
 * Created by Yura on 19.03.2016.
 */
public class Main {
    public static void main(String args[]){
        FileReader fis;
        try {
            fis = new FileReader("D://InTAble.txt");
        }
        catch (FileNotFoundException e) {
            System.out.println("Файл не найден");
            return;
        }
        int c;
        String str="";
        ArrayList<String> list = new ArrayList<String>();
        try {
            while((c=fis.read())!=-1){
                if(c!=10) {
                    str = str.concat(Character.toString((char) c));
                }
                else{
                    str = str.substring(0,str.length()-1);
                    list.add(str);
                    str = "";
                }
            }
            list.add(str);
        } catch (IOException e) {
            System.out.println(e.getMessage());
            return;
        }
        new HashTable(list.get(0));
        for(int i=1;i<list.size();i++){
            HashTable.Add(HashTable.root,list.get(i));
        }
        for(int i=0;i<list.size();i++){
            HashTable.Search(HashTable.root,list.get(i));
        }
        System.out.println("Среднее количество коллизий:"+ String.valueOf(HashTable.Collision/26));
        System.out.println("Cреднее количество сравнений:"+ String.valueOf(HashTable.Compare/150));
    }
}


