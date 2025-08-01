
/*
ID: dermotl1
LANG: JAVA
PROG: sort3
*/

import java.io.*;
import java.lang.*;
import java.util.*;

public class sort3 {
  public static void main(String[] args) throws FileNotFoundException {
    Scanner in = new Scanner(new File("sort3.in"));
    PrintWriter out = new PrintWriter(new File("sort3.out"));

    int n;
    n = in.nextInt();

    int[] original = new int[n];
    int[] sorted = new int[n];

    for (int i = 0; i < n; i++) {
      original[i] = in.nextInt();
      sorted[i] = original[i];
    }

    Arrays.sort(sorted);

    int num = 0; 
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {

        if (i == j) continue;

        if (original[i] != sorted[i] && original[j] != sorted[j] &&
          original[i] == sorted[j] && original[j] == sorted[i]) {
          
            int temp = original[i];
            original[i] = original[j];
            original[j] = temp;

            num++;
            break;
       }
      }
    }

    int unsort = 0;

    for (int i = 0; i < n; i++) {
      if (original[i] != sorted[i]) unsort++;
   }

    num = (unsort / 3) * 2 + num;

   out.println(num);

   in.close();
   out.close();
  }
}