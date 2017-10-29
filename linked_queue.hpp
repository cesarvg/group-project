#ifndef LINKED_QUEUE_HPP_
#define LINKED_QUEUE_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <initializer_list>
#include "ics_exceptions.hpp"


namespace ics {


    template<class T>
    class LinkedQueue {
    public:
        //Destructor/Constructors
        ~LinkedQueue();

        LinkedQueue();

        LinkedQueue(const LinkedQueue<T> &to_copy);

        explicit LinkedQueue(const std::initializer_list<T> &il);

        //Iterable class must support "for-each" loop: .begin()/.end() and prefix ++ on returned result
        template<class Iterable>
        explicit LinkedQueue(const Iterable &i);


        //Queries
        bool empty() const;

        int size() const;

        T &peek() const;

        std::string str() const; //supplies useful debugging information; contrast to operator <<


        //Commands
        int enqueue(const T &element);

        T dequeue();

        void clear();

        //Iterable class must support "for-each" loop: .begin()/.end() and prefix ++ on returned result
        template<class Iterable>
        int enqueue_all(const Iterable &i);


        //Operators
        LinkedQueue<T> &operator=(const LinkedQueue<T> &rhs);

        bool operator==(const LinkedQueue<T> &rhs) const;

        bool operator!=(const LinkedQueue<T> &rhs) const;

        template<class T2>
        friend std::ostream &operator<<(std::ostream &outs, const LinkedQueue<T2> &q);


    private:
        class LN;

    public:
        class Iterator {
        public:
            //Private constructor called in begin/end, which are friends of LinkedQueue<T>
            ~Iterator();

            T erase();

            std::string str() const;

            LinkedQueue<T>::Iterator &operator++();

            LinkedQueue<T>::Iterator operator++(int);

            bool operator==(const LinkedQueue<T>::Iterator &rhs) const;

            bool operator!=(const LinkedQueue<T>::Iterator &rhs) const;

            T &operator*() const;

            T *operator->() const;

            friend std::ostream &operator<<(std::ostream &outs, const LinkedQueue<T>::Iterator &i) {
                outs << i.str(); //Use the same meaning as the debugging .str() method
                return outs;
            }

            friend Iterator LinkedQueue<T>::begin() const;

            friend Iterator LinkedQueue<T>::end() const;

        private:
            //If can_erase is false, current indexes the "next" value (must ++ to reach it)
            LN *prev = nullptr;  //if nullptr, current at front of list
            LN *current;         //current == prev->next (if prev != nullptr)
            LinkedQueue<T> *ref_queue;
            int expected_mod_count;
            bool can_erase = true;

            //Called in friends begin/end
            Iterator(LinkedQueue<T> *iterate_over, LN *initial);
        };


        Iterator begin() const;

        Iterator end() const;


    private:
        class LN {
        public:
            LN() {}

            LN(const LN &ln) : value(ln.value), next(ln.next) {}

            LN(T v, LN *n = nullptr) : value(v), next(n) {}

            T value;
            LN *next = nullptr;
        };


        LN *front = nullptr;
        LN *rear = nullptr;
        int used = 0;            //Cache count for nodes in linked list
        int mod_count = 0;            //Alllows sensing for concurrent modification

        //Helper methods
        void delete_list(LN *&front);  //Deallocate all LNs, and set front's argument to nullptr;
    };





////////////////////////////////////////////////////////////////////////////////
//
//LinkedQueue class and related definitions

//Destructor/Constructors

    template<class T>
    LinkedQueue<T>::~LinkedQueue() {
        delete_list(front);
        //delete[] LinkedQueue;//deletelist
    }


    template<class T>
    LinkedQueue<T>::LinkedQueue() {

        //queue = new LinkedQueue;
    }

    template<class T>
    LinkedQueue<T>::LinkedQueue(const LinkedQueue<T> &to_copy)
//    : used(to_copy.used)
    {
//    {
//        queue = new T[used];
//        front = 0;
//        rear = to_copy.size();
//        for (int i = 0; i < rear; ++i)
//            queue[i] = to_copy.queue[(to_copy.front + i) % to_copy.length];
//    }
        //resulting queue starts at front of array, regardless of where to_copy starts
    }


    template<class T>
    LinkedQueue<T>::LinkedQueue(const std::initializer_list<T> &il)
//    : used(il.size())
    {
//        queue = new T[length];
//        for (const T& q_elem : il)
//            enqueue(q_elem);
//}
    }


    template<class T>
    template<class Iterable>
    LinkedQueue<T>::LinkedQueue(const Iterable &i)
    {
//    : length(i.size())
//    {
//        queue = new T[length];
//        for (const T &v : i)
//            enqueue(v);
//    }
    }


////////////////////////////////////////////////////////////////////////////////
//
//Queries

    template<class T>
    bool LinkedQueue<T>::empty() const {

        //return front == rear;

    }


    template<class T>
    int LinkedQueue<T>::size() const {
        return used;
        //return rear >= front ? rear-front : length-(front-rear);
    }


