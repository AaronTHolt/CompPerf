#include "Client.h"


Define_Module(Client);

// void Client::initialize()
// {
//     busyTime = 0;
//     WATCH(busyTime);

//     hitRate = par("hitRate");

//     currentlyServing = NULL;
// }

void Client::initialize()
{
    msg = new WebRequest("HELLO!");
    send(msg, "proxy$o");
}

// void Client::handleMessage(cMessage *msg)
// {
//     WebRequest *req = check_and_cast<WebRequest *>(msg);

//     if (req == currentlyServing) {
//         //
//         // Self message
//         //
//         busyTime += currentServiceTime;
//         currentlyServing = NULL;
//         sendMsgOnItsWay(req);
//     } else {
//         requests.push_back(req);
//     }

//     if ( currentlyServing == NULL && ! requests.empty() ) {
//         //
//         // serve next request -- send as self-message
//         //
//         currentlyServing = requests.front();
//         requests.pop_front();
//         simtime_t serviceTime = par("ServiceTime");
//         EV << "Start service of " << currentlyServing << " for " << serviceTime << endl;
//         scheduleAt( simTime() + serviceTime, currentlyServing);
//     }
// }

void Client::handleMessage(WebRequest *msg)
{
    // The handleMessage() method is called whenever a message arrives
    // at the module. Here, we just send it to the other module, through
    // gate `out'. Because both `tic' and `toc' does the same, the message
    // will bounce between the two.
    send(msg, "proxy$o");
}



void Client::sendMsgOnItsWay(WebRequest *msg)
{
    if ( msg -> getServed() ) {
        EV << "Forwarding message " << msg << " to client " << endl;
        send(msg, "client$o");
    } else {
        if ( uniform(0.0, 1.0) < hitRate ) {
            EV << "Hit in proxy cache " << msg << endl;
            msg -> setServed(true);
            send(msg, "client$o");
        } else {
            EV << "Forwarding message " << msg << " to router " << endl;
            send(msg, "router$o");
        }
    }
}