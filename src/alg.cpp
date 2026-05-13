#include <fstream>
#include <cctype>
#include <algorithm>
#include <iostream>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) return;

    std::string word;
    char ch;

    while (file.get(ch)) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            word += std::tolower(static_cast<unsigned char>(ch));
        } else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }
    if (!word.empty()) tree.insert(word);
    file.close();
}

void printFreq(BST<std::string>& tree) {
    auto nodes = tree.getNodes();

    std::sort(nodes.begin(), nodes.end(),
              [](const auto& a, const auto& b) {
                  if (a.second != b.second) return a.second > b.second;
                  return a.first < b.first;
              });

    std::ofstream out("result/freq.txt");

    for (const auto& node : nodes) {
        std::cout << node.first << ": " << node.second << std::endl;
        out << node.first << ": " << node.second << std::endl;
    }
    out.close();
}
