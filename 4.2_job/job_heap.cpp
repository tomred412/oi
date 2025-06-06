/*
ID: dermotl1
LANG: C++
PROG: job
*/

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

struct machine {
  int free_time;
  int id;
};

machine heap[1000];
int heap_size;

void push(machine value) {
  int pos = heap_size;
  ++heap_size;
  heap[pos] = value;

  while (pos > 0) {
    int parent = (pos - 1) / 2;
    if (heap[parent].free_time <= heap[pos].free_time) break;
    swap(heap[parent], heap[pos]);
    pos = parent;
  }
}

machine pop() {
  machine top = heap[0];
  --heap_size;
  heap[0] = heap[heap_size];

  int pos = 0;
  while (true) {
    int left = 2 * pos + 1;
    int right = 2 * pos + 2;
    int smallest = pos;

    if (left < heap_size && heap[left].free_time < heap[smallest].free_time)
      smallest = left;
    if (right < heap_size && heap[right].free_time < heap[smallest].free_time)
      smallest = right;

    if (smallest == pos) break;
    swap(heap[pos], heap[smallest]);
    pos = smallest;
  }
  return top;
}

int main() {
  ifstream fin("job.in");
  ofstream fout("job.out");
  int n, m1, m2;
  fin >> n >> m1 >> m2;

  vector<int> a_times(m1);
  vector<int> b_times(m2);

  for (int i = 0; i < m1; ++i) {
    fin >> a_times[i];
  }

  for (int i = 0; i < m2; ++i) {
    fin >> b_times[i];
  }

  vector<int> a_store_finished;  // when each job finished using machine a
  heap_size = 0;
  for (int i = 0; i < m1; ++i) {
    machine temp;
    temp.free_time = a_times[i];
    temp.id = i;
    push(temp);
  }

  for (int i = 0; i < n; ++i) {
    machine best_a = pop();
    a_store_finished.push_back(best_a.free_time);
    best_a.free_time += a_times[best_a.id];
    push(best_a);
  }

  int final_a_time =
      *max_element(a_store_finished.begin(), a_store_finished.end());

  sort(a_store_finished.begin(), a_store_finished.end());

  vector<int> b_free_time(m2);
  heap_size = 0;

  for (int i = 0; i < m2; ++i) {
    machine temp;
    temp.free_time = b_times[i];
    temp.id = i;
    push(temp);
  }

  vector<int> b_store_finished(n);

  for (int i = n - 1; i >= 0; --i) {
    machine best_b = pop();
    b_store_finished[i] = a_store_finished[i] + best_b.free_time;
    best_b.free_time += b_times[best_b.id];
    push(best_b);
  }

  int final_b_time =
      *max_element(b_store_finished.begin(), b_store_finished.end());

  fout << final_a_time << " " << final_b_time << "\n";

  return 0;
}
