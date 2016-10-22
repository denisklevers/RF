/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FiniteQueue.h
 *
 * Created on October 22, 2016, 11:17 AM
 */

#ifndef FINITEQUEUE_H
#define FINITEQUEUE_H

#include "LinkedList.h"
#include <string>

template <class T> class FiniteQueue {
public:
    FiniteQueue() {
        length = 0;
        
        data = new LinkedList<T>();
    };
    
    /*
     * Init an empty finite queue
     * 
     * size : max length of queue
     */
    FiniteQueue(int size) {
        length = size;
        
        data = new LinkedList<T>();
        
    };
    
    /*
     * Init a finite queue filled with default member, fully filled
     * 
     * size : length of queue
     * fill : default member
     */
    FiniteQueue(int size, T fill) {
        length = size;
        data = new LinkedList<T>();
        
        for(int i = 0; i < size; i++) {
            data->add(fill);
        }
    };
    
    T &operator[](int i) {
        if(i < data->size()) {
            return data[i];
        } 
        
        throw std::out_of_range("FiniteQueue::access - Index out of range");
    }
    
    void in(T el) {
        data->add(el);
        
        if(data->size() > length) data->removeFirst();
    }
   
    T out() {
        return data->removeFirst();
    }
    
    int size() {
        return data->size();
    }
    
    std::string toString() {
        return data->toString();
    }

private:
    int length;
    
    LinkedList<T>* data;
    
};

#endif /* FINITEQUEUE_H */

