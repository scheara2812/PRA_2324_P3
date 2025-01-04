#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"
#include <vector>
#include <ostream>
#include <stdexcept>


template <typename V>
class BSTreeDict : public Dict<V> {
private:
    BSTree<TableEntry<V>>* tree;

public:
    BSTreeDict() {
        tree = new BSTree<TableEntry<V>>();
    }

    ~BSTreeDict() {
        delete tree;
    }

    void insert(std::string key, V value) override {
        TableEntry<V> entry(key, value);
        tree->insert(entry);
    }

    V search(std::string key) override {
	    TableEntry<V> entry(key, V());
        TableEntry<V> result = tree->search(entry);
        return result.value;
    }

    int remove(std::string key) override {
        TableEntry<V> entry(key, V());
        TableEntry<V> result = tree->search(entry);
        V valor = result.value;
        tree->remove(entry);
        return valor;
    }

    int entries() override {
        return tree->size();
    }

    V operator[](std::string key) {
        return search(key);
    }

    friend std::ostream& operator<<(std::ostream& out, BSTreeDict<V>& dict) {
        out << *dict.tree;
        return out;
    }
};

#endif

