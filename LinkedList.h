//
// Created by Nate Lampros on 10/1/21.
//

#ifndef INC_235LAB3_LINKEDLIST_H
#define INC_235LAB3_LINKEDLIST_H
#include "LinkedListInterface.h"
#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;

template<typename T>
class LinkedList : public LinkedListInterface<T>{

private:
    struct Node
    {
        T data;
        Node* next;
        Node(const T& d, Node* n) : data(d), next(n) {}
        ~Node() = default;
    };
    Node* head;

public:
    LinkedList() : head(NULL) {}
    ~LinkedList() {clear();}
    /** Copy Constructor */
    LinkedList<T>(const LinkedList<T>& copyList) : head(NULL) {
        // Copy (append) copyList to *this
        Node* cptr = copyList.head;
        Node** nptr = &head;			// point to head
        while (cptr != NULL) {
            // append next node to end of copyList
            *nptr = new Node(cptr->data, NULL);
            // update pointer to next of appended node
            nptr = &((*nptr)->next);
            cptr = cptr->next;
        }
    }

    LinkedList& operator=(const LinkedList& other){
        LinkedList<T> temp(other);
        std::swap(temp.head, head);
        return *this;
    }

    /** Insert Node(value) at beginning of linked list */
    void push_front(const T& value){
        head = new Node(value, head);
        return;
    }

    /** Remove Node at beginning of linked list */
    void pop_front(){
        if (head == NULL){
            return;
        }
        else {
            Node* temp = head;
            head = head->next;

            delete temp;
        }
    }

    /** Return reference to value of Node at beginning of linked list */
    T& front(){
        return head->data; ///TODO IS THIS CORRECT
        //return head;
    }

    /** Return true if linked list size == 0 */
    bool empty() const{
        if (head == NULL){
            return true;
        }
        else{
            return false;
        }
    }

    /** Remove all Nodes with value from linked list */
    void remove(const T& value){
        // Initialize current
        Node* current = head;
        Node* temp = head;

        while (current != NULL){
            if (current->data == value){
                if (current == head){
                    temp = current->next;
                    delete current;
                    current = temp;
                    head = current;
                }
                else {
                    temp->next = current->next;
                    delete current;
                    current = temp->next;
                }
            }
            else {
                temp = current;
                current = current->next;
            }
        }
    }

    /** Remove all Nodes from linked list */
    void clear(){

        while (head != NULL){
            Node* temp = head;
            head = temp->next;
            delete temp;
        }
        head = NULL;
    }

    /** Reverse Nodes in linked list */
    void reverse(){
        // Initialize current, previous & next ptrs
        Node* current = head;
        Node *prev = NULL;
        Node *next = NULL;

        while (current != NULL) {
            // Store next
            next = current->next;
            // Reverse current node's pointer
            current->next = prev;
            // Move pointers one position ahead.
            prev = current;
            current = next;
        }
        head = prev;
    }

    /** Return the number of nodes in the linked list */
    size_t size() const{
        // Initialize counter and current
        int counter = 0;
        Node* current = head;

        while (current != NULL){
            current = current->next;
            counter++;
        }
        return counter;
    }

    /** Return contents of Linked List as a string */
    std::string toString() const{
            ostringstream os;
            Node* nextNode = head;

            while (nextNode != NULL)
            {
                os << " ";
                Node currentNode = (*nextNode);
                //get data at node pointed to by nextNode
                os << currentNode.data;
                //set nextNode to the next value in the node it is point to
                nextNode = currentNode.next;
        }
    }

    /**Friend operator*/
    friend ostream& operator<<(ostream& os, LinkedList& ll)
    {
        Node* node_ptr = ll.head;
        while (node_ptr != NULL)
        {
            os << node_ptr->data << (node_ptr->next != NULL ? " " : "");
            node_ptr = node_ptr->next;
        }
        return os;
    }

    /** ITERATOR CLASS */
    class Iterator
    {
    private:
        Node* nptr;
    public:
        Iterator(Node* np) : nptr(np) {}
        ~Iterator() = default;

        bool operator==(const Iterator& rhs) { return this->nptr == rhs.nptr; }
        bool operator!=(const Iterator& rhs) { return this->nptr != rhs.nptr; }
        T& operator*()
        {
            if (nptr == NULL) throw string("Invalid dereference!!");
            return nptr->data;
        }
        Iterator& operator++() { nptr = nptr->next; return *this; }
        Iterator operator++(int)
        {
            Iterator temp(*this);
            operator++();
            return temp;
        }
        Node* GetNode(){
            return nptr;
        }
    };
    Iterator begin() { return Iterator(this->head); }

    Iterator end() { return Iterator(NULL); }

    Iterator find(Iterator first, Iterator last, const T& value){
        Iterator iterator = first;
        int counter = 0;
        while (iterator != last){
            if (*iterator == value){
                return iterator;
                ++counter;
            }
            ++iterator;
        }

        if(counter == 0){
            throw string ("Not Found");
        }
    }

    void insert_before(Iterator position, const T& value){
        if (position.GetNode() == NULL) {
            throw string("Not Found");
        }

        Iterator iterator1 = begin();
        Iterator iterator2 = begin();

        iterator2++;

        if (iterator1 == position){
            push_front(value);
            return;
        }
        while (iterator2 != position){
            ++iterator1;
            ++iterator2;
        }

        iterator1.GetNode()->next = new Node(value, iterator2.GetNode());
    }

    void insert_after(Iterator position, const T& value){
        if (position.GetNode() == NULL) {
            throw string("Not Found");
        }

        Node* newNode = new Node(value, position.GetNode()->next);
        position.GetNode()->next = newNode;
    }

    void erase(Iterator position){
        if (position.GetNode() == NULL){
            throw string ("Not Found");
        }

        Iterator iterator1 = begin();
        Iterator iterator2 = begin();
        iterator2++;

        if (position == begin()){
            pop_front();
            return;
        }

        while (iterator2 != position){
            ++iterator1;
            ++iterator2;
        }

        iterator1.GetNode()->next = iterator2.GetNode()->next;
        delete iterator2.GetNode();
    }

    void replace(Iterator first, Iterator last, const T& old_value, const T& new_value){
        Iterator iterator = first;

        while(iterator != last){
            if (*iterator == old_value){
                *iterator = new_value;
            }
            ++iterator;
        }
    }


};
#endif //INC_235LAB3_LINKEDLIST_H
