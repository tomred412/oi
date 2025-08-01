/*
ID: dermotl1
LANG: JAVA
PROG: sprime
*/

import java.io.*;
import java.lang.*;
import java.util.*;

public class sprime {
  static int n;
  static int[] results = new int[10000];
  static int total = 0;

  public static boolean prime(int n) {
    if (n < 2)
      return false;
    if (n == 2)
      return true;
    if (n % 2 == 0)
      return false;

    double temp = Math.sqrt(n);
    int limit = (int) Math.ceil(temp);

    for (int i = 3; i <= limit; i += 2) {
      if (n % i == 0)
        return false;
    }
    return true;
  }

  public static void generate(int num, int length) {
    if (length == n) {

      results[total] = num;
      total++;
      return;
    }

    int digits[] = { 1, 3, 7, 9 };

    for (int i = 0; i < 4; i++) {
      int new_num = num * 10 + digits[i];

      if (prime(new_num) == true)
        generate(new_num, length + 1);
    }
  }

  public static void main(String[] args) throws FileNotFoundException {
    Scanner in = new Scanner(new File("sprime.in"));
    PrintWriter out = new PrintWriter(new File("sprime.out"));

    n = in.nextInt();

    int start[] = { 2, 3, 5, 7 };

    for (int i = 0; i < 4; i++) {
      generate(start[i], 1);
    }

    for (int i = 0; i < total; i++) {
      out.println(results[i]);
    }

    out.close();
    in.close();
  }
}