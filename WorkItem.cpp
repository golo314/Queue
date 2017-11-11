/*
 Project: WorkQueue
 File Name: WorkItem.cpp
 Created by Aleksandr Golovin on 10/20/17.
 Copyright © 2017 Aleksandr Golovin. All rights reserved.
 */

#include "WorkItem.hpp"

//Constructor
WorkItem::WorkItem (int priority, const string & key)
{
    prio=priority;
    ID.assign(key);
}

//Copy Constructor
WorkItem::WorkItem (const WorkItem & item)
{
    this->prio=item.prio;
    this->ID=item.ID;
}

//Overloaded Assignment Operator
WorkItem & WorkItem:: operator = (const WorkItem & rhs)
{
    this->prio=rhs.prio;
    this->ID=rhs.ID;
    return *this;
}

//Virtual Destructor, left blank
WorkItem::~WorkItem(){}
