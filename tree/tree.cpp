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

int main() {

int n;
while (cin >> n) {
  insert(n);
}

  return 0;
}
