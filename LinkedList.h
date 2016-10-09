/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LinkedList.h
 * Author: krefl
 *
 * Created on October 9, 2016, 1:22 PM
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <cstdlib>

template <class A> class Node 
{
    public:
        Node(A in) {
            data = in;
        }
        
        Node<A>* next = NULL;
        Node<A>* prev = NULL;
        
        A        data;
};

/**
 * Linked List 
 * (double linked)
 * 
 */
template <class A> class LinkedList 
{
    public:
        
        /**
         * Adds element to list
         * 
         * @param in element to add
         */
        void add(A in) {
            Node<A> *N = new Node<A>(in);
            
            if(head==NULL) {
                head = N;
            } else {
                N->prev = tail;
                tail->next = N;
            }
   
            tail = N;
            
            elements++;
        }
        
        /*
         * Return # elements
         *
         */
        int size() {
            return elements;
        }
       
        /*
         * Returns ith element or NULL if not present
         *
         */
        A* get(int i) {
            if(i >= 0 && i < elements) {
                Node<A> *N = head; 
                        
                for(int n = 1; n <= i; n++) {
                    N = N->next;
                }
                
                return &N->data;
            }
           
            return NULL;
        }
        
        /*
         * Removes and returns ith element 
         * Throws exception if i is out of range
         *
         */
        A remove(int i) {
            if(i==0) return removeFirst(); 
            if(i==elements-1) return removeLast(); ;
            
            if(i > 0 && i < elements-1) {
                Node<A> *N = head; 
                        
                for(int n = 1; n <= i; n++) {
                    N = N->next;
                }
                
                N->prev->next = N->next;
                N->next->prev = N->prev;
                
                A ret = N->data;
                
                delete N;
                elements--;
                
                return ret;
            }
           
            throw std::out_of_range("LinkedList::remove - Index out of range");
        }
        
        
        /*
         * Return first element
         *
         */
        A* getFirst() {
            return &head->data;
        }
        
        /*
         * Return last element
         *
         */
        A* getLast() {
            return &tail->data;
        }
        
        /*
         * Removes and returns last element
         * Throws exception if empty
         */
        A removeLast() {
            
            if(elements > 0) {
                Node<A> *N = tail;
                
                if(elements > 1) {
                    tail = N->prev;
                    tail->next = NULL;
                } else {
                    tail = NULL;
                    head = NULL;
                }
                
                A ret = N->data; 
          
                delete N;
                elements--;
            
                return ret;
            } else {
                throw std::out_of_range("LinkedList::removeLast - Empty list");
            }
        }
        
        /*
         * Removes and returns last element
         * Throws exception if empty
         */
        A removeFirst() {
            
            if(elements > 0) {
                Node<A> *N = head;
                
                if(elements > 1) {
                    head  = N->next;
                    head->prev = NULL;
                } else {
                    head = NULL;
                    tail = NULL;
                }
                
                A ret = N->data; 
          
                delete N;
                elements--;
            
                return ret;
            } else {
                throw std::out_of_range("LinkedList::removeFirst - Empty list");
            }
        }
        
        
        /*
         * Remove all entries
         * 
         */
        void removeAll() {
            while(elements!=0) {
                removeLast();
            }
        }
        
        /*
         * Deconstructor
         */
        ~LinkedList() {
            removeAll();
        }
        
    private:   
        Node<A>* head = NULL;
        Node<A>* tail = NULL;
        
        int elements = 0;
};

#endif /* LINKEDLIST_H */

