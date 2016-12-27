import java.util.Scanner;
import java.util.Stack;

class Task3
{
    public static void main(String[] args)
    {
        String Rs;
        float R;
        while(true) {
            System.out.println("Enter R");
            Scanner sc = new Scanner(System.in);
            Rs = sc.next();
            try {
                R = Float.parseFloat(Rs);
                if (R <= 0) throw new RuntimeException();
            } catch (Exception e) {
                System.out.println("Uncorrect input");
                continue;
            }
            break;
        }
        Stack<Tochka> st = new Stack<Tochka>();
        Tochka t1 = new Tochka(1,3);
        Tochka t2 = new Tochka(-2,1);
        Tochka t3 = new Tochka(4,-4);
        Tochka t4 = new Tochka(-4,-4);
        Tochka t5 = new Tochka(-4,4);
        Tochka t6 = new Tochka(0,0);
        Tochka t7 = new Tochka(3,4);
        Tochka t8 = new Tochka(3,2);
        Tochka t9 = new Tochka(-2,1);
        st.push(t1);
        st.push(t2);
        st.push(t3);
        st.push(t4);
        st.push(t5);
        st.push(t6);
        st.push(t7);
        st.push(t8);
        st.push(t9);
        Kontur kn = new Kontur(R);
        for (int i=0;i<9;i++)
        {
            System.out.print("("+st.peek().getx()+","+st.peek().gety()+")  ");
            if (kn.Check(st.pop())==true)
            {
                System.out.println("Point is in area");
            }
            else
            {
                System.out.println("Point is out of area");
            }
        }
    }
}


