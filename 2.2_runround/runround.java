/*
ID: dermotl1
LANG: JAVA
PROG: runround
*/

import java.io.*;
import java.lang.*;
import java.util.*;

public class runround {
  public static boolean compute(int number) {
    ArrayList<Integer> digits = new ArrayList<>();
    int digit = 0;
    boolean[] track = new boolean[10];
    int num = number;

    while (num > 0) {
      digit = num % 10;
      if (digit == 0 || track[digit])
        return false;
      track[digit] = true;

      digits.add(digit);
      num /= 10;
    }

    Collections.reverse(digits);

    boolean[] saw = new boolean[digits.size()];
    int watch = 0;
    int digit_num = 0;

    while (!saw[watch]) {
      saw[watch] = true;
      digit_num++;
      watch = (watch + digits.get(watch)) % digits.size();
    }
    if (digit_num == digits.size() && watch == 0)
      return true;
    return false;
  }

  public static void main(String[] args) throws FileNotFoundException {
    Scanner in = new Scanner(new File("runround.in"));
    PrintWriter out = new PrintWriter(new File("runround.out"));

    int m;
    m = in.nextInt();

    boolean stop = false;
    int n = m + 1;

    while (!stop) {
      if (compute(n)) {
        stop = true;
        out.println(n);
        in.close();
        out.close();
      }
      n++;
    }

    in.close();
    out.close();
  }
}
