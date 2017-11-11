/*
 Project: WorkQueue
 File Name: WorkItem.hpp
 Created by Aleksandr Golovin on 10/20/17.
 Copyright © 2017 Aleksandr Golovin. All rights reserved.
*/

#ifndef WorkItem_hpp
#define WorkItem_hpp

#include <stdio.h>
#include <string>

//Saves from using namespace std
using std::string;

class WorkItem
{
private:
    
    //Private variable
    int prio;
    string ID;
    
public:
    
    //Constructor
    WorkItem( int priority, const string & key);
    
    //Copy Constructor
    WorkItem (const WorkItem & item);
    
    //Overloaded assignment operator
    WorkItem & operator = ( const WorkItem & rhs);
    
    //Inline Functions
    int getPriority() const {return prio;}
    
    const string &  getKey() const {return ID;}
    
    //Virtual Destructor
    virtual ~WorkItem();
};

#endif /* WorkItem_hpp */
