#include "BinaryTree.h"
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <iomanip>

template <typename T>
BinaryTree<T>::BinaryTree() : _depth(0) {}

template <typename T>
void BinaryTree<T>::setDepth(int depth)
{
    _depth = depth;
    _tree.resize(_depth + 1);
    for (int i = 0; i <= _depth; ++i)
    {
        _tree[i].resize(i + 1);
    }
}

template <typename T>
void BinaryTree<T>::setNode(int n, int i, T value)
{
    if (n < 0 || n > _depth || i < 0 || i > n)
    {
        throw std::out_of_range("Indices out of range");
    }
    _tree[n][i] = value;
}

template <typename T>
T BinaryTree<T>::getNode(int n, int i) const
{
    if (n < 0 || n > _depth || i < 0 || i > n)
    {
        throw std::out_of_range("Indices out of range");
    }
    return _tree[n][i];
}

template <typename T>
void BinaryTree<T>::fillTree(double S0, double U, double D)
{
    for (int n = 0; n <= _depth; ++n)
    {
        for (int i = 0; i <= n; ++i)
        {
            T stockPriceAtNode = S0 * std::pow(1 + U, i) * std::pow(1 + D, n - i);
            setNode(n, i, stockPriceAtNode);
        }
    }
}

template <typename T>
bool BinaryTree<T>::isEmptyNode(int level, int index) const
{
    // S'assure que le niveau est dans la plage
    if (level < 0 || level >= _tree.size())
    {
        return true; // Niveau en dehors de la plage => noeud vide
    }

    // S'assure que l'index est dans la plage pour le niveau donné
    if (index < 0 || index >= _tree[level].size())
    {
        return true; //  Index en dehors de la plage le niveau donné => noeux vide
    }

    return _tree[level][index] == T();
}


template <typename T>
// Fonction pour calculer l'espacement autour d'une valeur pour la centrer
int BinaryTree<T>::calculatePadding(int spaceBetween, int valueWidth) const
{
    int totalPadding = spaceBetween - valueWidth;
    return totalPadding > 0 ? totalPadding / 2 : 0;
}

template <typename T>
void BinaryTree<T>::display() const
{
    int i = 0;
    int j = 0;

    while (i <= 2 * _depth)
    {
        for (int k = 0; k <= (4 * _depth - i); k++)
        {
            std::cout << " ";
        }

        if (i % 2 == 1)
        {
            j = 0;
            while (j <= i)
            {
                if (j % 2 == 1)
                {
                    std::cout << "\\ "; // 1 seul back slash ne fonctionne pas sur c++, on va à droite
                }
                else
                {
                    std::cout << "/ "; // on va à gauche
                }
                j = j + 1;
            }
        }

        else
        {
            for (int j = 0; j <= i / 2; j++)
            {
                std::cout << _tree[i / 2][j];

                if (i > 0)
                {
                    std::cout << "   ";
                }
            }
        }
        std::cout << "\n";
        i = i + 1;
    }
}

template class BinaryTree<int>;
template class BinaryTree<double>;
template class BinaryTree<bool>;
