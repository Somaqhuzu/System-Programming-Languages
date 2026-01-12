#include "LinkedList.h"
#include "Node.h"
#include <iostream>


LinkedList::LinkedList(){
    head = nullptr;
    tail = nullptr;
}
LinkedList::LinkedList(Node* h){
    size = 1;
    head = h;
    tail = nullptr;
    head -> setNext(tail);
}

void LinkedList::setHead(Node* node){
    node -> setNext(head);
    head = node;
    size++;
}

void LinkedList::setTail(Node* node){
    tail -> setNext(node);
    tail = node;
    size++;
}
void LinkedList::addNode(Node* node){
    if(head==nullptr){
        head = node;
        head -> setNext(nullptr);
        tail = nullptr;
    }
    else{
        if(tail!= nullptr){
            Node* temp = tail;
            tail = node;
            temp -> setNext(tail);
            tail -> setNext(nullptr);
        }
        else{
            tail = node;
            head->setNext(tail);
            tail->setNext(nullptr);
        }
 
    }
    size++;
}

void LinkedList::removeTail(){ 
    /*  
        Removes last node on the list
        Efficiency class: O(n)
    */
    Node* n_tail = head;
    while (n_tail->getNext() != tail) {
        n_tail = n_tail->getNext();
    }
    
    n_tail->setNext(nullptr);
    delete tail;
    tail = n_tail;
    
    size--;
    
}
void LinkedList::removeHead(){ 
    /*
        Removes first node on the list
        Efficiency class: O(1)
    */
    if(head!=nullptr){
        Node* n_head = head->getNext();
        if(n_head!=nullptr){
            head->setNext(nullptr);
            delete head;
            head = n_head;
        }
    }
    size--;
}

void LinkedList::removeNode(int i){
    if(i < 0 || i > size-1)return;
    else if( i == 0) removeHead();
    else if( i == size-1) removeTail();
    else{
        Node* node = getNode(i);
        Node* pointer = head->getNext();
        Node* prevPointer = head ;
        Node* nextPointer = pointer->getNext();
        while(pointer != nullptr && pointer != node){
            prevPointer = pointer;
            pointer = pointer->getNext();
            nextPointer = pointer->getNext();
        }

        prevPointer->setNext(nextPointer);
        delete pointer;
        pointer = nullptr;
    }
    size--;

}

void LinkedList::insertNode(Node* node,int i){
    if(i < 0 || i > size-1) return;
    else if(i == 0){setHead(node);}
    else if(i == size-1){setTail(node);}
    else{
        Node* pointer = getNode(i);
        Node* nextPointer = pointer->getNext();
        pointer->setNext(node);
        node->setNext(nextPointer);
        size++;
    } 
}

Node* LinkedList::getNode(int i){ // Get the i'th Node in the LinkedList Efficiency class : O(n)
    if(i < 0 || i > size-1)return nullptr;
    Node* pointer = head;
    int id = 0;
    while(id != i ){
        pointer = pointer->getNext();
        std::cout<<pointer<<std::endl;
        id = id + 1 ;
    }
    return pointer;
}

void LinkedList::printList(){
    Node* temp = head;
    while(temp!=nullptr){
        std::cout<<temp->getID()<<std::endl;
        temp = temp->getNext();
    }
}

