/*
ID: dermotl1
LANG: JAVA
PROG: heritage
*/

import java.io.*;
import java.lang.*;
import java.util.*;

public class heritage {

  static char in_array[] = new char[27];
  static int in_length = 0;

  static char pre_array[] = new char[27];
  static int pre_length = 0;

  static char post_array[] = new char[27];
  static int post_tracker = 0;

  public static void solve(int in_first, int in_last, int pre_first,
      int pre_last) {
    if (in_first > in_last)
      return;

    char root = pre_array[pre_first];
    int root_tracker = 0;

    for (int i = in_first; i <= in_last; ++i) {
      if (in_array[i] == root) {
        root_tracker = i;
        break;
      }
    }

    int left_nodes = root_tracker - in_first;

    solve(in_first, root_tracker - 1, pre_first + 1,
        pre_first + left_nodes);
    solve(root_tracker + 1, in_last, pre_first + left_nodes + 1,
        pre_last);

    post_array[post_tracker] = root;
    post_tracker++;
  }

  public static void main(String args[]) throws Exception {
    Scanner in = new Scanner(new File("heritage.in"));
    PrintWriter out = new PrintWriter(new File("heritage.out"));

    char temp;
    String in_string = in.nextLine();
    String pre_string = in.nextLine();

    if (in_string != null) {
      in_array = in_string.toCharArray();
      in_length = in_string.length();
    }

    if (pre_string != null) {
      pre_array = pre_string.toCharArray();
      pre_length = pre_string.length();
    }

    solve(0, in_length - 1, 0, pre_length - 1);

    for (int i = 0; i < post_tracker; i++) {
      out.print(post_array[i]);
    }
    out.println();

    in.close();
    out.close();
  }
}