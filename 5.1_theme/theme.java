/*
ID: dermotl1
LANG: JAVA
PROG: theme
*/

import java.io.*;
import java.lang.*;
import java.util.*;

public class theme {
static int original[] = new int[5002];
static int difference[] = new int[5002]; 
static int n;

public static boolean CheckLengthExisting(int length) {
  for (int i = 0; i + length <= n - 1; ++i) {
    for (int j = length + i; j + length <= n; ++j) {

      if (Math.abs(i - j) >= length + 1) {
        boolean check = true;

        for (int q = 0; q < length; ++q) {
          if (difference[i + q] != difference[j + q]) {
            check = false;
            break;
          }
        }
        if (check) return true;
      }
    }
  }
  return false;
}

public static void main(String args[]) throws FileNotFoundException {
  Scanner in = new Scanner(new File("theme.in"));
  PrintWriter out = new PrintWriter(new File("theme.out"));

  n = in.nextInt();

  for (int i = 0; i < n; ++i) {
    original[i] = in.nextInt();
  }

  for (int i = 0; i < n - 1; ++i) {
    difference[i] = original[i + 1] - original[i];
  }

  int low = 4;
  int high = n - 1;
  int result = 0;

  while (low <= high) {
    int middle = (low + high) / 2;
    if (CheckLengthExisting(middle)) {
      result = middle;
      low = middle + 1;
    } else {
      high = middle - 1;
    }
  }

  if (result >= 4) {
    out.println(result + 1);
  } else {
    out.println(0);
  }
  
    in.close();
    out.close();
}
}