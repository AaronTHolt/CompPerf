#ifndef _QueueNode_h_
#define _QueueNode_h_

#include <omnetpp.h>


class QueueNode: public cSimpleModule
{
    protected:
        // virtual void initialize() = 0;
        simtime_t busyTime;
        simtime_t serviceTime;

    public:
        virtual simtime_t getBusy() { return busyTime; }
        // QueueNode();
        // ~QueueNode();
};


#endif