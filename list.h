// =================================================================
//
// File: list.h
// Author: Sven Chávez García 
// Date: 10-05-22
//
// =================================================================
#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <string>
#include <sstream>
#include "exception.h"
#include "header.h"

template <class T> class DoubleLinkedList;

// =================================================================
// Definition of the Node class
// =================================================================
template <class T>
class Node {
private:
	Node(T);
	Node(T, Node<T>*, Node<T>*);

	T	    	value;
	Node<T> *previous, *next;

	friend class DoubleLinkedList<T>;
};

// =================================================================
// Constructor. Initializes the value of the node. The variable next
// is initialized to null.
//
// @param val, stored value in the node.
// =================================================================
template <class T>
Node<T>::Node(T val) : value(val), previous(NULL), next(NULL) {
}

// =================================================================
// Constructor. Initializes both instance variables.
//
// @param val, stored value in the node.
// @param nxt, the next node.
// =================================================================
template <class T>
Node<T>::Node(T val, Node *prev, Node* nxt)
	: value(val), previous(prev), next(nxt) {
}

// =================================================================
// Definition of the DoubleLinkedList class
// =================================================================
template <class T>
class DoubleLinkedList {
private:
	Node<T> *head;
	uint 		size;

public:
	DoubleLinkedList();
	~DoubleLinkedList();

	uint  length() const;
	bool empty() const;
	bool contains(T) const;
	void clear();
	std::string toString() const;

	T front() const;
	T last() const;
	T before(T) const;
	T after(T) const;

	void push_front(T);
	void push_back(T);
	void insert_before(T, T);
	void insert_after(T, T);

	T    pop_front();
	T 	 pop_back();
};

// =================================================================
// Constructor. Initializes both instance variables to zero.
// =================================================================
template <class T>
DoubleLinkedList<T>::DoubleLinkedList() :head(NULL), size(0) {
}

// =================================================================
// Destructor. Remove all items from the DoubleLinkedList.
// =================================================================
template <class T>
DoubleLinkedList<T>::~DoubleLinkedList() {
	clear();
}

// =================================================================
// Returns if the DoubleLinkedList is empty or not
//
// @returns true if the DoubleLinkedList is empty, false otherwise.
// =================================================================
template <class T>
bool DoubleLinkedList<T>::empty() const {
	return (head == NULL);
}

// =================================================================
// Returns the number of items in the DoubleLinkedList.
//
// @returns size, the number of items in the DoubleLinkedList.
// =================================================================
template <class T>
uint DoubleLinkedList<T>::length() const {
	return size;
}

// =================================================================
// Determines if an item is in the DoubleLinkedList.
//
// @returns true if val is in the DoubleLinkedList, false otherwise
// =================================================================
template <class T>
bool DoubleLinkedList<T>::contains(T val) const {
	Node<T> *p;

	p = head;
	while (p != NULL) {
		if(p->value == val) {
			return true;
		}
		p = p->next;
	}
	return false;
}

// =================================================================
// Remove all items from the DoubleLinkedList.
// =================================================================
template <class T>
void DoubleLinkedList<T>::clear() {
	Node<T> *p, *q;

	p = head;
	while (p != NULL){
		q = p->next;
		delete p;
		p = q;
	}

	head = NULL;
	size = 0;
}

