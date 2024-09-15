#pragma once

#include <iostream>
#include <vector>

template <typename T>
class BinaryTree
{
private:
    int _depth;
    std::vector<std::vector<T>> _tree;

public:
    BinaryTree();

    void setDepth(int depth);
    void setNode(int n, int i, T value);
    T getNode(int n, int i) const;
    void display() const;
    int getValueWidth(const T &value) const;
    int getMaxValueWidth() const;
    void fillTree(double S0, double U, double D);
    bool isEmptyNode(int level, int index) const;
    int calculatePadding(int spaceBetween, int valueWidth) const;
};
