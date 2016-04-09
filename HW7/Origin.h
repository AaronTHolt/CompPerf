#ifndef _Origin_h_
#define _Origin_h_

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include "WebRequest_m.h"
#include <list>
#include "QueueNode.h"

class Origin : public QueueNode
{
private:
    std::list<WebRequest *> requests;
    
    WebRequest *currentlyServing;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void sendMsgOnItsWay(WebRequest *msg);
public:
};
#endif