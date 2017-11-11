/*
 Project: WorkQueue
 File Name: WorkQueue.cpp
 Created by Aleksandr Golovin on 10/20/17.
 Copyright © 2017 Aleksandr Golovin. All rights reserved.
 */

#include "WorkQueue.hpp"

//Copy constructor, creates deep copy
WorkQueue::WorkQueue (const WorkQueue & rhs)
{
    //Checks to make sure you aren't copying queue to itself
    if(this != &rhs)
    {
        this->phead=NULL; //initializes phead
        
        LLNode * pRhs= rhs.phead;
        
        //Loops through passed queue
        while(pRhs)
        {
            this->addWorkItem(pRhs->getWork()); //Calls addWorkItem function to add WorkItem
            pRhs=pRhs->getNxt();
        }
    }
}

//Overloaded assignment operator, creates deep copy
WorkQueue & WorkQueue::operator = ( const WorkQueue & rhs)
{
    //Check to make sure queue is not assigned to itself
    if(this != &rhs)
    {
        deleteAllWorkItems(); //clears queue that will receive workItems
        
        LLNode * pRhs= rhs.phead;

        //Loops through passed queue
        while(pRhs)
        {
            this->addWorkItem(pRhs->getWork());
            pRhs=pRhs->getNxt();
        }
    }
    return *this;
}

//Adds workItem to queue
void WorkQueue::addWorkItem ( const WorkItem & item)
{
    if (phead==NULL)
    {
        phead= new LLNode(item);
    }
    else
    {
        LLNode * before=phead;
        LLNode * crnt=phead->getNxt();
        while (crnt && crnt->getPrio() <= item.getPriority())
        {
            crnt=crnt->getNxt();
            before=before->getNxt();
        }
        LLNode * nwItem= new LLNode (item);
        before->setNxt(nwItem);
        nwItem->setNxt(crnt);
    }
}

//Retuns workItem with given priorty, otherwise throw exception
const WorkItem & WorkQueue::nextWorkItem (int priority) const
{
    if (phead)
    {
        LLNode * temp=phead;
        
        //loops through queue until priority matches
        while(temp && temp->getPrio()<priority)
        {
            temp=temp->getNxt();
        }
        
        if(temp && temp->getPrio()>=priority)
        {
            return temp->getWork();
        }
        else
        {
            throw std::logic_error(" Work Doesn't Exist");
        }
    }
    else
    {
        throw std::logic_error(" Work Doesn't Exist");
    }
}

//Returns true if workItem with given priority exists else false
bool WorkQueue::hasWorkItem( int priority) const
{
    bool contains =false;
    if(phead)
    {
        LLNode * temp=phead;
        
        //Loops through queue until item found or end of queue
        while(!contains && temp)
        {
            if (temp->getPrio()>= priority)
            {
                contains =true;
            }
           temp=temp->getNxt();
        }
    }
    return contains;
}

//Returns true if workItem with given key exists else false
bool WorkQueue::containsKey( const string & key) const
{
    bool contains=false;
    if (phead)
    {
        LLNode * temp=phead;
        
        //Loops through queue until item found or end of queue
        while (!contains && temp)
        {
            if (temp->getID() == key)
            {
                contains=true;
            }
            else
            {
                temp=temp->getNxt();
            }
        }
    }
    return contains;
}

//Bumps workItem to top of it's priority level
void WorkQueue::bumpWorkItem( const string & key)
{
    if(phead)
    {
        LLNode * prioLead=phead;
        LLNode *before=phead;
        LLNode * crnt=phead->getNxt();
        bool found=false;
        
        //Loops through queue until item found or end of queue
        while(!found && crnt)
        {
            if(crnt->getID()==key)
            {
                found = true;
            }
            else
            {
                crnt=crnt->getNxt();
                before=before->getNxt();
                
                //Moves prioLead to priority level before current priority level
                if(crnt && (before->getPrio() < crnt->getPrio()))
                {
                    prioLead=before;
                }
            }
        }
        
        //Checks to see if item found and it's not already at top
        if(found && (before->getPrio() == crnt->getPrio()))
        {
            before->setNxt(crnt->getNxt());
            if(prioLead != phead)
            {
                crnt->setNxt(prioLead->getNxt());
                prioLead->setNxt(crnt);
            }
            else
            {
                crnt->setNxt(prioLead);
                phead=crnt;
            }
        }
    }
}

//Returns number of workItems in queue
int WorkQueue::getNumWorkItems() const
{
    int count=0;
    if (phead)
    {
        LLNode* temp=phead;
        
        //Loops through queue counting items
        while(temp)
        {
            temp=temp->getNxt();
            count++;
        }
    }
    return count;
}

//Returns number of workItems in queue with given priority
int WorkQueue::getNumWorkItems( int priority)const
{
    int count=0;
    if (phead)
    {
        LLNode * temp=phead;
        
        //Loops through queue, starts counting when items found
        while(temp)
        {
            if(temp->getPrio() == priority)
            {
                count++;
            }
            temp=temp->getNxt();
        }
    }
    return count;
}

//Deletes workItem with given key else does nothing
void WorkQueue::deleteWorkItem (string key)
{
    if(phead)
    {
        //If item at head is matched delete head, else loops until item found or end of queue
        if(phead->getID()==key)
        {
            LLNode * temp=phead->getNxt();
            delete phead;
            phead=temp;
        }
        else
        {
            LLNode * before=phead;
            LLNode * crnt=phead->getNxt();
            bool found=false;
            
            //loops through queue until item found or end of queue
            while(!found && crnt)
            {
                if(crnt->getID()==key)
                {
                    found = true;
                }
                else
                {
                    before=before->getNxt();
                    crnt=crnt->getNxt();
                }
            }
            
            //If item found, delete it
            if(found)
            {
                before->setNxt(crnt->getNxt());
                delete crnt;
            }
        }
    }
}

//Deletes all workItems from queue
void WorkQueue::deleteAllWorkItems()
{
    if (phead)
    {
        LLNode * temp=phead;
        
        //Loops through queue, deleting items
        while (temp)
        {
            LLNode * toDlt= temp;
            temp=toDlt->getNxt();
            delete toDlt;
        }
        phead=NULL;
    }
}

//Destructor, calls deleteAllWorkItems
WorkQueue::~WorkQueue()
{
    deleteAllWorkItems();
}
