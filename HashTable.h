#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2324_P1/ListLinked.h"

template <typename V>
class HashTable: public Dict<V> {

    private:
        int n;
	int max;
	ListLinked<TableEntry<V>>** table;
	int h(std::string key){
		int hash=0;
		for(int i=0;i<key.length();i++){
			hash = hash + key[i]; 
		}
		return hash % this->max;
	}
	

    public:
	HashTable(int size){
		this->n = 0;
		this->max = size;
		this->table = new ListLinked<TableEntry<V>>*[size];
	}

	~HashTable(){
		delete this->table;
	}

	int capacity(){
		return this->max;
	}

	friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
		for(int i=0;i<th.max;i++){
			if(th.table[i]!=NULL){
				for(int j=0;j<th.table[i]->size();j++){
					out<<th.table[i]->get(j);
				}
			}
		}
	return out;
	}

	V operator[](std::string key){
		return this->search(key);
	}

        void insert(std::string key, V value){
		int pos=this->h(key);
		if(this->table[pos]==NULL){
			this->table[pos]=new ListLinked<TableEntry<V>>();
		}
		for(int i=0;i<this->table[pos]->size();i++){
			TableEntry<V> entrada=this->table[pos]->get(i);
			if(entrada.key==key){
				throw std::runtime_error("Ya existe la clave en el diccionario");
			}
		}
		TableEntry<V> entrada(key, value);
		this->table[pos]->append(entrada);
		this->n++;
	}

	V search(std::string key){	
		int pos=this->h(key);
		if(this->table[pos]==NULL){
			throw std::runtime_error("No se encontró la clave");
		}
		for(int i=0;i<this->table[pos]->size();i++){
			TableEntry<V> entrada=this->table[pos]->get(i);
			if(entrada.key==key){
				return entrada.value;
			}
		}
		throw std::runtime_error("Se encontró la lista pero no la entrada");
	}
        
	V remove(std::string key){	
		int pos=this->h(key);
		if(this->table[pos]==NULL){
			throw std::runtime_error("No se encontró la clave");
		}
		for(int i=0;i<this->table[pos]->size();i++){
			TableEntry<V> entrada=this->table[pos]->get(i);
			if(entrada.key==key){
				this->n--;
				return this->table[pos]->remove(i).value;
			}
		}
		throw std::runtime_error("Se encontró la lista pero no la entrada");
	}

	int entries(){
		return this->n;
	}
};

#endif
