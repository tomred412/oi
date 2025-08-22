/*
ID: dermotl1
LANG: JAVA
PROG: combo
*/

import java.io.*;
import java.lang.*;
import java.util.*;

public class combo {
  public static void main(String[] args) throws Exception {
    Scanner in = new Scanner(new File("combo.in"));
    PrintWriter out = new PrintWriter(new File("combo.out"));

    int n, fj1, fj2, fj3, m1, m2, m3;
    n = in.nextInt();
    fj1 = in.nextInt();
    fj2 = in.nextInt();
    fj3 = in.nextInt();
    m1 = in.nextInt();
    m2 = in.nextInt();
    m3 = in.nextInt();

    int count = 0;

    for (int x = 1; x <= n; x++) {
      for (int y = 1; y <= n; y++) {
        for (int z = 1; z <= n; z++) {
          if (((Math.abs(x - fj1) <= 2) || (Math.abs(x - fj1) >= n - 2)) &&
              ((Math.abs(y - fj2) <= 2) || (Math.abs(y - fj2) >= n - 2)) &&
              ((Math.abs(z - fj3) <= 2) || (Math.abs(z - fj3) >= n - 2))) {
            count++;

          } else if (((Math.abs(x - m1) <= 2) || (Math.abs(x - m1) >= n - 2)) &&
              ((Math.abs(y - m2) <= 2) || (Math.abs(y - m2) >= n - 2)) &&
              ((Math.abs(z - m3) <= 2) || (Math.abs(z - m3) >= n - 2))) {
            count++;
          }
        }
      }
    }

    out.println(count);
    in.close();
    out.close();
  }
}
