/*
ID: dermotl1
LANG: JAVA
PROG: fracdec
*/

import java.io.*;
import java.lang.*;
import java.util.*;

public class fracdec {
  public static void main(String[] args) throws FileNotFoundException {
      Scanner in = new Scanner(new File("fracdec.in"));
      PrintWriter out = new PrintWriter(new File("fracdec.out"));

  int n, d;
  n = in.nextInt();
  d = in.nextInt();

  ArrayList<Integer> decimal_digit = new ArrayList<>();
  int[] remainder_pos = new int[d];
  Arrays.fill(remainder_pos, -1);

  int integer = n / d;
  out.print(integer);
  int remainder = n % d;

  int count = Integer.toString(integer).length();

  if (remainder == 0) {
    out.println(".0");
    in.close();
    out.close();
  }
  out.print(".");
  count++;

  int repeat_start = -1;
  for (int i = 0; remainder != 0; i++) {
    if (remainder_pos[remainder] != -1) {
      repeat_start = remainder_pos[remainder];
      break;
    }
    remainder_pos[remainder] = i;
    remainder *= 10;
    decimal_digit.add(remainder / d);
    remainder %= d;
  }

  for (int i = 0; i < decimal_digit.size(); i++) {
    if (i == repeat_start) {
      out.print("(");
      count++;
    }
    int temp = decimal_digit.get(i);
    out.print(temp);
    count++;

    if (count == 76) {
      out.println();
      count = 0;
    }
  }

  if (repeat_start != -1) out.print(")");
  out.println();

  in.close();
  out.close();
  }
}
