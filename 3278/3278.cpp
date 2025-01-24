#include <iostream>

using namespace std;

int main() {
  int n, k;
  cin >> n >> k;

  if (n == k) {
    cout << 0 << "\n";
    return 0;
  }

  int queue[200000];  // queue, the max FJ could be is 200000, since he might go
                      // after to get the cow at 100000
  bool visited[100001];  // has [i] been visited?

  for (int i = 0; i < 100001; i++) {
    visited[i] = false;
  }

  int start = 0;  // delete from queue after using it
  int end = 0;    // put in queue

  end++;
  queue[end] = n;     // put FJ at queue's start
  visited[n] = true;  // mark it as done

  int minutes = 0;  // the minutes it will take

  while (start < end) {
    int step =
        end - start;  // the steps after the current position to be processed

    // process all pos in this step
    for (int i = 0; i < step; i++) {
      start++;
      int current = queue[start];  // temporary FJ current position

      int moves[3] = {current - 1, current + 1,
                      2 * current};  // store the moves in an array so it can be
                                     // used in for loop

      for (int j = 0; j < 3; j++) {
        int next = moves[j];  // try the next move in the for loop

        if (next >= 0 && next <= 100000 &&
            visited[next] == false) {  // check if it can be used
          if (next == k) {             // check if it's the solution
            cout << minutes + 1 << "\n";
            return 0;
          }

          queue[end++] = next;   // increment the queue
          visited[next] = true;  // mark it as visited
        }
      }
    }

    minutes++;  // move to the next steps
  }

  return 0;
}

