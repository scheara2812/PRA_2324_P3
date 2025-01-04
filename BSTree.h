#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {
private:
    BSNode<T>* root; 
    int nelem;      

    BSNode<T>* search(BSNode<T>* n, T e) const {
        if (n == nullptr) {
            throw std::runtime_error("Elemento no encontrado");
        }
        if (e < n->elem) {
            return search(n->left, e);
        } else if (e > n->elem) {
            return search(n->right, e);
        } else {
            return n; 
        }
    }

    BSNode<T>* insert(BSNode<T>* n, T e) {
        if (n == nullptr) {
            return new BSNode<T>(e);
	     }
        if (e < n->elem) {
            n->left = insert(n->left, e);
        } else if (e > n->elem) {
            n->right = insert(n->right, e);
        } else {
            throw std::runtime_error("Elemento duplicado");
        }
        return n;
    }

    BSNode<T>* removeNode(BSNode<T>* n, T e) {
        if (n == nullptr) {
            throw std::runtime_error("Elemento no encontrado");
        }

        if (e < n->elem) {
            n->left = removeNode(n->left, e);
        } else if (e > n->elem) {
            n->right = removeNode(n->right, e);
        } else {
            if (n->left == nullptr) {
                BSNode<T>* temp = n->right;
                delete n;
                return temp;
            } else if (n->right == nullptr) {
                BSNode<T>* temp = n->left;
                delete n;
                return temp;
            }

            BSNode<T>* successor = n->right;
            while (successor->left != nullptr) {
                successor = successor->left;
            }

            n->elem = successor->elem;

            n->right = removeNode(n->right, successor->elem);
        }

        return n;
    }

    void print_inorder(std::ostream& out, BSNode<T>* n) {
        if (n != nullptr) {
            print_inorder(out, n->left);
            out << n->elem << " ";
            print_inorder(out, n->right);
        }
    }


public:
    BSTree() {
        root = nullptr;
        nelem = 0;
	    }


    int size() const {
        return nelem;
    }

    T search(T e) {
        BSNode<T>* result = search(root, e);
        return result->elem;
    }

    T remove(T e) {
        T result = this->search(e);
        removeNode(this->root, e);
        return result;
    }

    T operator[](T e) const {
        return search(e);
    }

    void insert(T e) {
        root = insert(root, e);
        nelem++;
    }

    friend std::ostream& operator<<(std::ostream& out, BSTree<T>& bst) {
        bst.print_inorder(out, bst.root);
        return out;
    }
    };

#endif
