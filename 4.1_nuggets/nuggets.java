/*
ID: dermotl1
LANG: JAVA
PROG: nuggets
*/

import java.io.*;
import java.lang.*;
import java.util.*;


public class nuggets {
    public static int gcd(int a, int b) {
        while (b != 0) {
            int r = a % b;
            a = b;
            b = r;
        }
        return a;
    }
    public static void main(String args[]) throws FileNotFoundException, IOException{
        Scanner in = new Scanner(new File("nuggets.in"));
        PrintWriter out = new PrintWriter(new File("nuggets.out"));

        Boolean can_make_nugget[] = new Boolean[65536];
        Arrays.fill(can_make_nugget, false);

        int n = in.nextInt();
        int pack[] = new int[10];
        int max_pack = 0;

        for (int i = 0; i < n; ++i) {
            pack[i] = in.nextInt();
            if (pack[i] > max_pack) max_pack = pack[i];
        }

        int gcds = pack[0];
        for (int i = 1; i < n; ++i) {
          gcds = gcd(gcds, pack[i]);
        }
        if (gcds != 1) {
          out.println("0");
          in.close();
          out.close();
        }

        can_make_nugget[0] = true;

        for (int i = 1; i < 65536; ++i) {
          for (int j = 0; j < n; ++j) {
            if (i >= pack[j] && can_make_nugget[i - pack[j]]) {
              can_make_nugget[i] = true;
              break;
            }
          }
        }

        int run = 0;
        int answer = 0;

        for (int i = 1; i < 65536; ++i) {
          if (can_make_nugget[i]) {
            run++;

            if (run >= max_pack)
              break; 
          } else {

            run = 0;
            answer = i; 
          }
        }
        out.println(answer);

        in.close();
        out.close();
    }
}