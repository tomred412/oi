/*
ID: dermotl1
LANG: JAVA
PROG: dualpal
*/

import java.io.*;
import java.lang.*;
import java.util.*;

public class dualpal {
  public static String convert(int n, int B) {
    int l = 0;
    StringBuilder result = new StringBuilder();

    while (n > 0) {
      int remainder = n % B;
      n /= B;

      if (remainder < 10) {
        result.append((char) ('0' + remainder));
      } else {
        result.append((char) ('A' + (remainder - 10)));
      }
    }

    return result.reverse().toString();
  }

  public static boolean palindromeCheck(String check) {
    int length = check.length();
    char[] check1 = check.toCharArray();

    for (int i = 0; i < length / 2; i++) {
      if (check1[i] != check1[length - 1 - i])
        return false;
    }

    return true;
  }

  public static void main(String args[]) throws Exception {
    Scanner in = new Scanner(new File("dualpal.in"));
    PrintWriter out = new PrintWriter(new File("dualpal.out"));

    int N = in.nextInt();
    int S = in.nextInt();

    int found_numbers = 0;
    int check = S + 1;

    while (found_numbers < N) {
      int number_of_bases = 0;

      for (int i = 2; i <= 10; i++) {
        String result_in_base = convert(check, i);

        if (palindromeCheck(result_in_base.toString())) {
          number_of_bases++;
        }

        if (number_of_bases >= 2) {
          out.println(check);
          found_numbers++;
          break;
        }
      }
      check++;
    }

    in.close();
    out.close();
  }
}
