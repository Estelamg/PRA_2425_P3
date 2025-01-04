#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"
#include "/home/emargar1/PRA/P1/PRA_2425_P1/ListLinked.h" 

template <typename V>
class HashTable : public Dict<V> {
	private:
		int n;		//nº elementos almacenados
		int max; 	//nº cubetas
		ListLinked<TableEntry<V>>* table;
		
		int h(std::string key) const{
			int suma = 0;
			for(char c : key){
				suma += static_cast<int>(c);
			}

			return suma % max;
		}
			         
	public:
		HashTable(int size) : n(0), max(size){
			table = new ListLinked<TableEntry<V>>[max];
		}

		~HashTable(){
			delete[] table;
		}

		int capacity(){
			return max;
		}

		void insert(std::string key, V value) override{
			int index = h(key);
			for(int i=0; i < table[index].size(); ++i){
				if(table[index].get(i).key == key){
					throw std::runtime_error("La clave ya existe");
				}
			}

			TableEntry<V> entry(key, value);
			table[index].append(entry);
			n++;
		}

		V search(std::string key) const override{
			int index = h(key);
			for(int i=0; i < table[index].size(); ++i){
				if(table[index].get(i).key == key){
					return table[index].get(i).value;
				}
			}

			throw std::runtime_error("No se ha encontrado la clave");
		}

		V remove(std::string key) override{
			int index = h(key);
			for(int i=0; i < table[index].size(); ++i){
				if(table[index].get(i).key == key){
					V value = table[index].get(i).value;
					table[index].remove(i);
					n--;
					return value;
				}
			}
			
			throw std::runtime_error("No se ha encontrado la clave");
		}

		int entries() const override{
			return n;
		}

		friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
			for(int i=0; i < th.max; i++){
				out << "Cubeta " << i << ": ";
				for(int j=0; j < th.table[i].size(); ++j){
					out << th.table[i].get(j) << " ";
				}
				out << std::endl;
			}

			return out;
		}

		V operator[](std::string key){
			return search(key);
		}

};

#endif
 
