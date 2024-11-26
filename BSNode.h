#ifndef BSNODE_H
#define BSNODE_H

template <typename T>
class BSNode {
public:
    T elem;
    BSNode<T>* left;
    BSNode<T>* right;

    BSNode(T elem, BSNode<T>* left = nullptr, BSNode<T>* right = nullptr);
};

template <typename T>
BSNode<T>::BSNode(T elem, BSNode<T>* left, BSNode<T>* right)
    : elem(elem), left(left), right(right) {}

#endif