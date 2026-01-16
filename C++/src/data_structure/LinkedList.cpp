#include "LinkedList.h"
#include "Node.h"
#include <iostream>


LinkedList::LinkedList(){
    head = nullptr;
    tail = nullptr;
}
LinkedList::LinkedList(Node* h){
    if(h){
        head = h;
        tail = nullptr;
        head -> setNext(tail);
        size = 1;
    }
}

LinkedList::LinkedList(Node* h,Node* t){
    head = h;
    tail = t;
    size = 2;
    head -> setNext(tail);
}

void LinkedList::setHead(Node* node){
    node -> setNext(head);
    head = node;
    size++;
}

void LinkedList::replaceHead(Node* node){
    head = node;
}

void LinkedList::setTail(Node* node){
    if(size == 0){
        setHead(head);
    }
    else if(size==1){//there's only head on ds
        tail = node;
        head -> setNext(tail);

    }
    else{
        tail -> setNext(node);
        tail = node;
        size++;
    }

}

void LinkedList::replaceTail(Node* node){
    tail = node;
}
void LinkedList::deleteAndReset(Node* node,int i){
    if(i<0 || i>size)return;
    else if(i>0){
        Node* _node = getNode(i);
        Node* next_node = _node->getNext();
        Node* prev_node = getNode(i-1);
        prev_node->setNext(nullptr);
        delete _node;
        _node = nullptr;
        prev_node -> setNext(node);
        node->setNext(prev_node);
    }
    else{
        Node* next_head = head->getNext();
        delete head;
        head = node;
        head->setNext(next_head);
    }
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
        }
        delete head;
        head = n_head;
        size--;
    }
    
}

void LinkedList::removeNode(int i){
    if(i < 0 || i > size-1)return;
    else if( i == 0) removeHead();
    else if( i == size-1) removeTail();
    else{
        Node* pointer = getNode(i);
        Node* prev_pointer = getNode(i-1);
        Node* next_pointer = pointer->getNext();
        prev_pointer->setNext(next_pointer);
        
        pointer->setNext(nullptr);
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
        id = id + 1 ;
    }
    return pointer;
}

void LinkedList::printList(){
    Node* temp = head;
    do{
        std::cout<<temp->getID()<<std::endl;
        temp = temp->getNext();
    }while(temp!=nullptr && temp!=head);
}

DLinkedList::DLinkedList(): LinkedList(){}
DLinkedList::DLinkedList(DNode* head): LinkedList(static_cast<Node*>(head)){}
DLinkedList::DLinkedList(DNode* head,DNode* tail): LinkedList(static_cast<Node*>(head),static_cast<Node*>(tail)){
    head -> setPrev(tail);
    tail -> setPrev(head);
    static_cast<Node*>(head)->setNext(tail);
    static_cast<Node*>(tail)->setNext(head);
}

void DLinkedList::insertNode(Node* node,int i){
    if(i < 0 || i > getSize() - 1) return;
    else if(i == 0)DLinkedList::setHead(node);
    else if (i == getSize()-1)DLinkedList::setTail(node);
    else{
        DNode* pointer = dynamic_cast<DNode*>(getNode(i));
        DNode* prevPointer = pointer->getPrev();
        DNode* dnode = dynamic_cast<DNode*>(node);
        dnode->setPrev(prevPointer);
        prevPointer->setNext(node);
        pointer->setPrev(dnode);
        node->setNext(static_cast<Node*>(pointer));
        incrementSize();
    }
    
    
}

void DLinkedList::setHead(Node* node){
    LinkedList::setHead(node);
    DNode* dnode = dynamic_cast<DNode*>(node);
    Node* tail = getTail();
    dnode->setPrev(dynamic_cast<DNode*>(tail));
    tail->setNext(node);

}

