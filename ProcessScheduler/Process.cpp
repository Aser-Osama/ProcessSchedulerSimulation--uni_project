#include "Process.h"

int Process::getPID() const { return PID; }
LinkedList<Process*>* Process::getChildren()const{ return children; }
int Process::getAT() const { return AT; }
int Process::getRT() const{ return FT- AT; }
int Process::getCT() const{ return CT; }
int Process::getTT() const{ return TT; }
int Process::getTRT()const{ return TRT; }
int Process::getWT() const{ return WT; }
Map<int,int> Process::getIO_R_D() const { return IO_R_D; }

void Process::setFT(int ft) { FT = ft; } // FT stands for first time. for the timestep it enters the CPU
void Process::setTT(int tt) { TT = tt; } // Termination Time should be set once
void Process::setTRT(){ TRT = TT - AT; } // Turn around time should be set once
void Process::setWT() { WT = TRT - CTstored; } // Wait time should be set once
bool Process::find_by_pid(int pid) { return this->PID == pid; }
int Process::getCTstored() const {return CTstored;}
bool Process::subRemainingTime()
{
	if (this->CT > 0) {
		this->CT--;
		return true;
	}
	else {
		return false;
	}
} // subtract from left over time. This returns false to show you when process is done
void Process::setCpuArrivalTime(int ft) { cpuArrivalTime=ft; } // first time should be set during scheduler loop


Process::Process(int pid, int at, int ct, Map<int,int> io_r_d):PID(pid),AT(at),CT(ct),IO_R_D(io_r_d), //initializer list to use while reading from file
													  TRT(0),WT(0),TT(0),RT(0),cpuArrivalTime(0),CTstored(ct) //values that are set as something initially
{
}

Process::Process(){}

ostream& operator<<(ostream& os, const Process& prcs)
{
	os << prcs.PID << " ";
	return os;
}

bool Process::operator==(const Process & p){
	if (p.getPID()==this->PID)
		return true;
	else
		return false;
}

bool Process::operator<(const Process& Process) const {
	return this->CT > Process.getCT();
}

bool Process::operator>(const Process& Process) const {
	return this->CT < Process.getCT();
}

void Process::addChild(Process* const& Child)
{
	children->InsertEnd(Child);
}

void Process::setForked()
{
	ForkedProcess = true;
}
bool Process::isForked()
{
	return ForkedProcess;
}


bool Process::decrementIO(int timestep) 
{
	Node<Pair<int, int>>* ProcessIO = IO_R_D.getHead();
	while (ProcessIO->getItem().getKey() <= timestep) // loops on the map to get the process ready for IO
	{
		ProcessIO = ProcessIO->getNext();
	}
	if (ProcessIO->getItem().getValue() > 1) // When the process' IO is greater than 1
	{
		ProcessIO->getItem().setValue(ProcessIO->getItem().getValue() - 1); // Decrement IO time 
		return true; // The process does not finish IO 
	}
	else
	{
		ProcessIO->getItem().setValue(ProcessIO->getItem().getValue() - 1); // Decrement IO time 
		return false; // The process finished its IO 
	}
}