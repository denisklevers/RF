/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>
#include "uthash.h"

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
    
            struct Map *m;
            
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
            
            struct Map *m;

            HASH_FIND_INT(Maps, &key, m);
    
            A *pointer = (A*) malloc(sizeof *pointer);
            
            if(m == NULL) {
                return NULL;
            } else {
                *pointer = m->value;
                return pointer;
            }
        }
     
        /*
         * Tests if key exist
         * 
         */
        bool exist(int key) {
            struct Map *m;

            HASH_FIND_INT(Maps, &key, m);
            
            return (m==NULL) ? false : true;
        }
        
        /*
         * Removes key
         * 
         */
        void remove(int key) {
            
            struct Map *m;

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

    private:
        
        struct Map {
            int key;
            A value;
            UT_hash_handle hh;
        };
    
        struct Map* Maps = NULL;
    
};

#endif /* HASHMAP_H */

