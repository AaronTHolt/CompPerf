#ifndef _Proxy_h_
#define _Proxy_h_

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include "WebRequest_m.h"
#include <list>
#include "QueueNode.h"

class Proxy : public QueueNode
{
private:
	std::list<WebRequest *> requests;
	
	double hitRate;

	WebRequest *currentlyServing;
	

protected:
	virtual void initialize();
	virtual void handleMessage(cMessage *msg);
	virtual void sendMsgOnItsWay(WebRequest *msg);
	
public:
};
#endif