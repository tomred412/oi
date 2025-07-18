/*
ID: dermotl1
LANG: JAVA
PROG: money
*/

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

public class money{
    @SuppressWarnings("ConvertToTryWithResources")
    public static void main(String[] args) throws FileNotFoundException, IOException {
		Scanner in = new Scanner(new File("money.in"));
        PrintWriter out = new PrintWriter(new File("money.out"));

        long[] arr = new long[10001];
        int[] coins = new int[25];
        int v, n;
        
        v = in.nextInt();
        n = in.nextInt();

        for (int i = 0; i < v; i++) {
            coins[i] = in.nextInt();
        }
        arr[0] = 1;
        for (int i = 0; i < v; i++) {
            int a = coins[i];
            for (int j = a; j <= n; ++j) {
                arr[j] = arr[j - a] + arr[j];
            }
        }
        out.println(arr[n]);
        
        out.close();
        in.close();
    }

}