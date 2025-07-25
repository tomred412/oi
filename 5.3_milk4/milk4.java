/*
ID: dermotl1
LANG: JAVA
PROG: milk4
*/

import java.io.*;
import java.lang.*;
import java.util.*;

public class milk4 {

static int q, p;
static ArrayList<Integer> pails = new ArrayList<>();
static ArrayList<Integer> best = new ArrayList<>();

public static boolean CanUse(int q, ArrayList<Integer> pail_subset) {
  boolean[] usable = new boolean[q + 1];
  Arrays.fill(usable, false);
  usable[0] = true;

  for (int i = 0; i <= q; ++i) {
    if (usable[i]) {
      for (int j = 0; j < pail_subset.size(); ++j) {
        int next = i + pail_subset.get(j);
        if (next <= q) usable[next] = true;
      }
    }
  }
  return usable[q];
}

public static void TryAll(int pos, int size, ArrayList<Integer> current) {
  if (current.size() == size) {
    if (CanUse(q, current)) {
        best = new ArrayList<>(current);
    }
    return;
  }

  if (pos >= p || !best.isEmpty()) return;

  current.add(pails.get(pos));
  TryAll(pos + 1, size, current);
  current.remove(current.size() - 1);

  TryAll(pos + 1, size, current);
}

public static void main(String args[]) throws FileNotFoundException {
Scanner in = new Scanner(new File("milk4.in"));
PrintWriter out = new PrintWriter(new File("milk4.out"));

q = in.nextInt();
p = in.nextInt();

  for (int i = 0; i < p; ++i) {
    int temp = in.nextInt();
    pails.add(temp);
  }

  Collections.sort(pails);

  for (int i = 1; i <= p; ++i) {
    ArrayList<Integer> current = new ArrayList<>();
    TryAll(0, i, current);
    if (!best.isEmpty()) break;
  }

  out.print(best.size());
  for (Integer it : best) {
    out.print(" " + it);
  }
  out.print("\n");

  in.close();
  out.close();
}
}
