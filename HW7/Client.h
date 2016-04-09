#ifndef _Client_h_
#define _Client_h_

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include "WebRequest_m.h"
#include <list>

class Client : public cSimpleModule
{
private:
    // std::list<WebRequest *> requests;
    WebRequest *msg;
    double busyTime;
    
    double hitRate;

    WebRequest *currentlyServing;
    double currentServiceTime;

protected:
    virtual void initialize();
    virtual void handleMessage(WebRequest *msg);
    virtual void sendMsgOnItsWay(WebRequest *msg);
    
public:
    virtual double getBusy() { return busyTime; }
};
#endif