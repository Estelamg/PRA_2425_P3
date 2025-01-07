#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"
#include "BSTree.h"

template <typename V>
class BSTreeDict: public Dict<V> {
	private:
		BSTree<TableEntry<V>>* tree;
		int entryCount;	//Contador

	public:
		BSTreeDict(){
			tree = new BSTree<TableEntry<V>>();
			entryCount = 0;
		}

		~BSTreeDict(){
			delete tree;
		}
		
		void insert(std::string key, V value) override{
			TableEntry<V> entry(key, value);
			tree->insert(entry);
			entryCount++;
		}

		V search(std::string key) const override{
			TableEntry<V> entry(key);
			return tree->search(entry).value;
		}

		V remove(std::string key) override{
			TableEntry<V> entry(key);
			V value = tree->search(entry).value;
			tree->remove(entry);
			entryCount--;

			return value;
		}

		int entries() const override{
			return entryCount;
		}

		V operator[](std::string key){
			return search(key);
		}

		friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &dict){
			out << *dict.tree;
			return out;
		}
};

#endif

