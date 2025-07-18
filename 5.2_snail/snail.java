/*
ID: dermotl1
LANG: JAVA
PROG: snail
*/
import java.io.*;
import java.lang.*;
import java.util.*;

public class snail {
static boolean visited[][] = new boolean[121][121];
static boolean barriers[][] = new boolean[121][121];
static int n;
static int b;

static int dx[] = {-1, 0, 1, 0};  
static int dy[] = {0, 1, 0, -1};

public static int TraverseGrid(int direction, int x, int y,
                 int turns) {  
  visited[x][y] = true;
  int new_x, new_y;
  int steps = 1;

  new_x = x + dx[direction];
  new_y = y + dy[direction];

  if (new_x >= 0 && new_y < n && new_x < n && new_y >= 0) {
    if (!barriers[new_x][new_y] && !visited[new_x][new_y])
      steps = 1 + TraverseGrid(direction, new_x, new_y, 0);

    else if (barriers[new_x][new_y]) {
      if (turns == 0) {
        turns++;
        steps = Math.max(TraverseGrid(((direction + 1) % 4), x, y, turns),
                    TraverseGrid(((direction + 3) % 4), x, y, turns));
      }
    }
  } else if (turns == 0) {
    turns++;
    steps = Math.max(TraverseGrid(((direction + 1) % 4), x, y, turns),
                TraverseGrid(((direction + 3) % 4), x, y, turns));
  }
  visited[x][y] = false;
  return steps;
}

public static void main(String args[]) throws FileNotFoundException {

  Scanner in = new Scanner(new File("snail.in"));
  PrintWriter out = new PrintWriter(new File("snail.out"));

  n = in.nextInt();
  b = in.nextInt();

  for (int i = 0; i < b; ++i) {
    String temp = in.next();
    char temp1 = temp.charAt(0);
    String tempString = temp.substring(1);
    int temp2 = Integer.parseInt(tempString);
    
    barriers[temp1 - 'A'][temp2 - 1] = true;
  }

  int answer = Math.max(TraverseGrid(2, 0, 0, 0), TraverseGrid(1, 0, 0, 0));

  out.println(answer);

  in.close();
  out.close();

}
}
