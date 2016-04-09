#include "ClientClosed.h"
#include "QueueNode.h"


Define_Module(ClientClosed);

void ClientClosed::initialize()
{
    N = par("NumJobs");

    requests.resize(N);

    for (int i = 0; i<N; i++){
        requests[i] = new WebRequest("Hello!");
        requests[i] -> setServed(false);
        requests[i] -> setStartTime( simTime() );
        send(requests[i], "proxy$o");
    }
    // msg = new WebRequest("Hello!");
    // msg -> setServed(false);
    // send(msg, "proxy$o");
}

void ClientClosed::handleMessage(cMessage *msg)
{
    WebRequest *req = check_and_cast<WebRequest *>(msg);
    // req -> setServed(false);
    // send(req, "proxy$o");

    if ( req -> getServed() ) {
        // it's a request that's finally been satisfied...
        // ...record some performance statistics....

        simtime_t responseTime;
        responseTime = simTime() - req->getStartTime();
        std::cout << "Response Time = " << responseTime << std::endl;

        simtime_t otherTimes;
        otherTimes = 0;
        otherTimes = getUtil("^.proxy");
        std::cout << "Proxy Time = " << otherTimes/simTime() << std::endl;

        // now, "think" for 250ms and then remind myself to send msg
        req -> setServed( false );
        double thinkTime;
        thinkTime = par("ThinkTime");
        scheduleAt(simTime() + thinkTime, req);
    } else {
        // this must be a "self message, so time to send out a request...
        req -> setStartTime( simTime() );
        send(req, "proxy$o");
    }
}

simtime_t ClientClosed::getUtil(const char *node) { 
    return check_and_cast<QueueNode *>(getModuleByPath(node)) -> getBusy(); 
}



// void ClientClosed::sendMsgOnItsWay(WebRequest *msg)
// {
//     if ( msg -> getServed() ) {
//         EV << "Forwarding message " << msg << " to ClientClosed " << endl;
//         send(msg, "ClientClosed$o");
//     } else {
//         if ( uniform(0.0, 1.0) < hitRate ) {
//             EV << "Hit in proxy cache " << msg << endl;
//             msg -> setServed(true);
//             send(msg, "ClientClosed$o");
//         } else {
//             EV << "Forwarding message " << msg << " to router " << endl;
//             send(msg, "router$o");
//         }
//     }
// }