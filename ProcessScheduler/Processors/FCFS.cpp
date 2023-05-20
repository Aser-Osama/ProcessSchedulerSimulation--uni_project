#include "FCFS.h"
#include "../Scheduler.h"
void FCFS::SigKill(Process* P){
    //search for the the process in  the RUN or RDY list then move it TRM 
    //then calculate the statistics of the process like CT, etc.
}

void FCFS::ScheduleAlgo(){
    Node<Process*>* nR;
    nR = RDY.getHead();
    if (nR) 
    {
        while (sch->migratedMaxW(nR->getItem()))
        {
            RDY.DeleteFirst();
            nR = RDY.getHead();
            if (!nR) {setRUN(nullptr); return;}
        }
        setRUN(nR->getItem());
        RDY.DeleteFirst();
    }
    else {
        setRUN(nullptr);
    }
}


  

Process* FCFS::removeFromReady(int pid)
{
    Node<Process*>* head = RDY.getHead();
    Process* to_remove;
    if (!head) return nullptr;

    while (head->getNext())
    {
        if (head->getItem()->find_by_pid(pid))
        {
            to_remove = head->getItem();
            RDY.DeleteNode(to_remove);
            return to_remove; //assuming 2 processes cant have the same pid
        }
        else 
        {
            head = head->getNext();
        }
    }
    return nullptr;
    
}

FCFS::FCFS(){

}

void FCFS::moveToRDY(Process* const& NewProcess)
{
    this->currentBusyTime += NewProcess->getCT();
    RDY.InsertEnd(NewProcess);
}

ostream& operator<<(ostream& os, const FCFS& prcsr)
{
    os << "[FCFS]: " << prcsr.RDY.getCount() << " RDY: ";
    prcsr.RDY.PrintList();
    return os;
}

Process* FCFS::getTopElem() 
{
    Process* first = RDY.getHead()->getItem();
    if (!first) { return nullptr; }
    this->currentBusyTime -= first->getCT();
    RDY.DeleteFirst();
    return first; 
}

