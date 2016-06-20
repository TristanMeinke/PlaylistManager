//  LinkedList.cpp
//  CS162Assignment4-mp3Player
//
//  Created by Tristan on 2/22/16.


#include "LinkedList.h"

LinkedList::LinkedList()
{
    listLen_ = 0;
}

LinkedList::~LinkedList()
{
    
    
}

//***Modifiers***//

void LinkedList::AddLinkToBack(void* ptr) //Adds a link (item) to the back (tail) of the list
{
    
    if (listLen_ > 0 )
    {
        //        std::cout<<"Adding new item\n"; //***DIAGNOSTIC: FILE REPORT***//
        
        Node* addition = new Node; //Creates a new node in the list
        addition->data_ = ptr;  //this node gets the new song data
        last_->next_ = addition; //this node now comes after the last node
        addition->prev_ = last_; //sets prev_ to the previous last node of the list
        last_ = addition; // this node becomes the last node
        
        listLen_++; //Increments list length when an item is added
    }
    
    if (listLen_ == 0) //If there are no nodes in the list
    {
        
        //        std::cout<< "Adding first item\n"; //***DIAGNOSTIC: FILE REPORT***//
        
        Node* addFirst = new Node; //creates a node to start the list
        addFirst->data_ = ptr; //Assigns the song object to the data_ field of the node through ptr
        last_ = addFirst;  //Assigns addFirst to last_
        first_ = addFirst; //Assigns addFirst to first_ as well, making it the entire list
        addFirst->prev_= 0; //Assigns prev_ to 0 for the head of the list
        
        listLen_++;
    }
    
    
    //    std::cout<<"Lenghth of list is: " << listLen_ <<std::endl; //***DIAGNOSTIC: FILE REPORT***//
    //    std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * *"  << std::endl; //***DIAGNOSTIC: FILE REPORT***//
}

void* LinkedList::RemoveThisLink(Node* removal)
{

    
    if (listLen_ < 1)
    {
        std::cout << "¡Error! Node selected for deletion out of range." << std::endl;
        return removal;
    }
    
//    std::cout << "Length of List: " << listLen_ << "\n"; //***DIAGNOSTIC***//
//    
//    std::cout << "Current Data: " << removal->data_ << "\n"; //***DIAGNOSTIC***//
    
    
    if (removal == first_)
    {
        RemoveLinkFromFront();
        return removal;
    }
    
    else {
    
        if (removal->next_ != 0 && removal->prev_ != 0 && listLen_ >=1)//If removal is neither the first nor last node
        {
            removal->next_->prev_ = removal->prev_;
            
            removal->prev_->next_ = removal->next_;
        }
    
        if (removal->prev_ == 0)
        {
            removal->next_->prev_ = 0;
        
            if (removal->next_ != 0) //If removal is the first node
            {
                removal->next_->prev_ = removal->prev_;
            
            }
        
        }
    
        if (removal->next_ == 0)
        {
            removal->prev_->next_ = 0;
        
            if(removal->prev_ != 0) //If removal is the last node
            {
                removal->prev_->next_ = removal->next_;
            }
        }
    
    }
    
    if (listLen_ == 1) //If the list length is only one song, then it is both the beginning and the end.
    {
        last_ = first_;
    }
    
    listLen_--;
    
//
    // if prev_ = 0, then  next->prev = 0,
    // etc.
    
    

    
    return removal;
}

void* LinkedList::RemoveLinkFromFront() //Removes a link from the beginning of the list
{
    Node* removal = first_;
    Node* newFirst = first_->next_;
    delete removal;
    
    //    std::cout << "RemoveLinkFromFront() has fired! (listLen_:" << listLen_ << " )\n"; //***DIAGNOSTIC: DELETION REPORT***//
    
    listLen_--;
    
    first_ = newFirst;
    return first_;
    
}
//
////***Accessors***//

Node* LinkedList::GetFirstNode()
{
    return first_;
}

long LinkedList::GetListLength()
{
    return listLen_;
}