import java.util.ArrayList;

/**
 * Created by Yura on 18.05.2016.
 */
public class Gear {
    private boolean turn;
    private ArrayList<Gear> gears;
    private boolean isSet=false;

    public boolean getTurn(){
        return turn;
    }

    public ArrayList<Gear> getGears(){
        return gears;
    }

    public void setTurn(boolean turn) {
        this.turn = turn;
        isSet=true;
    }
    public void clearSet(){
        isSet=false;
    }

    public void addGear(Gear g){
        gears.add(g);
    }

    public boolean isSet(){
        return  isSet;
    }

    public boolean isEquals(boolean newTurn){
        if(newTurn==turn) return true;
        else return false;
    }

    public Gear(){
        gears = new ArrayList<>();
        isSet=false;
    }
}
