#include <iostream>
#include "Node.h"
#include "LinkedList.h"

int main(){
    Node* temp = nullptr;
    LinkedList list;
    for(int i=0;i<5;i++){
        Node *node = new Node(i,temp);
        list.addNode(node);
        temp = node;
    }
    list.printList();
    return 0;
}