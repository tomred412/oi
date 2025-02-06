#include <iostream>

using namespace std;

struct Node {
  int data;
  int left, right;
};

Node s[10000];
int size = 1;
int root = -1;

void insert(int data) {
  if (root == -1) {
    root = 0;
    s[root].data = data;
    s[root].left = -1;
    s[root].right = -1;
    return;
  }

  int current = root;

  while (true) {
    if (data > s[current].data) {
      if (s[current].right == -1) {
        s[current].right = size;
        s[size].left = -1;
        s[size].right = -1;
        s[size].data = data;
        size++;
        return;
      }
      current = s[current].right;
      continue;
    }
    if (data < s[current].data) {
      if (s[current].left == -1) {
        s[current].left = size;
        s[size].left = -1;
        s[size].right = -1;
        s[size].data = data;
        size++;
        return;
      }
      current = s[current].left;
      continue;
    }
  }
}

void print();
// prints the data in the tree, in order

void print(int node) {
  if (s[node].left != -1) {
    print(s[node].left);
  }

  cout << s[node].data << " ";

  if (s[node].right != -1) {
    print(s[node].right);
  }
}

bool find(int data) {
  int current = root;

  while (current != -1) {
    if (s[current].data == data) return true;
    if (data < s[current].data) current = s[current].left;
    if (data > s[current].data) current = s[current].right;
  }

  return false;
}

int main() {
  cout << "Please enter the list, then a period, then m numbers to find in the "
          "tree.\n";

  int n;
  while (cin >> n) {
    insert(n);
    if (cin.peek() == '.') break;
  }

  char period;
  cin >> period;

  if (period != '.') {
    cout << "There should be a period.\n";
    return 0;
  }

  int m;
  cin >> m;

  int p = 0;

  for (int i = 0; i < m; i++) {
    cin >> p;
    if (find(p) == true) cout << p << ": yes\n";
    if (find(p) == false) cout << p << ": no\n";
  }
  cout << "Sorted tree:\n";
  print(0);

  return 0;
}
