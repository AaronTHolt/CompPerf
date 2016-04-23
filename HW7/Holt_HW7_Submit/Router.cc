#include "Router.h"


Define_Module(Router);

void Router::initialize()
{
    busyTime = 0;
    WATCH(busyTime);

    // hitRate = par("hitRate");

    currentlyServing = NULL;
    serviceTime = par("ServiceTime");
}

void Router::handleMessage(cMessage *msg)
{
    WebRequest *req = check_and_cast<WebRequest *>(msg);

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

void Router::sendMsgOnItsWay(WebRequest *msg)
{
    if ( msg -> getServed() ) {
        EV << "Forwarding message " << msg << " to Proxy " << endl;
        send(msg, "proxy$o");
    } else {
        if ( uniform(0.0, 1.0) < 0.5 ) {
            EV << "Go to Origin1 " << msg << endl;
            msg -> setServed(true);
            send(msg, "origin$o", 0);
        } else {
            EV << "Go to Origin2" << msg << endl;
            send(msg, "origin$o", 1);
        }
    }
}