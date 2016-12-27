/**
 * Created by Yura on 24.05.2016.
 */
public class Main {
    public static void main(String args[]){
        if(args.length==0) System.out.println(false);
        String str= args[0];
        int iter=-1;
        boolean wasA=false, wasB = false, accept=true;
        while (iter<str.length()-1 & accept){
            iter++;
            switch (str.charAt(iter)){
                case 'a':
                    if(wasB) //Б было?
                        if(iter+1<=str.length()) // есть еще 1 символ?
                            if(str.charAt(iter+1)=='b'){//если символ б
                                if(!(iter==str.length()-2)) accept=false; //если не конец строки
                            }
                            else {
                                accept=false;
                            }
                    wasA=true;
                    break;
                case 'b':
                    wasB=true;
                    break;
                case 'c':
                    if(!(iter==str.length()-1)) accept=false; //если С не последний символ
                    break;
                default: accept=false;
                    break;
            }
        }
        System.out.println(accept);
    }
}
