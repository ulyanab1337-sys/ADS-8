// Copyright 2021 NNTU-CS
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "bst.h"

bool isEnglishLetter(char symbol) {
  return (symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z');
}

char convertToLower(char symbol) {
  if (symbol >= 'A' && symbol <= 'Z') {
    return symbol + ('a' - 'A');
  }
  return symbol;
}

void makeTree(BST<std::string> &container, const char *source) {
  std::ifstream input(source);

  if (!input.is_open()) {
    std::cerr << "Cannot open file" << std::endl;
    return;
  }

  std::string buffer;
  char currentChar;

  while (input.get(currentChar)) {
    if (isEnglishLetter(currentChar)) {
      buffer.push_back(convertToLower(currentChar));
    } else {
      if (!buffer.empty()) {
        container.insert(buffer);
        buffer.clear();
      }
    }
  }

  if (!buffer.empty()) {
    container.insert(buffer);
  }

  input.close();
}

bool sortByFrequency(const std::pair<std::string, int> &first,
                     const std::pair<std::string, int> &second) {
  return first.second > second.second;
}

void printFreq(BST<std::string> &vocabulary) {
  std::vector<std::pair<std::string, int>> items;
  vocabulary.collectInfo(items);

  std::sort(items.begin(), items.end(), sortByFrequency);

  std::ofstream output("result/freq.txt");

  for (const auto &entry : items) {
    std::cout << entry.first << " - " << entry.second << std::endl;
    if (output.is_open()) {
      output << entry.first << " - " << entry.second << std::endl;
    }
  }

  output.close();
}
