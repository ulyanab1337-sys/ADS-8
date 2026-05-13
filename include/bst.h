// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>

template<typename T>
class BST {
private:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;
        
        Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    
    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
    
    Node* insert(Node* node, const T& value) {
        if (!node) {
            return new Node(value);
        }
        
        if (value < node->key) {
            node->left = insert(node->left, value);
        } else if (value > node->key) {
            node->right = insert(node->right, value);
        } else {
            node->count++;
        }
        return node;
    }
    
    int getDepth(Node* node) const {
        if (!node) return 0;
        return 1 + std::max(getDepth(node->left), getDepth(node->right));
    }
    
    bool search(Node* node, const T& value) const {
        if (!node) return false;
        if (value == node->key) return true;
        if (value < node->key) return search(node->left, value);
        return search(node->right, value);
    }
    
    void collectNodes(Node* node, std::vector<std::pair<T, int>>& nodes) const {
        if (node) {
            collectNodes(node->left, nodes);
            nodes.push_back({node->key, node->count});
            collectNodes(node->right, nodes);
        }
    }
    
public:
    BST() : root(nullptr) {}
    
    ~BST() {
        clear(root);
    }
    
    void insert(const T& value) {
        root = insert(root, value);
    }
    
    int depth() const {
        return getDepth(root);
    }
    
    bool search(const T& value) const {
        return search(root, value);
    }
    
    std::vector<std::pair<T, int>> getNodes() const {
        std::vector<std::pair<T, int>> nodes;
        collectNodes(root, nodes);
        return nodes;
    }
};

#endif  // INCLUDE_BST_H_
