/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 六  5/30 23:30:50 2020
 ************************************************************************/

#include<iostream>
using namespace std;

struct list {
    int val;
    list* p_after = nullptr;
};

int main(int argc, char* argv[]) {
    list *head;
    list p[10];
    for(int i = 0; i < 10; i++) {
        p[i].val = i;
        if (i != 9) {
            p[i].p_after = &p[i+1];
        }
    }
    
    list *ptr = &p[0];
    while(ptr) {
        std::cout << ptr->val << std::endl;
        ptr = ptr->p_after;
    }

    std::cout << "reverse a list" << std::endl;
    
    list* after = nullptr;
    list *tmp = nullptr;
    list *now = &p[0];
    list* before = now->p_after;
    while(now) {
        tmp = now->p_after;
        now->p_after = after;
        after = now;
        now = tmp;
    }
    
    ptr = &p[9];
    while(ptr) {
        std::cout << ptr->val << std::endl;
        ptr = ptr->p_after;
    }
    return 0;
}
