#include "Origin.h"


Define_Module(Origin);

void Origin::initialize()
{
    busyTime = 0;
    WATCH(busyTime);

    currentlyServing = NULL;
    serviceTime = par("ServiceTime");
}



void Origin::handleMessage(cMessage *msg)
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

void Origin::sendMsgOnItsWay(WebRequest *msg)
{
    msg -> setServed(true);
    send(msg, "router$o");
}
