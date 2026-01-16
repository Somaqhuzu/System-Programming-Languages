#include "Node.h"

Node::Node(int id):id(id){};
Node::Node(int id,Node* n):id(id),next(n){}
void Node::setNext(Node* n){
    next = n;
}

DNode::DNode(int id):Node(id){}
DNode::DNode(int id,DNode* next,DNode* prev):Node(id,next),prev(prev){}
void DNode::setPrev(DNode* node){prev=node;}