    template<class T>
    T &LinkedQueue<T>::peek() const {
//    if (this->empty())
//        throw EmptyError("ArrayQueue::peek");
//
//    return queue[front];
    }


    template<class T>
    std::string LinkedQueue<T>::str() const {
//    std::ostringstream answer;
//    answer << "ArrayQueue[";
//
//    if (length != 0)
//        for (int i=0; i<length; ++i) {
//            answer << i << ":";
//            if (this->is_in(i))
//                answer << queue[i];
//            answer << (i == length-1 ? "]" : ",");
//        }
//
//    answer << "(length=" << length << ",front=" << front << ",rear=" << rear << ",mod_count=" << mod_count << ")";
//    return answer.str();
    }


////////////////////////////////////////////////////////////////////////////////
//
//Commands

    template<class T>
    int LinkedQueue<T>::enqueue(const T &element)
    {

        if (front == nullptr) {
            front = new LN(element, front);
            rear = front;
        }
        rear = new LN(element, rear);

        used++;
        return rear;


    }


    template<class T>
    T LinkedQueue<T>::dequeue() {
        if (begin() == end()) return nullptr;

        --used;
        ++mod_count;

        T returnValue = end()->value;
        delete end();

        for (LN* i = begin(); i != nullptr; i++)
        {
            if (i->next == nullptr)
                front = i;
        }
        return returnValue;
    }


    template<class T>
    void LinkedQueue<T>::clear() {
        //delete end(); wrong!!
    }


    template<class T>
    template<class Iterable>
    int LinkedQueue<T>::enqueue_all(const Iterable &i) {
//    LN<T>* temp = this;
//    for (LN<T> *p = i; p != nullptr; p = p->next) {
//
//        this->value = p->value;
//        this = this->next;
//    } // has to enque if no nodes are available
    }


////////////////////////////////////////////////////////////////////////////////
//
//Operators

    template<class T>
    LinkedQueue<T> &LinkedQueue<T>::operator=(const LinkedQueue<T> &rhs)
    {
        if (this->size() == rhs.size()) {
            LN *temp; //= this->rear
            for (LN *p = rhs.begin(); p != nullptr; p = p->next) {
                temp->value = p->value;
                temp = temp->next;
            }
            if (size() > rhs.size()) {
                LN *temp = this->rear;
                for (LN *p = rhs; p != nullptr; p = p->next) {
                    temp->value = p->value;
                    temp = temp->next;
                    if (temp == nullptr) {
                        delete_list(temp);
                    }
                }

            }

            if (size() < rhs.size()) {
                LN *temp = this->rear;
                for (LN *p = rhs; p != nullptr; p = p->next) {
                    if (temp == nullptr) {
                        enqueue(p->value);
                    } else {
                        temp->value = p->value;
                    }
                    temp = temp->next;
                }
            }
        }
    }


    template<class T>
    bool LinkedQueue<T>::operator==(const LinkedQueue<T> &rhs) const {
    }


    template<class T>
    bool LinkedQueue<T>::operator!=(const LinkedQueue<T> &rhs) const {
    }


    template<class T>
    std::ostream &operator<<(std::ostream &outs, const LinkedQueue<T> &q) {
    }


////////////////////////////////////////////////////////////////////////////////
//
//Iterator constructors

    template<class T>
    auto LinkedQueue<T>::begin() const -> LinkedQueue<T>::Iterator {
        return *rear;
    }

    template<class T>
    auto LinkedQueue<T>::end() const -> LinkedQueue<T>::Iterator {
        return *front;
    }


////////////////////////////////////////////////////////////////////////////////
//
//Private helper methods

    template<class T>
    void LinkedQueue<T>::delete_list(LN *&front) {
//            if(front == nullptr) return;
//            delete_list(front->next);
//            delete front;

    }





////////////////////////////////////////////////////////////////////////////////
//
//Iterator class definitions

    template<class T>
    LinkedQueue<T>::Iterator::Iterator(LinkedQueue<T> *iterate_over, LN *initial) {
    }


    template<class T>
    LinkedQueue<T>::Iterator::~Iterator() {

    }


    template<class T>
    T LinkedQueue<T>::Iterator::erase() {
    }


    template<class T>
    std::string LinkedQueue<T>::Iterator::str() const {
    }


    template<class T>
    auto LinkedQueue<T>::Iterator::operator++() -> LinkedQueue<T>::Iterator & {
    }


    template<class T>
    auto LinkedQueue<T>::Iterator::operator++(int) -> LinkedQueue<T>::Iterator {
    }


    template<class T>
    bool LinkedQueue<T>::Iterator::operator==(const LinkedQueue<T>::Iterator &rhs) const {
    }


    template<class T>
    bool LinkedQueue<T>::Iterator::operator!=(const LinkedQueue<T>::Iterator &rhs) const {
    }


    template<class T>
    T &LinkedQueue<T>::Iterator::operator*() const {
    }


    template<class T>
    T *LinkedQueue<T>::Iterator::operator->() const {
    }


}

#endif /* LINKED_QUEUE_HPP_ */
