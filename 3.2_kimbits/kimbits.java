/*
ID: dermotl1
LANG: JAVA
PROG: kimbits
*/

import java.io.*;
import java.lang.*;
import java.util.*;

public class kimbits {
    public static long count;
    public static long cxy[][] = new long[32][32];

    public static void Choose() {
        cxy[0][0] = 0;
        cxy[1][0] = 1;
        cxy[1][1] = 1;
        for (int i = 0; i < 31; ++i) {
            cxy[i][0] = 1;
            cxy[i][i] = 1;
            for (int j = 1; j <= i - 1; ++j) {
                cxy[i][j] = cxy[i - 1][j - 1] + cxy[i - 1][j];
            }
        }
    }

    public static long OneOrZero(long n, long l, long i) {
        count = 0;
        while (l >= 0) {
            count = count + cxy[(int) n - 1][(int) l];
            l--;
        }
        if (count < i)
            return 1;

        return 0;
    }

    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("kimbits.in"));
        PrintWriter out = new PrintWriter(new File("kimbits.out"));

        Choose();

        int n, l;
        long i;
        n = in.nextInt();
        l = in.nextInt();
        i = in.nextLong();
        long n_1 = n;

        for (int j = 0; j < n_1; ++j) {
            long a = OneOrZero(n, l, i);
            out.print(a);
            if (a == 0) {
                n = n - 1;
            } else {
                n = n - 1;
                l = l - 1;
                i = i - count;
            }
        }
        out.println();

        in.close();
        out.close();
    }
}
