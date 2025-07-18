/*
ID: dermotl1
LANG: JAVA
PROG: race3
*/

import java.io.*;
import java.lang.*;
import java.util.*;
public class race3 {

static ArrayList<ArrayList<Integer>> adj = new ArrayList<>();
static int counts;

public static void dfs(int start, boolean[] available, int avoid) {
  if (start == avoid) return;
  available[start] = true;
  for (Integer it : adj.get(start)) {
    if (!available[it]) dfs(it, available, avoid);
  }
}

public static void main(String args[]) throws FileNotFoundException {
  Scanner in = new Scanner(new File("race3.in"));
  PrintWriter out = new PrintWriter(new File("race3.out"));

  for (int i = 0; i < 50; ++i) {
    adj.add(new ArrayList<>());
}

  while (true) {
    int n = in.nextInt();
    if (n == -1) break;

    while (n != -2) {
      adj.get(counts).add(n);
      n = in.nextInt();
    }
    counts++;
  }
  int finish = counts - 1;

  ArrayList<Integer> unavoidable = new ArrayList<>();

  for (int i = 1; i < finish; ++i) {
    boolean[] available = new boolean[counts];
    dfs(0, available, i);

    if (!available[finish]) unavoidable.add(i);
  }

  ArrayList<Integer> split = new ArrayList<>();

  for (Integer it : unavoidable) {
    boolean[] available_start = new boolean[counts];
    dfs(0, available_start, it);

    boolean[] available_other = new boolean[counts];
    dfs(it, available_other, -1);

    boolean overlap = false;

    for (int i = 0; i < counts; ++i) {

      if (i != it && available_start[i] && available_other[i]) {
        overlap = true;
        break;
      }
    }
    if (!overlap) split.add(it);
  }
  out.print(unavoidable.size());

  for (Integer it : unavoidable) {
    out.print(" " + it);
  }
  out.println();

  out.print(split.size());

  for (Integer it : split) {
    out.print(" " + it);
  }
  out.println();

  in.close();
  out.close();
}
}