//  LinkedList.h
//  CS162Assignment4-mp3Player
//
//  Created by Tristan on 2/22/16.


#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

struct Node
{
    void* data_; //Points to a song object
    Node* prev_;
    Node* next_; //Points to the next link
    
    Node() //Constructor
    {
        data_ = 0;
        prev_ = 0;
        next_ = 0;
    }
};

class LinkedList
{
private:
    
    Node* first_;
    Node* last_;
    long listLen_; //Number of nodes between first and last
    
public:
    
    LinkedList();
    ~LinkedList();
    //***Modifiers***//
    void AddLinkToBack(void* ptr); //Pass song here, then package into node and add to list
    void* RemoveThisLink(Node* node);
    void* RemoveLinkFromFront();  //Returns new beginning of list
    //***Accessors***//
    Node* GetFirstNode();
    long GetListLength();
};

#endif /* LinkedList_h */
