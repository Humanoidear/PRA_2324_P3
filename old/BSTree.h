#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
        int nelem;
        BSNode<T> *root;
        BSNode<T>* search(BSNode<T>* n, T e) const;
        BSNode<T>* insert(BSNode<T>* n, T e);
        void print_inorder(std::ostream &out, BSNode<T>* n) const;
        BSNode<T>* remove(BSNode<T>* n, T e);
        T max(BSNode<T>* n) const;
        BSNode<T>* remove_max(BSNode<T>* n);
        void delete_cascade(BSNode<T>* n);

    public:
        BSTree();
        int size() const;
        T search(T e) const;
        T operator[](T e) const;
        void insert(T e);
        friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst);
        void remove(T e);
        ~BSTree();

    
};

// Implement the methods
template <typename T>
BSTree<T>::BSTree() {
    this->nelem = 0;
    this->root = nullptr;
}

template <typename T>
int BSTree<T>::size() const {
    return this->nelem;
}

template <typename T>
T BSTree<T>::search(T e) const {
    return search(this->root, e);
}

template <typename T>
BSNode<T>* BSTree<T>::search(BSNode<T>* n, T e) const {
    if (n == nullptr) {
        throw std::runtime_error("Value not found");
    }
    if (e > n->elem) {
        return search(n->right, e);
    }
    if (e < n->elem) {
        return search(n->left, e);
    } else {
        return n;
    }
}

template <typename T>
T BSTree<T>::operator[](T e) const {
    return search(e);
}

template <typename T>
void BSTree<T>::insert(T e) {
    this->root = insert(this->root, e);
    this->nelem++;
}

template <typename T>
BSNode<T>* BSTree<T>::insert(BSNode<T>* n, T e) {
    if (n == nullptr) {
        return new BSNode<T>(e);
    } else if (n-> elem == e) {
        throw std::runtime_error("Value already exists");
    } else if (e < n->elem) {
        n->right = insert(n->right, e);
    } else {
        n->left = insert(n->left, e);
    }
    return n;
}

template <typename T>
std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
    bst.print_inorder(out, bst.root);
    return out;
}

template <typename T>
void BSTree<T>::print_inorder(std::ostream &out, BSNode<T>* n) const {
    if (n != nullptr) {
        print_inorder(out, n->left);
        out << n->elem << " ";
        print_inorder(out, n->right);
    }
}

template <typename T>
void BSTree<T>::remove(T e) {
    this->root = remove(this->root, e);
    this->nelem--;
}

template <typename T>
BSNode<T>* BSTree<T>::remove(BSNode<T>* n, T e) {
    if (n == nullptr) {
        throw std::runtime_error("Value not found");
    }
    if (e < n->elem) {
        n->left = remove(n->left, e);
    } else if (e > n->elem) {
        n->right = remove(n->right, e);
    } else {
        if (n->left == nullptr) {
            BSNode<T>* temp = n->right;
            delete n;
            return temp;
        } else if (n->right == nullptr) {
            BSNode<T>* temp = n->left;
            delete n;
            return temp;
        } else {
            n->elem = max(n->left);
            n->left = remove_max(n->left);
        }
    }
    return n;
}

template <typename T>
T BSTree<T>::max(BSNode<T>* n) const {
    if (n->right == nullptr) {
        return n->elem;
    }
    return max(n->right);
}

template <typename T>
BSNode<T>* BSTree<T>::remove_max(BSNode<T>* n) {
    if (n->right == nullptr) {
        BSNode<T>* temp = n->left;
        delete n;
        return temp;
    }
    n->right = remove_max(n->right);
    return n;
}

template <typename T>
BSTree<T>::~BSTree() {
    delete_cascade(this->root);
}

template <typename T>
void BSTree<T>::delete_cascade(BSNode<T>* n) {
    if (n != nullptr) {
        delete_cascade(n->left);
        delete_cascade(n->right);
        delete n;
    }
}

#endif