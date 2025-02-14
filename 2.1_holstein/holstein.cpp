/*
ID: dermotl1
LANG: C++
PROG: holstein
*/

#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

int v;                         // vitamins
int g;                         // feed types
vector<int> min_vitamins;      // min vitamin required levels
vector<int> feeds;             // the actual feeds (there are v types of g)
vector<int> best_combination;  // store the best combination/answer
int min_scoops = 16;

void find(
    int feed, vector<int> current_vitamins, vector<int> current_feeds,
    int scoops) {  // feed = feed (progressing through), vitamins = sum of so
                   // far, current_feed = feeds used, scoops = number of scoops
  bool required = true;
  for (int i = 0; i < v; i++) {
    if (current_vitamins[i] < min_vitamins[i]) {  // has not met requirement
      required = false;
      break;
    }
  }
  if (required == true) {
    if (scoops < min_scoops ||
        (scoops == min_scoops && current_feeds < best_combination)) {
      min_scoops = scoops;
      best_combination = current_feeds;  // set the vectors
    }
    return;
  }

  if (feed >= g) return;  // there's no more feeds to continue to

  find(feed + 1, current_vitamins, current_feeds,
       scoops);  // go to the next feed

  for (int i = 0; i < v; i++) {  // stay at the current feed
    current_vitamins[i] +=
        feeds[feed * v +
              i];  // this is where feeds data for current "feed" is, then adds
                   // it to contain that feed's feeds as well
  }
  current_feeds.push_back(feed + 1);  // starts at 0, so add 1

  find(feed + 1, current_vitamins, current_feeds, scoops + 1);  // keep going
}

int main() {
  ofstream fout("holstein.out");
  ifstream fin("holstein.in");

  fin >> v;
  min_vitamins.resize(v);

  for (int i = 0; i < v; i++) {
    fin >> min_vitamins[i];
  }

  fin >> g;
  feeds.resize(g * v);
  for (int i = 0; i < (g * v); i++) {
    fin >> feeds[i];
  }

  vector<int> current_vitamins(v, 0);
  vector<int> current_feeds;

  find(0, current_vitamins, current_feeds, 0);

  fout << min_scoops;
  for (int i = 0; i < best_combination.size(); i++) {
    fout << " " << best_combination[i];
  }
  fout << "\n";

  return 0;
}
