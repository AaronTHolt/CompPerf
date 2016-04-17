#include "ClientClosed.h"
#include "QueueNode.h"


Define_Module(ClientClosed);

void ClientClosed::initialize()
{

    
    MyFile.open ("OmnetClosed36.csv");

    N = 36;

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
        // std::cout << "Response Time = " << responseTime << std::endl;

        simtime_t proxy;
        proxy = 0;
        proxy = getUtil("^.proxy");
        // std::cout << "Proxy Time = " << proxy/simTime() << std::endl;

        simtime_t router;
        router = 0;
        router = getUtil("^.router");

        simtime_t originA;
        originA = 0;
        originA = getUtil("^.originA");

        simtime_t originB;
        originB = 0;
        originB = getUtil("^.originB");

        //time  resp    proxy   router  originA originB        
        MyFile << simTime() << ",";
        MyFile << responseTime << ",";
        MyFile << proxy/simTime() << ",";
        MyFile << router/simTime() << ",";
        MyFile << originA/simTime() << ",";
        MyFile << originB/simTime() << std::endl;


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