// =================================================================
// String representation of the elements in the DoubleLinkedList.
//
// @returns a string containing all the elements of the DoubleLinkedList.
// =================================================================
template <class T>
std::string DoubleLinkedList<T>::toString() const {
	std::stringstream aux;
	Node<T> *p;

	p = head;
	aux << "[";
	while (p != NULL) {
		aux << p->value;
		if (p->next != NULL) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

// =================================================================
// Returns the first item in the DoubleLinkedList.
//
// @returns the object T at the beginning of the DoubleLinkedList.
// @throws NoSuchElement, if the DoubleLinkedList is empty.
// =================================================================
template <class T>
T DoubleLinkedList<T>::front() const {
	if (empty()) {
		throw NoSuchElement();
	}

	return head->value;
}

// =================================================================
// Returns the last item in the DoubleLinkedList.
//
// @returns the object T at the end of the DoubleLinkedList.
// @throws NoSuchElement, if the DoubleLinkedList is empty.
// =================================================================
template <class T>
T DoubleLinkedList<T>::last() const {
	Node<T> *p;

	if (empty()) {
		throw NoSuchElement();
	}

	p = head;
	while (p->next != NULL) {
		p = p->next;
	}
	return p->value;
}

// =================================================================
// Returns the value before the first occurrence if certain value.
//
// @throws NoSuchelement, if val is not on the list.
// =================================================================
template <class T>
T DoubleLinkedList<T>::before(T val) const {
	Node<T> *cNode;
	cNode = head; // empezamos desde la cabeza 

	for (int i = 0; i < size; i++){ // se recorre la lista 
		if (cNode->value == val){ // si el valor es igual al nodo actual...
			if (cNode->previous == NULL) // se checa si el apuntador es el head
      		{
        		throw NoSuchElement(); // si si entonces no hay elemento anterior
      		}
    	return cNode->previous->value; // se devuelve el valor anterior al valor ingresado
		}
    cNode = cNode->next; // se recorre la lista
	}
	throw NoSuchElement();
	return val;
	
}

// =================================================================
// Returns the value after the first occurrence of certain value.
//
// @throws NoSuchelement, if val is not on the list.
// =================================================================
template <class T>
T DoubleLinkedList<T>::after(T val) const {
	Node<T> *cNode; // se crea un nodo de recorrido
	cNode = head; // se iguala a la cabeza

	for (int i = 0; i < size; i++){ // se recorre la lista 
		if (cNode->value == val){ // si se encuentra el valor 
      		if (cNode->next == NULL){ // si es el final de la lista
        		throw NoSuchElement(); // no hay elementos
      		}
      		return cNode->next->value;// si si se devuelve el valor del siguiente nodo 
    	}
    	cNode = cNode->next; // se recorre la lista 
	}

	throw NoSuchElement();
	return val;
}

// =================================================================
// Add an item to the beginning of the DoubleLinkedList. Increase the size of
// the DoubleLinkedList.
// =================================================================
template <class T>
void DoubleLinkedList<T>::push_front(T val) {
	Node<T> *q, *p;

	q = new Node<T>(val);
	if (head == NULL) {
		q->next = NULL;
		q->previous = NULL;
	} else {
		p = head;

		q->next = p; // q->next = head;
		q->previous = NULL;

		p->previous = q; //head->previous = q;
	}
	head = q;
	size++;
}

// =================================================================
// Add an item to the end of the DoubleLinkedList. Increase the size of
// the DoubleLinkedList.
// =================================================================
template <class T>
void DoubleLinkedList<T>::push_back(T val) {
	Node<T> *p, *q;

	if (empty()) {
		push_front(val);
		return;
	}

	p = head;
	while (p->next != NULL) {
		p = p->next;
	}

	q = new Node<T>(val);
	q->next = p->next;
	q->previous = p;

	p->next = q;
	size++;
}

// =================================================================
// Insert an element before the first occurrence of a certain value.
//
// @throws NoSuchelement, if lookingFor is not on the list.
// =================================================================
template <class T>
void DoubleLinkedList<T>::insert_before(T lookingFor, T newVal) {
	if (empty()){
    push_front(newVal); // se checa si la lista esta vacia 
    return;
  }

  Node<T> *cNode, *pNode, *nNode; // se crean los apuntadores con los que se va a recorrer la lista, siendo el actual el previo y el nuevo nodo
  cNode = head; // se iguala al primer apuntador 

  for (int i = 0; i < size; i++){ // se recorre la lista 
    if (cNode->value == lookingFor){ // si es igual al valor que estamos buscando definido por el apuntador... 
      nNode = new Node<T>(newVal); // se genera un nuevo nodo con el nuevo valor 

      if (cNode->previous == NULL){ // si el valor se encuentra en la cabeza y por lo tanto no hay previous entonces... 
        nNode->next = cNode; // el nuevo nodo se iguala al apuntador de head
        cNode->previous = nNode; // el previo se cNode se iguala al apuntador del nuevo nodo
        head = nNode; // y finalmente se iguala head al primer valor que es nuestro primer nodo 
        size++; // se aumenta el tamaño
        return;
      }

      pNode = cNode->previous; // si se encuentra en otra posicion sigue una logica similar 

      pNode->next = nNode; // el apuntador del nodo previo apunta al nuevo nodo 
      cNode->previous = nNode; // el apuntador previo del nodo acual se iguala al nuevo nodo 
      nNode->previous = pNode; // el previo del nuevo nodo se iguala al  nodo previo 
      nNode->next = cNode; //y el siguiente del nodo se iguala al nodo actual para mantener la lista

      size++;// se aumenta el tamanio 
      return;
    }
    cNode = cNode->next; // si no se cumple la condicion solo sigue recorriendo la lista
  }
  throw NoSuchElement(); // en caso de que se recorra la lista y no exista el elemento marca error 
}

// =================================================================
// Insert an element after the first occurrence of a certain value.
//
// @throws NoSuchelement, if lookingFor is not on the list.
// =================================================================
template <class T>
void DoubleLinkedList<T>::insert_after(T lookingFor, T newVal) {
	 if (empty()){
    push_front(newVal);// se checa si la lista esta vacia
    return;
  }

  Node<T> *cNode, *nxtNode, *nNode;// se crean los apuntadores con los que se va a recorrer la lista, siendo el actual el previo y el nuevo nodo
  cNode = head; // se iguala al primer apuntador

  for (int i = 0; i < size; i++){// se recorre la lista 
    if (cNode->value == lookingFor){ // si es igual al valor que estamos buscando definido por el apuntador... 
      nNode = new Node<T>(newVal); // se genera un nuevo nodo con el nuevo valor

      if (cNode->next == NULL){ // si el valor se encuentra en la cabeza y por lo tanto no hay previous entonces...
        nNode->previous = cNode; //el previo apuntador del nuevo nodo se iguala al nodo actual
        cNode->next = nNode; // el apuntador siguiente del nodo actual se iguala al nuevo nodo	
        size++;
        return;
      }

      nxtNode = cNode->next; // el nodo siguiente se iguala a el apuntador del nodo actual

      nxtNode->previous = nNode; // el previo del nodo siguiente se iguala al nuevo nodo
      cNode->next = nNode; // el siguiente del nodo se iguala al nuevo nodo 
      nNode->previous = cNode; // el previo del nuevo nodo se iguala al nodo actual 
      nNode->next = nxtNode; // y el siguiente del nuevo nodo se iguala al nodo siguiente

      size++;
      return;
    }
    cNode = cNode->next; //  se recorre la lista a traves de apuntadores 
  }
  throw NoSuchElement();// en caso de que se recorra la lista y no exista el elemento marca error

}

// =================================================================
// Delete the item at the beginning of the DoubleLinkedList.
//
// @returns the element that was at the beginning of the DoubleLinkedList.
// @throws NoSuchElement if the DoubleLinkedList is empty
// =================================================================
template <class T>
T DoubleLinkedList<T>::pop_front() {
	T val;
	Node<T> *p, *q;

	if (empty()) {
		throw NoSuchElement();
	}

	p = head;

	if (size == 1) {
		head = p->next;
	} else {
		q = p->next;

		q->previous = NULL;
		head = q;
	}

	val = p->value;

	delete p;
	size--;

	return val;
}

// =================================================================
// Delete the item at the end of the DoubleLinkedList.
//
// @returns the element that was at the end of the DoubleLinkedList.
// @throws NoSuchElement if the DoubleLinkedList is empty
// =================================================================
template <class T>
T DoubleLinkedList<T>::pop_back() {
	Node<T> *p, *q;
	T val;

	if (empty()) {
		throw NoSuchElement();
	}

	if (size == 1) {
		return pop_front();
	}

	p = head;
	while (p->next != NULL) {
		q = p;
		p = p->next;
	}
	q = p->previous;

	q->next = p->next;

	val = p->value;
	delete p;
	size--;

	return val;
}

#endif /* DoubleLinkedList_H */
