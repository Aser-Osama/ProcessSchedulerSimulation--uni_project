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
            this->currentBusyTime -= nR->getItem()->getCT();
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

Process* FCFS::findProcess(int pid)
{
    if (RUN) {
        if (pid == RUN->getPID())
        {
            return clearRUN();;
            //ScheduleAlgo();
        }
        else
        {
            Node<Process*>* tmp = RDY.getHead();
            bool found = false;
            while (tmp)
            {
                if (tmp->getItem()->getPID() == pid)
                {
                    currentBusyTime -= tmp->getItem()->getCT();
                    Process* item = tmp->getItem();
                    RDY.DeleteNode(item);
                    return item;
                }
                tmp = tmp->getNext();
            }
            return nullptr;
        }
    }
    else {
        return nullptr;
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

void FCFS::attemptFork()
{   
    int fork_random_num = (rand() % 1000) + 1;
    int fork_probability = sch->getForkProb();
    
    if (fork_random_num > fork_probability || !RUN){return;}

    Process* Child = sch->ForkProcess(RUN->getCT());
    if (!Child) {return;}


    RUN->addChild(Child);
}

bool FCFS::readyIsEmpty()
{
    return RDY.getCount() <= 0;
}

FCFS::FCFS()
{
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
    if (RDY.getHead()) {
        Process* first = RDY.getHead()->getItem();
        if (!first) { return nullptr; }
        this->currentBusyTime -= first->getCT();
        RDY.DeleteFirst();
        return first;
    }
    else {
        return nullptr;
    }
}

bool FCFS::Execute(Process*& P, int crnt_ts, int& io_length) {
	/*
		C1)True & PTR -> TRM (process done)
		C2)False & PTR -> TRM (IO request)
		C3)False & NULLPTR -> still excuting
		ScheduleAlgo fills the RUN in case its being cleared out or is already empty
	*/

	if (RUN) 
	{
		if (RUN->getIO_R_D().getValue(crnt_ts, io_length)) //if this is the time step when the process asks for I/O
		{
			this->currentBusyTime--;
			P = RUN; //returns the pointer the process for the scheduler to recieve and move to BLK
			ScheduleAlgo(); //calls the scheduling algorithim for the processor 
			return false; //informs the Scheduler that the process asked for I/O so it should be moved to BLK //C2 (move to blk, io req)
		}
		else 
		{
			bool isDone = !(RUN->subRemainingTime());
			if (isDone)
			{
				P = RUN;
				ScheduleAlgo();
				return true;//C1 (complete Process, move to TRM)
			}
			else
			{
                attemptFork();
				this->currentBusyTime--;
				P = nullptr;
				return false; //C3 (still excuting)
			}
		}
	}
	else //no process currently running
	{
		P = nullptr;
		ScheduleAlgo();
		return false; //C3 (edge case)
	}
}