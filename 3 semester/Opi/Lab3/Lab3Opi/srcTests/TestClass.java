import org.junit.Test;
import static org.junit.Assert.*;

public class TestClass{

    @Test
    public void testIsInKonturEnter(){
        Kontur kontur= new Kontur(10);
        assertTrue(kontur.Check(new Tochka(-1, -2)));
        assertTrue(kontur.Check(new Tochka(-9, -8)));
        assertTrue(kontur.Check(new Tochka(1, 1)));
        assertTrue(kontur.Check(new Tochka(-1, 2)));
    }

    @Test
    public void testIsInKonturNotEneter(){
        Kontur kontur= new Kontur(5);
        assertFalse(kontur.Check(new Tochka(5,  -5)));
        assertFalse(kontur.Check(new Tochka(-5,  0)));
        assertFalse(kontur.Check(new Tochka(-5,  -3)));
        assertFalse(kontur.Check(new Tochka(4, 3)));
    }

}