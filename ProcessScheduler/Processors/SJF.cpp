#include "SJF.h"


void SJF::ScheduleAlgo(){
    /*Process* nR;
    RDY.dequeue(nR);
    setRUN(nR);
    RDY.enqueue(nR);
    untill PQ implemenation is done*/

}

void SJF::add_to_RDY(Process* const &prcs)
{
    RDY.enqueue(prcs);
}

SJF::SJF(){
	
}


void SJF::MoveToRDY(Process* NewProcess)
{
    RDY.enqueue(NewProcess);
}

ostream& operator<<(ostream& os, const SJF& prcsr)
{
    //os << "[SJF]: " << prcsr.RDY.getCount() << "RDY: ";
    //prcsr.RDY.Print();
    return os;
}
