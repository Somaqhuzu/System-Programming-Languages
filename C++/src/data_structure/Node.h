#ifndef NODE_H
#define NODE_H

class Node{
    private:
        int id;
        mutable Node* next;
    public:
        virtual ~Node() = default;
        explicit Node(int id);
        explicit Node(int id,Node* next);
        inline virtual Node* getNext() const{return next;};
        int getID(){return id;}
        void setNext(Node* next);

};

class DNode: public Node{
     private:
        mutable DNode* prev;
    public:
        ~DNode()= default;
        explicit DNode(int id);
        explicit DNode(int id,DNode* next,DNode* prev);
        inline DNode* getPrev () const{return prev;};
        void setPrev(DNode* new_prev);
};
#endif