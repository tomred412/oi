/*
ID: dermotl1
LANG: JAVA
PROG: hidden
*/

import java.io.*;
import java.lang.*;
import java.util.*;

public class hidden {
  public static void main(String args[]) throws Exception {
    Scanner in = new Scanner(new File("hidden.in"));
    PrintWriter out = new PrintWriter(new File("hidden.out"));

    int l;
    char password[] = new char[200002];
    l = in.nextInt();

    String line = "";
    while (line.length() < l) {
      String temp = in.next();
      if (temp != null) {
        line += temp.trim();
      }
    }

    for (int i = 0; i < l; i++) {
      password[i] = line.charAt(i);
      password[i + l] = password[i];
    }

    int memory[] = new int[200002];
    Arrays.fill(memory, -1);

    int best = 0;
    for (int i = 1; i < 2 * l; ++i) {
      int challenge = memory[i - best - 1];

      while (challenge != -1 && password[i] != password[challenge + best + 1]) {
        if (password[i] < password[challenge + best + 1]) {
          best = i - challenge - 1;
        }
        challenge = memory[challenge];
      }
      if (challenge == -1 && password[best] != password[i]) {
        if (password[i] < password[best]) {
          best = i;
        }
        memory[i - best] = -1;
      } else {
        memory[i - best] = challenge + 1;
      }
    }

    out.println(best % l);

    in.close();
    out.close();
  }
}