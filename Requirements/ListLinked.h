#include <ostream>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {

    private:
 
        Node<T>* first;
	int n;

    public:

        ListLinked() : first(nullptr), n(0) {}
		
	~ListLinked(){
		while (first != nullptr){
			Node<T>* aux = first->next;
			delete first;
			first = aux;
		}
	}

    void insert(int pos, T e) override {
        if (pos < 0 || pos > n) {
            throw std::out_of_range("Índice fuera de rango");
        }
        if (pos == 0) {
            first = new Node<T>(e, first);
        } else {
            Node<T>* prev = first;
            for (int i = 1; i < pos; i++) {
                prev = prev->next;
            }
            prev->next = new Node<T>(e, prev->next);
        }
        n++;
    }

    void append(T e) override {
        insert(n, e);
    }

    void prepend(T e) override {
        insert(0, e);
    }

    T remove(int pos) override {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Índice fuera de rango");
        }
        Node<T>* to_delete;
        T data;
        if (pos == 0) {
            to_delete = first;
            first = first->next;
        } else {
            Node<T>* prev = first;
            for (int i = 1; i < pos; i++) {
                prev = prev->next;
            }
            to_delete = prev->next;
            prev->next = to_delete->next;
        }
        data = to_delete->data;
        delete to_delete;
        n--;
        return data;
    }

    T get(int pos) override {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Índice fuera de rango");
        }
        Node<T>* current = first;
        for (int i = 0; i < pos; ++i) {
            current = current->next;
        }
        return current->data;
    }

    int search(T e) override {
        Node<T>* current = first;
        for (int i = 0; i < n; i++) {
            if (current->data == e) {
                return i;
            }
            current = current->next;
        }
        return -1;
    }

    bool empty() override {
        return n == 0;
    }

    int size() override {
        return n;
    }

	T operator[](int pos){
		if(pos < 0 || pos >= n){
			throw std::out_of_range("Indice fuera de rango");
		}

		Node<T>* current = first; // Comenzar desde el primer nodo
        	for (int i = 0; i < pos; ++i) {
            		current = current->next; // Moverse al siguiente nodo
        	}	

        	return current->data;
	}

	friend std::ostream& operator<<(std::ostream &out, const ListLinked<T> &list){
		Node<T>* current = list.first; // Comenzar desde el primer nodo
        	out << "["; // Comenzar con un corchete

        	while (current != nullptr) {
            		out << current->data; // Imprimir el dato del nodo

            		current = current->next; // Moverse al siguiente nodo
            		if (current != nullptr) {
                		out << ", "; // Agregar una coma si no es el último nodo
            		}
        	}
        
        	out << "]"; // Cerrar el corchete
        	return out;
	}
	
};

