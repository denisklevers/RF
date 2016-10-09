/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#ifndef HASHMAP_H
#define HASHMAP_H


#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>
#include <iostream>

#include "uthash.h"

typedef std::mt19937 MyRNG; // Define Random Engine to be Mersenne Twister

template <class A> class hashmap
{
    public:
        
        /* Adds key -> value mapping
         * Overrides key if already exists
         */
        void add(int key, A val) {
            
            if(exist(key)) {
                remove(key);
            }
    
            Map *m;
            
            m = (Map*) malloc(sizeof(struct Map));
            m -> key   = key;
            m -> value = val;
    
            HASH_ADD_INT(Maps, key, m);
        }
        
        /*
         * Retrieves pointer to element under key or NULL
         * 
         */
        A *get(int key) {
            
            Map *m;

            HASH_FIND_INT(Maps, &key, m);
            
            if(m == NULL) {
                return NULL;
            } else {
                 
                return &m->value;
            }
        }
     
        /*
         * Tests if key exist
         * 
         */
        bool exist(int key) {
            Map *m;

            HASH_FIND_INT(Maps, &key, m);
            
            return (m==NULL) ? false : true;
        }
        
        /*
         * Removes key
         * 
         */
        void remove(int key) {
            
            Map *m;

            HASH_FIND_INT(Maps, &key, m);
            
            if(m!=NULL) {
            
                HASH_DEL(Maps, m);  
                free(m);  
            }
        }
        
        /*
         * Returns # key->maps
         * 
         */
        int size() {
            return HASH_COUNT(Maps);
        }
   
        /*
         * Retrieves next key value
         */
        A *next() {
            Map *m;
           
            if(iteratorPos==NULL) {
                m = (Map*) Maps;
            } else {
                m = (Map*) iteratorPos->hh.next;
            }
            
            if(m == NULL) {
                return NULL;
            } else {
                return &m->value;
            }
        }
        
        /*
         * Returns a random key value
         */
        A *random() {
            int s = size();
            
            std::uniform_int_distribution<uint32_t> unif_dist(0, s);
            
            int r = unif_dist(rng);
            
            Map *m = Maps;
            
            // Get rth element
            for(int i = 1; i < r; i++) {
                m = (Map*) m->hh.next;
            }
            
            if(m == NULL) {
                return NULL;
            } else {
                iteratorPos = m;
                
                return &m->value;
            }
        }
        /*
         * Removes all elements
         */
        void removeAll() {
            Map *m, *tmp;

            HASH_ITER(hh, Maps, m, tmp) {
                HASH_DEL(Maps,m);  
                free(m);            
            }
        }
        
        /*
         * Sets iterator to first added element
         */
        void resetIterator() {
            iteratorPos = NULL;
        }
        
        /*
         * Deconstructor
         */
        ~hashmap() {
            removeAll();
        }
        
        
    private:
        
        struct Map {
            int key;
            A value;
            UT_hash_handle hh;
        };
    
        Map* Maps = NULL;
    
        Map* iteratorPos = NULL;
        
        // Random number generator (seeded with unix time)
        MyRNG rng = MyRNG(std::time(0));  
        
};

#endif /* HASHMAP_H */

