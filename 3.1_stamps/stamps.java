
/*
ID: dermotl1
LANG: JAVA
PROG: stamps
*/
import java.io.*;
import java.lang.*;
import java.util.*;

public class stamps {
  public static void main(String args[]) throws Exception {
    Scanner in = new Scanner(new File("stamps.in"));
    PrintWriter out = new PrintWriter(new File("stamps.out"));

    int infinity = Integer.MAX_VALUE;

    int k = in.nextInt();
    int n = in.nextInt();

    int number_of_stamps[] = new int[2000000];
    Arrays.fill(number_of_stamps, infinity);

    int stamps[] = new int[50];
    number_of_stamps[0] = 0;

    for (int i = 0; i < n; ++i) {
      stamps[i] = in.nextInt();
    }
    int i;
    for (i = 1; i <= 2000000; ++i) {
      for (int j = 0; j < n; ++j) {
        int a = stamps[j];

        if (i - a >= 0 && number_of_stamps[i - a] + 1 < number_of_stamps[i]) {
          number_of_stamps[i] = number_of_stamps[i - a] + 1;
        }
      }
      if (number_of_stamps[i] > k)
        break;
    }
    out.println(i - 1);

    in.close();
    out.close();
  }
}
