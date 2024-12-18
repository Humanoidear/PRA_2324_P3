#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree
{
private:
    int nelem = 0;
    BSNode<T> *root = nullptr;

    BSNode<T> *search(BSNode<T> *n, T e) const
    {
        if (n == nullptr)
        {
            throw std::runtime_error("Elemento no encontrado");
        }
        else if (n->elem < e)
        {
            return search(n->right, e);
        }
        else if (n->elem > e)
        {
            return search(n->left, e);
        }
        else
        {
            return n;
        }
    }

    BSNode<T> *insert(BSNode<T> *n, T e)
    {
        if (n == nullptr)
        {
            nelem++;
            return new BSNode(e);
        }
        else if (n->elem == e)
        {
            throw std::runtime_error("Elemento duplicado");
        }
        else if (n->elem < e)
        {
            n->right = insert(n->right, e);
        }
        else
        {
            n->left = insert(n->left, e);
        }
        return n;
    }

    void print_postorder(std::ostream &out, BSNode<T> *n) const
    {
        if (n != nullptr)
        {
            print_postorder(out, n->left);
            print_postorder(out, n->right);
            out << n->elem << " ";
        }
    }

    BSNode<T> *remove(BSNode<T> *n, T e)
    {
        if (n == nullptr)
        {
            throw std::runtime_error("Elemento no encontrado");
        }
        else if (n->elem < e)
        {
            n->right = remove(n->right, e);
        }
        else if (n->elem > e)
        {
            n->left = remove(n->left, e);
        }
        else
        {
            if (n->left != nullptr && n->right != nullptr)
            {
                nelem--;
                n->elem = max(n->left);
                n->left = remove_max(n->left);
            }
            else
            {
                nelem--;
                n = (n->left != nullptr) ? n->left : n->right;
            }
        }
        return n;
    }

    T max(BSNode<T> *n) const
    {
        if (n == nullptr)
        {
            throw std::runtime_error("Elemento no encontrado");
        }
        else if (n->right != NULL)
        {
            return max(n->right);
        }
        else
        {
            return n->elem;
        }
    }

    BSNode<T> *remove_max(BSNode<T> *n)
    {
        if (n->right == nullptr)
        {
            return n->left;
        }
        else
        {
            n->right = remove_max(n->right);
            return n;
        }
    }

    T min(BSNode<T> *n) const
    {
        if (n == nullptr)
        {
            throw std::runtime_error("Elemento no encontrado");
        }
        else if (n->left != NULL)
        {
            return min(n->left);
        }
        else
        {
            return n->elem;
        }
    }

    void delete_cascade(BSNode<T> *n)
    {
        if (n != nullptr)
        {
            delete_cascade(n->left);
            delete_cascade(n->right);
            delete n;
        }
    }

public:
    BSTree() {}

    int size() const
    {
        return nelem;
    }

    T search(T e) const
    {
        return search(root, e)->elem;
    }

    T operator[](T e) const
    {
        return search(e);
    }

    void insert(T e)
    {
        root = insert(root, e);
    }

    friend std::ostream &operator<<(std::ostream &out, const BSTree<T> &bst)
    {
        bst.print_postorder(out, bst.root);
        return out;
    }

    void remove(T e)
    {
        root = remove(root, e);
    }

    ~BSTree()
    {
        delete_cascade(root);
    }

    T predecesor(T e)
    {
        BSNode<T> *n = search(root, e);
        if (n == nullptr)
        {
            throw std::runtime_error("Elemento no encontrado");
        }

        // Postorder predecessor: the last node visited before the current node in a postorder traversal
        BSNode<T> *predecessor = nullptr;
        bool found = false;
        postorder_predecessor(root, e, found, predecessor);

        if (predecessor == nullptr)
        {
            throw std::runtime_error("No hay predecesor");
        }

        return predecessor->elem;
    }

    T sucesor(T e)
    {
        BSNode<T> *n = search(root, e);
        if (n == nullptr)
        {
            throw std::runtime_error("Elemento no encontrado");
        }

        // Postorder successor: the next node visited after the current node in a postorder traversal
        BSNode<T> *successor = nullptr;
        bool found = false;
        postorder_successor(root, e, found, successor);

        if (successor == nullptr)
        {
            throw std::runtime_error("No hay sucesor");
        }

        return successor->elem;
    }

	T min() const
	{
		return min(root);
	}

private:
    void postorder_predecessor(BSNode<T> *n, T e, bool &found, BSNode<T> *&predecessor)
    {
        if (n == nullptr)
        {
            return;
        }

        postorder_predecessor(n->left, e, found, predecessor);
        postorder_predecessor(n->right, e, found, predecessor);

        if (n->elem == e)
        {
            found = true;
        }
        else if (found && predecessor == nullptr)
        {
            predecessor = n;
        }
    }

    void postorder_successor(BSNode<T> *n, T e, bool &found, BSNode<T> *&successor)
    {
        if (n == nullptr)
        {
            return;
        }

        postorder_successor(n->left, e, found, successor);
        postorder_successor(n->right, e, found, successor);

        if (found && successor == nullptr)
        {
            successor = n;
            return;
        }

        if (n->elem == e)
        {
            found = true;
        }
    }
};

#endif