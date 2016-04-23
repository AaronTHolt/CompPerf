#include "ClientOpen.h"
#include "QueueNode.h"


Define_Module(ClientOpen);

void ClientOpen::initialize()
{

    InterarrivalTime = par("InterarrivalTime");
    MyFile.open ("OmnetOpen23_96.csv");

    msg = new WebRequest("Hello!");
    msg -> setServed(false);
    msg -> setStartTime( simTime() );
    scheduleAt(simTime() + InterarrivalTime, msg);

}

void ClientOpen::handleMessage(cMessage *msg)
{
    WebRequest *req = check_and_cast<WebRequest *>(msg);
    InterarrivalTime = par("InterarrivalTime");

    if ( req -> getServed() ) {
     // it's a request that's finally been satisfied...
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
        delete(req);
    } else {

        delete(req); // could probably re-use this
      
        // this must be a "self message, so time to send out a request...
        req = new WebRequest("Hello!"); // generate messages for proxy...
        req -> setServed( false );
        req -> setStartTime( simTime() );
        // sendMessageToProxy( msg );
        send(req, "proxy$o");

        // now, send myself another "self message" to send next request
        req = new WebRequest("Hello!");
        req -> setServed( false );
        scheduleAt(simTime() + InterarrivalTime, req);
   }

}

simtime_t ClientOpen::getUtil(const char *node) { 
    return check_and_cast<QueueNode *>(getModuleByPath(node)) -> getBusy(); 
}
