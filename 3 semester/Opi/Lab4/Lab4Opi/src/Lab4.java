import javax.management.MBeanServer;
import javax.management.ObjectName;
import java.lang.management.ManagementFactory;

public class Lab4{
    public static void main(String args[]) {
        //SwingUtilities.invokeLater(Frame::new);
        Frame fr = new Frame();
        MBeanServer mBeanServer = ManagementFactory.getPlatformMBeanServer();
        // ObjectName mBeanSpyName, mBeanTimeName;
        averageTime mBeanTime = new averageTime(fr.getDr());
        Spy mBeanSpy = new Spy(fr.getDr(),fr.getBP());
        ObjectName mBeanSpyName = null;
        ObjectName mBeanTimeName = null;

        try {
            mBeanSpyName = new ObjectName("Lab4:name=Spythere");
            mBeanTimeName = new ObjectName("Lab4:name=Timethere");
             mBeanServer.registerMBean(mBeanSpy, mBeanSpyName);
            mBeanServer.registerMBean(mBeanTime, mBeanTimeName);
        } catch (Exception e) {
            e.printStackTrace();

        }
    }
}

