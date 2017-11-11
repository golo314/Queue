/*
 Project: WorkQueue
 File Name: WorkQueue.hpp
 Created by Aleksandr Golovin on 10/20/17.
 Copyright © 2017 Aleksandr Golovin. All rights reserved.
 */

#ifndef WorkQueue_hpp
#define WorkQueue_hpp

#include <stdio.h>
#include "WorkItem.hpp"


class WorkQueue
{
private:

    //Private Node Class
    class LLNode
    {
    private:
        
        //Private variable
        LLNode * pNxt;
        WorkItem item;
        
    public:
        
        //Constructor
        LLNode(const WorkItem & nwItem) : pNxt(NULL), item (nwItem){};
        
        //Sets pNxt to passed pointer
        void setNxt (LLNode * nxt)  {pNxt=nxt;}
        
        //When called, Returns WorkItem
        const WorkItem & getWork() const {return item;}
        
        //When called, returns a constant pointer
        LLNode * getNxt() const {return pNxt;}
        
        //Returns a constant string key of WorkItem
        const string & getID()const {return item.getKey();}
        
        //Sets item to passed WorkItem
        void setWork (const WorkItem & nwItem) {item=nwItem;}
        
        //Returns work item priority
        int getPrio() const {return item.getPriority();}
    };
    
    //Pointer to head of queue
    LLNode * phead;
    
public:
    
    //Default Constructor
    WorkQueue ( ): phead(NULL){};
    
    //Copy constructor, creates deep copy
    WorkQueue (const WorkQueue & rhs);
    
    //Overloaded assignment operator, creates a deep copy
    WorkQueue & operator = ( const WorkQueue & rhs);
    
    //Adds WorkItem to queue
    void addWorkItem (const WorkItem & item);
    
    //Returns constant WorkItem for the priority level
    //Throws exception, if no work of passed priority
    const WorkItem & nextWorkItem( int priority) const;
    
    // Returns true if there is a work item to be returned for a given priority
    bool hasWorkItem( int priority) const;
    
    // Returns true if there is a work item with the key in the queue
    bool containsKey( const string & key) const;

    // “Bumps” the work item to the head of it’s priority queue ahead of older items
    void bumpWorkItem( const string & key);
    
    //Returns number of items in queue
    int getNumWorkItems() const;
    
    //Returns number of items with provided priority
    int getNumWorkItems( int priority)const;
    
    //Deletes work item with given key
    void deleteWorkItem (string key);
    
    //Deletes all WorkItems in queue
    void deleteAllWorkItems();
    
    //Virtual destructor
    virtual ~WorkQueue();
};

#endif /* WorkQueue_hpp */
