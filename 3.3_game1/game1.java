/*
ID: dermotl1
LANG: JAVA
PROG: game1
*/


import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

public class game1 {

    static int[] original = new int[100];
    static int[] sum = new int[101];
    static int[][] result = new int[100][101];
    
    public static void sums(int n) {
        for (int i = 0; i < n; ++i) {
            sum[i + 1] += sum[i] + original[i];
        }
    }
    public static void main(String[] args) throws FileNotFoundException, IOException {
        Scanner in = new Scanner(new File("game1.in"));
        PrintWriter out = new PrintWriter(new File("game1.out"));

        int n;
        n = in.nextInt();

        for (int i = 0; i < n; ++i) {
            original[i] = in.nextInt();
        }

        sums(n);

        for (int i = 0; i < n; ++i) {
            result[i][i] = original[i];
          }

          for (int i = 2; i <= n; ++i) {
            for (int j = 0; j + i - 1 < n; ++j) {
              int r = j + i - 1;
              int total = sum[r + 1] - sum[j];
              result[j][r] = total - Math.min(result[j + 1][r], result[j][r - 1]);
            }
          }

          out.println(result[0][n - 1] + " " + (sum[n] - result[0][n - 1]));

          in.close();
          out.close();
    }
}
