#ifndef NODE_H
#define NODE_H

template<typename T>
class Node{
    private:
        mutable Node<T>* next{nullptr};
        T data;
    public:
        virtual ~Node<T>()=default;
        explicit Node(T data):data(data){};
        Node(T dd,Node<T>* nn):data(dd),next(nn){};
        inline virtual Node* getNext() const{return next;}
        void setNext(Node* nn) const {next = nn;}
        inline T getData() const{return data;}

};


template <typename T>
class DNode: public Node<T>{
     private:
        mutable DNode<T>* prev;
    public:
        ~DNode()= default;
        explicit DNode(T data):Node<T>(data){}
        explicit DNode(T data,DNode<T>* next,DNode<T>* prev):Node<T>(data,next),prev(prev){};
        inline DNode<T>* getPrev () const{return prev;};
        void setPrev(DNode<T>* new_prev) const {prev = new_prev; }
};

#endif