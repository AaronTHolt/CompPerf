#include "Proxy.h"
#include <iostream>

Define_Module(Proxy);

void Proxy::initialize()
{
	busyTime = 0;
	WATCH(busyTime);

	hitRate = par("hitRate");

	currentlyServing = NULL;
	serviceTime = par("ServiceTime");
}

void Proxy::handleMessage(cMessage *msg)
{
	WebRequest *req = check_and_cast<WebRequest *>(msg);
	// WebRequest *req = msg;

	if (req == currentlyServing) {
		//
		// Self message
		//
		busyTime += serviceTime;
		currentlyServing = NULL;
		sendMsgOnItsWay(req);
	} else {
		requests.push_back(req);
	}

	if ( currentlyServing == NULL && ! requests.empty() ) {
		//
		// serve next request -- send as self-message
		//
		currentlyServing = requests.front();
		requests.pop_front();
		serviceTime = par("ServiceTime");
		EV << "Start service of " << currentlyServing << " for " << serviceTime << endl;
		scheduleAt( simTime() + serviceTime, currentlyServing);
	}
}

void Proxy::sendMsgOnItsWay(WebRequest *msg)
{
	if ( msg -> getServed() ) {
		EV << "Forwarding message " << msg << " to client " << endl;
		send(msg, "client$o");
	} else {
		if ( uniform(0.0, 1.0) < 0.7 ) {
			EV << "Hit in proxy cache " << msg << endl;
			msg -> setServed(true);
			send(msg, "client$o");
		} else {
			EV << "Forwarding message " << msg << " to router " << endl;
			send(msg, "router$o");
		}
	}
}