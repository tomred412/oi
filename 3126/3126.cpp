#include <cmath>
#include <iostream>

using namespace std;

bool prime(int i) {
  if (i < 1000 || i >= 10000) return false;
  if (i <= 1) return false;
  for (int j = 2; j * j <= i; j++) {
    if (i % j == 0) return false;
  }
  return true;
}

int search(int start, int end) {
  if (start == end) return 0;

  bool visited[10000];

  for (int i = 0; i < 10000; i++) {
    visited[i] = false;
  }

  int queue[10000];  // current number
  int steps[10000];  // steps to transform to i, steps[i] = 2 means it took 2
                     // steps to get to that point

  int front = 0;  // front of queue, to delete from queue
  int last = 0;   // last of queue, where to insert the numbers and to process

  queue[last] = start;
  steps[last] = 0;
  visited[start] = true;
  last++;  // the queue has a new number

  while (front < last) {         // the queue still needs processing
    int current = queue[front];  // process the current
    int step = steps[front];     // find the steps
    front++;                     // move to the next one to process

    for (int i = 0; i < 4; ++i) {  // all 4 digits
      int digit =
          (current / (int)pow(10, 3 - i)) % 10;  // find the digit we are at

      for (int d = 0; d <= 9; ++d) {     // find the digit to replace that one
        if (i == 0 && d == 0) continue;  // cannot be 0 for hundreds
        if (d == digit) continue;        // cannot be the same

        int new_num = current - digit * (int)pow(10, 3 - i) +
                      d * (int)pow(10, 3 - i);  // calculate the new number

        if (new_num == end) {  // check if it's the end
          return (step + 1);
        }

        if (prime(new_num) &&
            visited[new_num] ==
                false) {  // check if it's a prime and not visited
          visited[new_num] = true;
          queue[last] = new_num;
          steps[last] = step + 1;
          last++;
        }
      }
    }
  }
  return -1;
}

int main() {
  int n;
  cin >> n;
  while (n-- != 0) {
    int a = 0;
    int b = 0;
    cin >> a >> b;
    int result = search(a, b);
    if (result == -1) {
      cout << "Impossible" << endl;
    } else {
      cout << result << endl;
    }
  }
  return 0;
}

