#ifndef _ClientClosed_h_
#define _ClientClosed_h_

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include "WebRequest_m.h"
#include <vector>
#include <fstream>
using namespace std;

class ClientClosed : public cSimpleModule
{
private:
    std::vector<WebRequest *> requests;

    int N;
    
    double hitRate;

    WebRequest *msg;

    WebRequest *currentlyServing;

    ofstream MyFile;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    // virtual void sendMessageToProxy()
    
public:
    simtime_t getUtil(const char *node);
};
#endif