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
        LinkedList(Node* h,Node* t);
        int getSize(){return size;}
        void incrementSize(){size++;}
        void decrementSize(){size>0?size--:size=0;}
        inline Node* getHead () const{return head?head:nullptr;}
        inline Node* getTail () const{return tail?tail:nullptr;}
        virtual void deleteAndReset(Node* node,int i);
        virtual void insertNode(Node* node,int i);
        virtual void removeNode(int i);
        virtual void addNode(Node* node);
        virtual void setHead(Node* node);
        void replaceHead(Node* node);
        void replaceTail(Node* node);
        virtual void setTail(Node* node);
        virtual void removeTail(); //remove last node on the list;
        virtual void removeHead();
        Node* getNode(int i);
        void printList();
};


class DLinkedList:public LinkedList{
    public:
        DLinkedList();
        DLinkedList(DNode* head);
        DLinkedList(DNode* head,DNode* tail);
        void insertNode(Node* node,int i);
        void removeNode(int i);
        void addNode(Node* node);
        void setHead(Node* node);
        void setTail(Node* node);
        void deleteAndReset(Node* node, int i);
        void removeTail(); //remove last node on the list;
        void removeHead();
};

#endif