void DLinkedList::setTail(Node* node){
    if (getSize()>1){
        DNode* tail = dynamic_cast<DNode*>(getTail());
        DNode* head = dynamic_cast<DNode*>(tail->getNext());
        DNode* n_node = dynamic_cast<DNode*>(node);
        
        n_node->setPrev(tail);
        n_node->setNext(head);
        head->setPrev(n_node);
        
    }
    LinkedList::setTail(node);

}

void DLinkedList::deleteAndReset(Node* node,int i){
    if(i <0 || i> getSize())return;
    if(getSize()==1 && i==0){
        node->setNext(nullptr);
        dynamic_cast<DNode*>(node)->setPrev(nullptr);
        replaceHead(node);
    }
    else if(i>0){
        DNode* d_node = dynamic_cast<DNode*>(getNode(i));
        DNode* prev_node = d_node->getPrev();
        Node* next_node = d_node->getNext();
        prev_node -> setNext(nullptr);
        static_cast<DNode*>(next_node) -> setPrev(nullptr);
        delete d_node;
        DNode* n_node = dynamic_cast<DNode*>(node);
        prev_node -> setNext(node);
        n_node->setPrev(prev_node);
        static_cast<DNode*>(next_node)->setPrev(n_node);
        n_node->setNext(next_node);
    }
    else{
        Node* head = getHead();
        DNode* next_head = dynamic_cast<DNode*>(head->getNext());
        DNode* d_node = dynamic_cast<DNode*>(node);
        DNode* prev_head = dynamic_cast<DNode*>(head)->getPrev();

        d_node->setNext(next_head);
        d_node->setPrev(prev_head);
        prev_head->setNext(node);
        next_head->setPrev(d_node);
        delete head;
        replaceHead(node);
    }

}

void DLinkedList::removeHead(){
    if(getHead()==nullptr)return;
    if(getSize()>1){
        DNode* header = dynamic_cast<DNode*>(getHead());
        DNode* nextHead = dynamic_cast<DNode*>(header->getNext());
        DNode* prevHead = header->getPrev();

        nextHead->setNext(static_cast<Node*>(prevHead));
        nextHead->setPrev(prevHead);
        prevHead->setNext(static_cast<Node*>(nextHead));
        prevHead->setPrev(nextHead);

        delete header;
        replaceHead(nextHead);
        decrementSize();
        

    }
    else{
        LinkedList::removeHead();
    }

}

void DLinkedList::removeTail(){
    if(getTail()!=nullptr){
        DNode* t_tail = dynamic_cast<DNode*>(getTail());
        DNode* prevTail = t_tail->getPrev();
        DNode* nextTail = dynamic_cast<DNode*>(static_cast<Node*>(t_tail)->getNext());
        prevTail->setNext(nextTail);
        nextTail->setPrev(prevTail);
        delete t_tail; 
        t_tail = nullptr;
        decrementSize();
    }
}

void DLinkedList::removeNode(int i){
    if(i < 0 || i > getSize() - 1) return;
    else if(i == 0){
        removeHead();
    }
    else{
        Node* pp = getNode(i);
        DNode* pointer = dynamic_cast<DNode*> (pp);
        DNode* prevPointer = pointer->getPrev();
        DNode* nextPointer = dynamic_cast<DNode*>(pointer->getNext());
        
        prevPointer -> setNext(static_cast<Node*>(nextPointer));
        nextPointer -> setPrev(prevPointer);

        if(pointer){
            delete pointer;
            pointer = nullptr;
        }
        
    }

}

void DLinkedList::addNode(Node* node){
    DNode* dnode = dynamic_cast<DNode*>(node);
    if(getSize() == 0){
        setHead(node);
        dnode->setPrev(nullptr);
    }
    else if(getSize() > 1 ){
        DNode* head = dynamic_cast<DNode*>(getHead());
        Node* tail = getTail();

        head->setPrev(dnode);
        dnode->setPrev(dynamic_cast<DNode*>(tail));
        LinkedList::setTail(node);
        node->setNext(static_cast<Node*>(head));
        incrementSize();
    }
    else{
        setTail(node);
    }
}
   

