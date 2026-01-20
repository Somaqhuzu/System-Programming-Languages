#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include "Node.h"

template <typename T>
class LinkedList{
    private:
        Node<T>* head{nullptr};
        Node<T>* tail{nullptr};
        mutable int size = 0;
    public:
        LinkedList():head(nullptr),tail(nullptr){};
        explicit LinkedList(Node<T>* h):head(h){
            if(!head){return;}
            else if(!head->getNext()){
                head -> setNext(tail);
                size = 1;
            }else{
                if(head -> getNext()){
                    tail = head -> getNext();
                }
                size = 2;
            }
            
        }

        LinkedList(Node<T>* h,Node<T>* t):head(h),tail(t){
            if(h && t){
                head->setNext(tail);
                size = 2;
            }     
        }
        int getSize(){return size;}
        void incrementSize() {size++;}
        void decrementSize() {size>0?size--:size=0;}
        inline virtual Node<T>* getHead () {return head;}
        inline Node<T>* getTail () {return tail?tail:nullptr;}
        virtual void deleteAndReset(Node<T>* node,int i) {
            if(i<0 || i>size)return;
            else if(i>0){
                Node<T>* _node = getNode(i);
                Node<T>* next_node = _node->getNext();
                Node<T>* prev_node = getNode(i-1);
                prev_node->setNext(nullptr);
                delete _node;
                _node = nullptr;
                prev_node -> setNext(node);
                node->setNext(prev_node);
            }
            else{
                Node<T>* next_head = head->getNext();
                delete head;
                head = node;
                head->setNext(next_head);
            }
        }
        virtual void insertNode(Node<T>* node,int i){
            if(i < 0 || i > size-1) return;
            else if(i == 0){setHead(node);}
            else if(i == size-1){setTail(node);}
            else{
                Node<T>* pointer = getNode(i);
                Node<T>* nextPointer = pointer->getNext();
                pointer->setNext(node);
                node->setNext(nextPointer);
                size++;
            } 
        }

