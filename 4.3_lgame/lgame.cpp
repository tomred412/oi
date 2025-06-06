/*
ID: dermotl1
LANG: C++
PROG: lgame
*/

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <utility>
#include <vector>

using namespace std;

char dictionary[40000][8];
int word_score[40000];      // scores for each word
int word_count[40000][26];  // count of letters for each word

int dict_size = 0;
int input_count[26];  // count of letters for the input
char input[8];

int letter_score[26] = {2, 5, 4, 4, 1, 6, 5, 5, 1, 7, 6, 3, 5,
                        2, 3, 5, 7, 2, 1, 2, 4, 6, 6, 7, 5, 7};

int max_score = 0;
char single_result[40000][8];
char pair_result[40000][8];
int result_count = 0;

bool form_word(int* have, int* need) {
  for (int i = 0; i < 26; ++i) {
    if (need[i] > have[i]) return false;
  }
  return true;
}

int calculate_score(char* word) {
  int score = 0;
  int i = 0;
  while (word[i] != '\0') {
    score += letter_score[word[i] - 'a'];
    ++i;
  }
  return score;
}

void count_letter(char* word, int* count) {
  for (int i = 0; i < 26; ++i) {
    count[i] = 0;
  }
  int i = 0;
  while (word[i] != '\0') {
    ++count[word[i] - 'a'];
    ++i;
  }
}

bool compare_less(char* a, char* b) {
  int i = 0;
  while (a[i] != '\0' && b[i] != '\0') {
    if (a[i] < b[i]) return true;
    if (a[i] > b[i]) return false;
    ++i;
  }
  if (a[i] == '\0' && b[i] != '\0') return true;
  return false;
}

int main() {
  ifstream fin("lgame.in");
  ofstream fout("lgame.out");
  ifstream din("lgame.dict");

  fin >> input;

  for (int i = 0; i < 26; ++i) {
    input_count[i] = 0;
  }

  int i = 0;
  while (input[i] != '\0') {
    input_count[input[i] - 'a']++;
    ++i;
  }

  char word[8];
  while (din >> word) {
    if (word[0] == '.') break;

    int counts[26];
    count_letter(word, counts);

    if (form_word(input_count, counts)) {
      strcpy(dictionary[dict_size], word);
      copy(counts, counts + 26, word_count[dict_size]);

      word_score[dict_size] = calculate_score(word);
      dict_size++;
    }
  }
  for (int i = 0; i < dict_size; ++i) {
    if (word_score[i] > max_score) {
      max_score = word_score[i];

      result_count = 0;
      strcpy(single_result[result_count], dictionary[i]);
      pair_result[result_count][0] = '\0';
      result_count++;

    } else if (word_score[i] == max_score) {
      strcpy(single_result[result_count], dictionary[i]);
      pair_result[result_count][0] = '\0';
      result_count++;
    }
  }

  for (int i = 0; i < dict_size; ++i) {
    for (int j = i; j < dict_size; ++j) {
      int combined[26];

      for (int k = 0; k < 26; ++k) {
        combined[k] = word_count[i][k] + word_count[j][k];
      }
      if (form_word(input_count, combined)) {
        int total_score = word_score[i] + word_score[j];

        if (compare_less(dictionary[j], dictionary[i])) {
          char temp[8];
          int temp_score;
          int temp_count[26];

          strcpy(temp, dictionary[i]);
          strcpy(dictionary[i], dictionary[j]);
          strcpy(dictionary[j], temp);

          temp_score = word_score[i];
          word_score[i] = word_score[j];
          word_score[j] = temp_score;

          for (int k = 0; k < 26; ++k) {
            temp_count[k] = word_count[i][k];
            word_count[i][k] = word_count[j][k];
            word_count[j][k] = temp_count[k];
          }
        }

        strcpy(single_result[result_count], dictionary[i]);
        strcpy(pair_result[result_count], dictionary[j]);

        if (total_score > max_score) {
          max_score = total_score;
          result_count = 0;

          strcpy(single_result[result_count], dictionary[i]);
          strcpy(pair_result[result_count], dictionary[j]);

          result_count++;
        } else if (total_score == max_score) {
          strcpy(single_result[result_count], dictionary[i]);
          strcpy(pair_result[result_count], dictionary[j]);
          result_count++;
        }
      }
    }
  }

  for (int i = 0; i < result_count - 1; ++i) {
    for (int j = i + 1; j < result_count; ++j) {
      if (compare_less(single_result[j], single_result[i]) ||
          (!compare_less(single_result[i], single_result[j]) &&
           compare_less(pair_result[j], pair_result[i]))) {
        char temp1[8], temp2[8];
        strcpy(temp1, single_result[i]);
        strcpy(single_result[i], single_result[j]);
        strcpy(single_result[j], temp1);

        strcpy(temp2, pair_result[i]);
        strcpy(pair_result[i], pair_result[j]);
        strcpy(pair_result[j], temp2);
      }
    }
  }

  fout << max_score << "\n";
  for (int i = 0; i < result_count; ++i) {
    if (pair_result[i][0] == '\0') {
      fout << single_result[i] << "\n";
    } else {
      fout << single_result[i] << " " << pair_result[i] << "\n";
    }
  }

  return 0;
}