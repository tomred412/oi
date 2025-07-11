/*
ID: dermotl1
LANG: JAVA
PROG: stall4
*/

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

public class stall4 {
    static int cow_likes[][] = new int[201][201];
    static int cow_likes_count[] = new int[201];
    static int final_match[] = new int[201];
    static Boolean visited[] = new Boolean[201];
    static int n, m;
    static int result;

    public static boolean solve(int cow) {
        for (int i = 0; i < cow_likes_count[cow]; ++i) {
            int stall = cow_likes[cow][i];

            if (!visited[stall]) {
                visited[stall] = true;
                if (final_match[stall] == 0 || solve(final_match[stall])) {
                    final_match[stall] = cow;
                    return true;
                }
            }
        }
        return false;
    }
    public static void main(String[] args) throws FileNotFoundException, IOException {
        Scanner in = new Scanner(new File("stall4.in"));
        PrintWriter out = new PrintWriter(new File("stall4.out"));

        n = in.nextInt();
        m = in.nextInt();

        for (int i = 1; i <= n; ++i) {
            cow_likes_count[i] = in.nextInt();
            for (int j = 0; j < cow_likes_count[i]; ++j) {
                cow_likes[i][j] = in.nextInt();
            }
        }

        for (int i = 1; i <= n; ++i) {
            Arrays.fill(visited, false);
            if (solve(i)) result++;
        }

        out.println(result);

        in.close();
        out.close();
    }
}