        virtual void removeNode(int i){
            if(i < 0 || i > size-1)return;
            else if( i == 0) removeHead();
            else if( i == size-1) removeTail();
            else{
                Node<T>* pointer = getNode(i);
                Node<T>* prev_pointer = getNode(i-1);
                Node<T>* next_pointer = pointer->getNext();
                prev_pointer->setNext(next_pointer);
                
                pointer->setNext(nullptr);
                delete pointer;
                pointer = nullptr;
            }
            size--;

        }
        virtual void addNode(Node<T>* node){
            if(head==nullptr){
                head = node;
                head -> setNext(nullptr);
                tail = nullptr;
            }
            else{
                if(tail!= nullptr){
                    Node<T>* temp = tail;
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
        virtual void setHead(Node<T>* node){
            node -> setNext(head);
            head = node;
        }

        void replaceHead(Node<T>* node){
            head = node;
        }

        void replaceTail(Node<T>* node){
            tail = node;
        }
        virtual void setTail(Node<T>* node){
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
            }

        }
        virtual void removeTail(){ 
            /*  
                Removes last node on the list
                Efficiency class: O(n)
            */
            Node<T>* n_tail = head;
            while (n_tail->getNext() != tail) {
                n_tail = n_tail->getNext();
            }
            
            n_tail->setNext(nullptr);
            delete tail;
            tail = n_tail;
            
            size--;
            
        }
        virtual void removeHead(){ 
            /*
                Removes first node on the list
                Efficiency class: O(1)
            */
            if(head!=nullptr){
                Node<T>* n_head = head->getNext();
                if(n_head!=nullptr){
                    head->setNext(nullptr);
                }
                delete head;
                head = n_head;
                size--;
            }
            
        }
        Node<T>* getNode(int i){ // Get the i'th Node in the LinkedList Efficiency class : O(n)
            if(i < 0 || i > size-1)return nullptr;
            Node<T>* pointer = head;
            int id = 0;
            while(id != i ){
                pointer = pointer->getNext();
                id = id + 1 ;
            }
            return pointer;
        }
        void printList(){
            Node<T>* temp = head;
            do{
                std::cout<<temp->getData()<<std::endl;
                temp = temp->getNext();
            }while(temp!=nullptr && temp!=head);
        }
}; 

template <typename T>
class DLinkedList:public LinkedList<T>{
    public:
        DLinkedList(): LinkedList<T>(){}

        DLinkedList(DNode<T>* head): LinkedList<T>(static_cast<Node<T>*>(head)){}

        DLinkedList(DNode<T>* head,DNode<T>* tail): LinkedList<T>(static_cast<Node<T>*>(head),static_cast<Node<T>*>(tail)){
            head -> setPrev(tail);
            tail -> setPrev(head);
            static_cast<Node<T>*>(head)->setNext(tail);
            static_cast<Node<T>*>(tail)->setNext(head);
            }

        void insertNode(Node<T>* node,int i){
            if(i < 0 || i > LinkedList<T>::getSize() - 1) return;
            else if(i == 0)DLinkedList<T>::setHead(node);
            else if (i == LinkedList<T>::getSize()-1)DLinkedList::setTail(node);
            else{
                DNode<T>* pointer = dynamic_cast<DNode<T>*>(LinkedList<T>::getNode(i));
                DNode<T>* prevPointer = pointer->getPrev();
                DNode<T>* dnode = dynamic_cast<DNode<T>*>(node);
                dnode->setPrev(prevPointer);
                prevPointer->setNext(node);
                pointer->setPrev(dnode);
                node->setNext(static_cast<Node<T>*>(pointer));
                LinkedList<T>::incrementSize();
                }   
            }

        void setHead(Node<T>* node){
            LinkedList<T>::setHead(node);
            DNode<T>* dnode = dynamic_cast<DNode<T>*>(node);
            Node<T>* tail = LinkedList<T>::getTail();
            dnode->setPrev(dynamic_cast<DNode<T>*>(tail));
            tail->setNext(node);

        }
        void setTail(Node<T>* node){
            if(LinkedList<T>::getSize()==0){setHead(node);}
            else if(LinkedList<T>::getSize() == 1){
                Node<T>* tail = node;
                Node<T>* head = LinkedList<T>::getHead();
                tail->setNext(head);
                static_cast<DNode<T>*>(tail)->setPrev(dynamic_cast<DNode<T>*>(tail));
                head->setNext(tail);
                static_cast<DNode<T>*>(head)->setPrev(dynamic_cast<DNode<T>*>(tail));
            }
            if (LinkedList<T>::getSize()>1){
                DNode<T>* tail = dynamic_cast<DNode<T>*>(LinkedList<T>::getTail());
                DNode<T>* head = dynamic_cast<DNode<T>*>(tail->getNext());
                DNode<T>* n_node = dynamic_cast<DNode<T>*>(node);
                
                n_node->setPrev(tail);
                n_node->setNext(head);
                head->setPrev(n_node);
                
                }
            }
        void deleteAndReset(Node<T>* node,int i){
            if(i <0 || i> LinkedList<T>::getSize())return;
            if(LinkedList<T>::getSize()==1 && i==0){
                node->setNext(nullptr);
                dynamic_cast<DNode<T>*>(node)->setPrev(nullptr);
                LinkedList<T>::replaceHead(node);
            }
            else if(i>0){
                DNode<T>* d_node = dynamic_cast<DNode<T>*>(LinkedList<T>::getNode(i));
                DNode<T>* prev_node = d_node->getPrev();
                Node<T>* next_node = d_node->getNext();
                prev_node -> setNext(nullptr);
                static_cast<DNode<T>*>(next_node) -> setPrev(nullptr);
                delete d_node;
                DNode<T>* n_node = dynamic_cast<DNode<T>*>(node);
                prev_node -> setNext(node);
                n_node->setPrev(prev_node);
                static_cast<DNode<T>*>(next_node)->setPrev(n_node);
                n_node->setNext(next_node);
            }
            else{
                Node<T>* head = LinkedList<T>::getHead();
                DNode<T>* next_head = dynamic_cast<DNode<T>*>(head->getNext());
                DNode<T>* d_node = dynamic_cast<DNode<T>*>(node);
                DNode<T>* prev_head = dynamic_cast<DNode<T>*>(head)->getPrev();

                d_node->setNext(next_head);
                d_node->setPrev(prev_head);
                prev_head->setNext(node);
                next_head->setPrev(d_node);
                delete head;
                this->replaceHead(node);
                }

            }

        void removeHead(){
            if(LinkedList<T>::getHead()==nullptr)return;
            if(LinkedList<T>::getSize()>1){
                DNode<T>* header = dynamic_cast<DNode<T>*>(LinkedList<T>::getHead());
                DNode<T>* nextHead = dynamic_cast<DNode<T>*>(header->getNext());
                DNode<T>* prevHead = header->getPrev();

                nextHead->setNext(static_cast<Node<T>*>(prevHead));
                nextHead->setPrev(prevHead);
                prevHead->setNext(static_cast<Node<T>*>(nextHead));
                prevHead->setPrev(nextHead);

                delete header;
                LinkedList<T>::replaceHead(nextHead);
                LinkedList<T>::decrementSize();
            }
            else{
                this->removeHead();
                }

            }
            void removeTail(){
                if(LinkedList<T>::getTail()!=nullptr){
                    DNode<T>* t_tail = dynamic_cast<DNode<T>*>(LinkedList<T>::getTail());
                    DNode<T>* prevTail = t_tail->getPrev();
                    DNode<T>* nextTail = dynamic_cast<DNode<T>*>(static_cast<Node<T>*>(t_tail)->getNext());
                    prevTail->setNext(nextTail);
                    nextTail->setPrev(prevTail);
                    delete t_tail; 
                    t_tail = nullptr;
                    LinkedList<T>::decrementSize();
                    }
                }
        void removeNode(int i){
            if(i < 0 || i > LinkedList<T>::getSize() - 1) return;
            else if(i == 0){
                removeHead();
            }
            else{
                Node<T>* pp = LinkedList<T>::getNode(i);
                DNode<T>* pointer = dynamic_cast<DNode<T>*> (pp);
                DNode<T>* prevPointer = pointer->getPrev();
                DNode<T>* nextPointer = dynamic_cast<DNode<T>*>(pointer->getNext());
                
                prevPointer -> setNext(static_cast<Node<T>*>(nextPointer));
                nextPointer -> setPrev(prevPointer);

                if(pointer){
                    delete pointer;
                    pointer = nullptr;
                    }
                    
                }

            }

        void addNode(Node<T>* node){
            DNode<T>* dnode = dynamic_cast<DNode<T>*>(node);
            if(LinkedList<T>::getSize() == 0){
                LinkedList<T>::setHead(node);
                dnode->setPrev(nullptr);
                }
            else if(LinkedList<T>::getSize() > 1 ){
                
                DNode<T>* head = dynamic_cast<DNode<T>*>(LinkedList<T>::getHead());
                Node<T>* tail = LinkedList<T>::getTail();
                head->setPrev(dnode);
                dnode->setPrev(dynamic_cast<DNode<T>*>(tail));
                tail -> setNext(node);
                setTail(node);              
                node->setNext(static_cast<Node<T>*>(head));
                
                }
            else{
                setTail(node);
                }
            LinkedList<T>::replaceTail(node);
            LinkedList<T>::incrementSize();
            }

        };
#endif
