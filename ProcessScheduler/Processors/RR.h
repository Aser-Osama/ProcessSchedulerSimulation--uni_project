#pragma once

#include "Processor.h"


class RR :
    public Processor
{
    Queue<Process *> RDY;
public:
    void ScheduleAlgo() override;
    friend ostream& operator<<(ostream& os, const RR& prcsr);
    RR(int);

};

