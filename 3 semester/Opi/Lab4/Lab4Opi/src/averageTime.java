import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.Calendar;
import java.util.Date;

public class averageTime implements averageTimeMBean{
    public double value=0;
    Calendar SaveData;
    public int clicks=0;
    public averageTime(DrPanel dr){
        dr.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                if(SaveData==null)SaveData=Calendar.getInstance();
                Calendar CurrentData = Calendar.getInstance();
                Calendar calculate = Calendar.getInstance();
                calculate.setTime(new Date(CurrentData.getTime().getTime() - SaveData.getTime().getTime()));
                SaveData = CurrentData;
                value = (value*clicks+calculate.getTimeInMillis()/1000)/++clicks;
            }
        });
    }

    @Override
    public double getAvarageValue(){
        return  value;
    }
}
