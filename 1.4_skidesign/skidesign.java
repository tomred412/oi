/*
ID: dermotl1
LANG: JAVA
PROG: skidesign
*/

import java.io.*;
import java.lang.*;
import java.util.*;

public class skidesign {
  public static void main(String[] args) throws Exception {

    Scanner in = new Scanner(new File("skidesign.in"));
    PrintWriter out = new PrintWriter(new File("skidesign.out"));

    int n = 0;
    n = in.nextInt();

    int array[] = new int[1000];

    for (int i = 0; i < n; i++) {
      array[i] = in.nextInt();
    }
    Arrays.sort(array, 0, n);

    int answer = 2147483647;
    int result = 0;
    int total = 0;
    int max = 0;

    for (int min = 0; min < array[n - 1]; min++) {
      max = min + 17;
      total = 0;
      result = 0;

      for (int j = 0; j < n; j++) {
        if (array[j] > max) {
          result = (array[j] - max) * (array[j] - max);
          total += result;
        }
        if (array[j] < min) {
          result = (min - array[j]) * (min - array[j]);
          total += result;
        }
      }
      if (total < answer)
        answer = total;
    }
    out.println(answer);

    in.close();
    out.close();
  }
}
