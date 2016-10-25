/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   disttests.cpp
 * Author: deklever
 *
 * Created on October 25, 2016, 1:28 PM
 */

#include <stdlib.h>
#include <iostream>

/*
 * Simple C++ Test Suite
 */

void test1() {
    std::cout << "disttests test 1" << std::endl;
}

void test2() {
    std::cout << "disttests test 2" << std::endl;
    std::cout << "%TEST_FAILED% time=0 testname=test2 (disttests) message=error message sample" << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% disttests" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (disttests)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (disttests)" << std::endl;

    std::cout << "%TEST_STARTED% test2 (disttests)\n" << std::endl;
    test2();
    std::cout << "%TEST_FINISHED% time=0 test2 (disttests)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

