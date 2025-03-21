#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<int> arr;

  cout << "Please enter a command:\n\npush (element) - Insert an element\npop "
          "(element) - Remove root element\nmake (elements) - Create a heap "
          "from "
          "numbers\nprint - Print the elements in the heap, sorted\nsort - "
          "Print a sorted version of the elements in the heap\nexit - Exit the "
          "program\n";
  while (true) {
    char in[5];
    cout << "\nEnter here:\n";
    cin >> in;

    int n;
    if (in[0] == 'p' && in[1] == 'u' && in[2] == 's' && in[3] == 'h') {
      cout << "Please enter the number to put into the heap:\n";
      cin >> n;
      // put n in the heap
      arr.push_back(n);
      int curr_index = arr.size() - 1;
      int par_index = (curr_index - 1) / 2;
      while (curr_index > 0 && arr[par_index] > arr[curr_index]) {
        swap(arr[par_index], arr[curr_index]);
        curr_index = par_index;
        par_index = (curr_index - 1) / 2;
      }
      for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
      }
      cout << "\n";
    }

    else if (in[0] == 'm' && in[1] == 'a' && in[2] == 'k' && in[3] == 'e') {
      while (true) {
        int a;
        cout << "\nEnter one element at a time, then press any letter to "
                "finish:\n";
        // put n in the heap
        cin >> a;
        if (cin.fail()) {
          cin.clear();
          cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          break;
        }

        arr.push_back(a);
        int curr_index = arr.size() - 1;
        int par_index = (curr_index - 1) / 2;
        while (curr_index > 0 && arr[par_index] > arr[curr_index]) {
          swap(arr[par_index], arr[curr_index]);
          curr_index = par_index;
          par_index = (curr_index - 1) / 2;
        }
      }
      cout << "Your heap:\n";
      for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
      }
      cout << "\n";
    }

    else if (in[0] == 'p' && in[1] == 'o' && in[2] == 'p') {
      if (arr.empty()) {
        cout << "Your heap is empty!\n";
      } else {
        cout << "You have removed: " << arr[0] << "\n";
        arr[0] = arr.back();
        arr.pop_back();

        int curr_index = 0;
        int left = 2 * curr_index + 1;
        int right = 2 * curr_index + 2;

        while (true) {
          if (left >= arr.size()) break;
          int smallest = curr_index;
          if (arr[left] < arr[curr_index]) {
            smallest = left;
          }
          if (right < arr.size() && arr[right] < arr[smallest]) {
            smallest = right;
          }
          if (smallest == curr_index) break;
          swap(arr[curr_index], arr[smallest]);

          curr_index = smallest;
          left = 2 * curr_index + 1;
          right = 2 * curr_index + 2;
        }
      }
    }

    else if (in[0] == 's' && in[1] == 'o' && in[2] == 'r' && in[3] == 't') {
      vector<int> temp = arr;
      vector<int> sorted;
      while (!temp.empty()) {
        sorted.push_back(temp[0]);
        temp[0] = temp.back();
        temp.pop_back();
        int curr_index = 0;
        int left = (curr_index + 1) * 2 - 1;
        int right = (curr_index + 1) * 2;
        while (true) {
          if (left >= temp.size()) break;
          int smallest = curr_index;
          if (temp[left] < temp[curr_index]) {
            smallest = left;
          }
          if (right < temp.size() && temp[right] < temp[smallest]) {
            smallest = right;
          }
          if (smallest == curr_index) break;
          swap(temp[curr_index], temp[smallest]);

          curr_index = smallest;
          left = (curr_index + 1) * 2 - 1;
          right = (curr_index + 1) * 2;
        }
      }

      cout << "Here are your elements, sorted:\n";
      for (int i = 0; i < sorted.size(); i++) {
        cout << sorted[i] << " ";
      }
      cout << "\n";
    } else if (in[0] == 'p' && in[1] == 'r' && in[2] == 'i' && in[3] == 'n' &&
               in[4] == 't') {
      cout << "Here is your heap:\n";
      if (arr.empty())
        cout << "The heap is empty.\n";
      else
        for (int i = 0; i < arr.size(); i++) {
          cout << arr[i] << " ";
        }
      cout << "\n";
    } else if (in[0] == 'e' && in[1] == 'x' && in[2] == 'i' && in[3] == 't') {
      cout << "Okay, exiting\n...\n";
      break;
    } else {
      cout << "Sorry, that's not a command. Here are the command "
              "again:\n\npush (elements) - Insert elements\npop "
              "(elements) - Remove elements\nmake (elements) - Create a heap "
              "from "
              "numbers\nprint - Print the elements in the heap, sorted\nsort - "
              "Print a sorted version of the elements in the heap\nexit - Exit "
              "the "
              "program\n";
    }
  }
  return 0;
}
