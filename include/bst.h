// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <utility>
#include <vector>

template <typename T> class BST {
 private:
  struct Node {
    T info;
    int freq;
    Node *leftChild;
    Node *rightChild;
  };

  Node *top;

  Node *createNode(T value) {
    Node *newNode = new Node;
    newNode->info = value;
    newNode->freq = 1;
    newNode->leftChild = nullptr;
    newNode->rightChild = nullptr;
    return newNode;
  }

  Node *attach(Node *current, T value) {
    if (current == nullptr) {
      return createNode(value);
    }
    if (value < current->info) {
      current->leftChild = attach(current->leftChild, value);
    } else if (value > current->info) {
      current->rightChild = attach(current->rightChild, value);
    } else {
      current->freq++;
    }
    return current;
  }

  void eraseAll(Node *current) {
    if (current == nullptr) return;
    eraseAll(current->leftChild);
    eraseAll(current->rightChild);
    delete current;
  }

  int computeHeight(Node *current) {
    if (current == nullptr) return -1;
    int leftHeight = computeHeight(current->leftChild);
    int rightHeight = computeHeight(current->rightChild);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
  }

  bool findKey(Node *current, T value) {
    if (current == nullptr) return false;
    if (current->info == value) return true;
    if (value < current->info) {
      return findKey(current->leftChild, value);
    } else {
      return findKey(current->rightChild, value);
    }
  }

  void gatherData(Node *current, std::vector<std::pair<T, int>> &buffer) {
    if (current == nullptr) return;
    gatherData(current->leftChild, buffer);
    buffer.push_back({current->info, current->freq});
    gatherData(current->rightChild, buffer);
  }

 public:
  BST() : top(nullptr) {}
  ~BST() { eraseAll(top); }

  void insert(T value) { top = attach(top, value); }

  int depth() { return computeHeight(top); }

  bool search(T value) { return findKey(top, value); }

  void collectInfo(std::vector<std::pair<T, int>> &output) {
    gatherData(top, output);
  }
};

#endif  // INCLUDE_BST_H_
