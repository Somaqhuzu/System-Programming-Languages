#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include "Node.h"


class LinkedList{
    private:
        mutable Node* head;
        mutable Node* tail;
        mutable int size = 0;
    public:
        LinkedList();
        LinkedList(Node* h);
        int getSize(){return size;}
        Node* getHead () const{return head;};
        Node* getTail () const{return tail;};
        virtual void insertNode(Node* node,int i);
        virtual void removeNode(int i);
        virtual void addNode(Node* node);
        virtual void setHead(Node* node);
        virtual void setTail(Node* node);
        virtual void removeTail(); //remove last node on the list;
        virtual void removeHead();

        Node* getNode(int i);
        void printList();
};

#endif