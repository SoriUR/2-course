import javax.management.MBeanNotificationInfo;
import javax.management.Notification;
import javax.management.NotificationBroadcasterSupport;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class Spy extends NotificationBroadcasterSupport implements SpyMBean {
    int notificationCount=0;
    private static DrPanel dr;

    public Spy(DrPanel dr, ButPanel bp){
        this.dr=dr;
        bp.spin.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                dr.setRadius((int)bp.spin.getValue());
                dr.repaint();
                Nf();
            }
        });
    }

    public void Nf(){
        for(Point p: dr.Mpoints) {
            if(p.anim)
                newNotification();
        }

    }

    @Override
    public MBeanNotificationInfo[] getNotificationInfo() {
        return new MBeanNotificationInfo[] {
                new MBeanNotificationInfo(null, "Notification", "Universal notification")
        };
    }

    @Override
    public int getNumberOfPoints(){
        return dr.Mpoints.size();
    }

    @Override
    public int getNumberOfEnterPoints(){
       return  dr.num;
    }

    private void newNotification() {
        this.sendNotification(new Notification(null, this, ++notificationCount, "Point has left the area"));
    }
}
