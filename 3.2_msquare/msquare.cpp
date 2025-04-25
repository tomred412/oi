/*
ID: dermotl1
LANG: C++
PROG: msquare
*/

#include <algorithm>
#include <climits>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

void transform_a(int original[8], int changed[8]) {
  changed[0] = original[7];
  changed[1] = original[6];
  changed[2] = original[5];
  changed[3] = original[4];
  changed[4] = original[3];
  changed[5] = original[2];
  changed[6] = original[1];
  changed[7] = original[0];
}

void transform_b(int original[8], int changed[8]) {
  changed[0] = original[3];
  changed[1] = original[0];
  changed[2] = original[1];
  changed[3] = original[2];
  changed[4] = original[5];
  changed[5] = original[6];
  changed[6] = original[7];
  changed[7] = original[4];
}

void transform_c(int original[8], int changed[8]) {
  for (int i = 0; i < 8; ++i) {
    changed[i] = original[i];
  }
  int temp = original[1];
  changed[1] = original[6];
  changed[2] = temp;
  changed[5] = original[2];
  changed[6] = original[5];
}

bool compare(int a[8], int b[8]) {
  for (int i = 0; i < 8; ++i) {
    if (a[i] != b[i]) return false;
  }
  return true;
}

int make_ids(int a[8]) {  // using permutation, identify each as a number
  int result = 0;
  int factorial_7[8] = {1, 1, 2, 6, 24, 120, 720, 5040};
  for (int i = 0; i < 8; ++i) {  // each position
    int counts = 0;
    for (int j = i + 1; j < 8;
         ++j) {  // how many numbers after i are smaller than it
      if (a[j] < a[i]) counts++;
    }
    result += counts * factorial_7[7 - i];
  }
  return result;
}

void search(int goal[8], char result[100], int &length) {
  int start[8] = {1, 2, 3, 4, 5, 6, 7, 8};
  int storage_sequence[40320][8];  // stores the transformed sequence
  char storage_path[40320][100] = {
      {0}};                    // shows how to get to a storage using transforms
  int storage_lengths[40320];  // stores the lengths of each numbered sequence
  bool visited[40320];         // shows which sequences have been visited

  for (int i = 0; i < 40320; ++i) {
    visited[i] = false;
  }

  int front = 0;  // points to the front (process) and back (add) of the queue
  int back = 1;

  for (int i = 0; i < 8; ++i) {
    storage_sequence[0][i] = start[i];
  }

  storage_lengths[0] = 0;
  visited[make_ids(start)] = true;

  int goal_id = make_ids(goal);

  int current[8], next[8];

  while (front < back) {
    for (int i = 0; i < 8; ++i) {
      current[i] = storage_sequence[front][i];
    }
    int current_length = storage_lengths[front];

    if (make_ids(current) == goal_id) {
      length = current_length;
      for (int i = 0; i < current_length; ++i) {
        result[i] = storage_path[front][i];
      }
      return;
    }
    transform_a(current, next);
    int next_id_a = make_ids(next);
    if (!visited[next_id_a]) {
      visited[next_id_a] = true;
      for (int i = 0; i < 8; ++i) {
        storage_sequence[back][i] = next[i];
      }
      for (int i = 0; i < current_length; ++i) {
        storage_path[back][i] = storage_path[front][i];
      }
      storage_path[back][current_length] = 'A';
      storage_lengths[back] = current_length + 1;
      back++;
    }
    transform_b(current, next);
    int next_id_b = make_ids(next);
    if (!visited[next_id_b]) {
      visited[next_id_b] = true;
      for (int i = 0; i < 8; ++i) {
        storage_sequence[back][i] = next[i];
      }
      for (int i = 0; i < current_length; ++i) {
        storage_path[back][i] = storage_path[front][i];
      }
      storage_path[back][current_length] = 'B';
      storage_lengths[back] = current_length + 1;
      back++;
    }

    transform_c(current, next);
    int next_id_c = make_ids(next);
    if (!visited[next_id_c]) {
      visited[next_id_c] = true;
      for (int i = 0; i < 8; ++i) {
        storage_sequence[back][i] = next[i];
      }
      for (int i = 0; i < current_length; ++i) {
        storage_path[back][i] = storage_path[front][i];
      }
      storage_path[back][current_length] = 'C';
      storage_lengths[back] = current_length + 1;
      back++;
    }

    front++;
  }
}

int main() {
  ifstream fin("msquare.in");
  ofstream fout("msquare.out");

  int goal[8];

  for (int i = 0; i < 8; ++i) {
    fin >> goal[i];
  }

  int length;
  char path[100];

  search(goal, path, length);

  fout << length << "\n";
  if (length == 0) fout << "\n";

  for (int i = 0; i < length; ++i) {
    fout << path[i];
    if ((i + 1) % 60 == 0) fout << "\n";
  }
  if (length % 60 != 0) fout << "\n";

  return 0;
}
