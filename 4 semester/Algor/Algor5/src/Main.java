import java.util.ArrayList;

/**
 * Created by Yura on 18.05.2016.
 */
public class Main {
    private static ArrayList<Gear> g;
    private static ArrayList<Gear> edit = new ArrayList<>();
    private static ArrayList<Gear> skip = new ArrayList<>();
    private static ArrayList<Gear> watched = new ArrayList<>();
    private static ArrayList<Gear> remember = new ArrayList<>();
    private static boolean flag;
    private static int n,m,count,iter=0,max=0;
    private static boolean mas [][];
    public static void main(String args[]){
        try {
            for(int i =0;i<args.length;i++) {
                Integer.parseInt(args[i]);
            }
            n = Integer.parseInt(args[iter++]);
            m = Integer.parseInt(args[iter++]);
            g = new ArrayList<>();
            for(int i=0;i<n;i++){
                g.add(new Gear());
            }
            mas = new boolean[n][n];
            for(int i = 0;i<m;i++){
                int j = Integer.parseInt(args[iter++])-1;
                int k = Integer.parseInt(args[iter++])-1;
                mas[j][k] = true;
                g.get(j).addGear(g.get(k));
                g.get(k).addGear(g.get(j));
            }
        }catch (NumberFormatException e){
            System.out.printf("Input Error");
            return;
        }
        catch (ArrayIndexOutOfBoundsException e){
            System.out.printf("Input Error");
            return;
        }

        boolean hz = checkRotation(g);
        System.out.println("Is it rotate without editing? "+hz);
        if(!hz) {
            MaxRotating(0);
        }
        else {
            System.out.println("How many rotate? "+count);
            return;
        }
        System.out.print("Which were deleted? ");
        for(Gear gear:remember){
            System.out.print(g.indexOf(gear)+1+" ");
        }
        System.out.println();
        System.out.println("How many are rotating now? "+max);
    }

    private static boolean checkRotation(ArrayList<Gear> g){
        count=1;
        g.get(0).setTurn(true);
        boolean p = Check(g.get(0));
        watched.clear();
        clearGears();
        return p;
    }

    private static void MaxRotating(int iter) {
        skip.add(edit.get(iter));
        flag = checkRotation(g);
        if (!flag) MaxRotating(iter + 2);
        max();
        skip.remove(edit.get(iter));
        skip.add(edit.get(iter+1));
        flag = checkRotation(g);
        if (!flag) MaxRotating(iter + 2);
        max();
        skip.remove(edit.get(iter+1));
    }

    private static void max(){
        if(max<count) {
            max=count;
            remember.clear();
            remember.addAll(skip);
        }
    }
    private static boolean Check(Gear gr) {
        for (Gear gear : gr.getGears()) {
            if(skip.contains(gear)) continue;
            if (!gear.isSet()) {
                gear.setTurn(!gr.getTurn());
                count++;
            } else {
                if(gear.getTurn()==gr.getTurn()){
                    edit.add(gear);
                    edit.add(gr);
                    return false;
                }
            }
        }
        watched.add(gr);
        for (Gear gear : gr.getGears()) {
            if(skip.contains(gear) || watched.contains(gear)) continue;
            if(!Check(gear))return false;
        }
        return true;
    }

    private static void clearGears(){
        for(Gear ge:g){
            ge.clearSet();
        }
    }
}