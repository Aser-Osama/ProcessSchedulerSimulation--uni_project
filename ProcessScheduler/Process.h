#pragma once

#include "ADT/Map.h"
#include <iostream>
#include <ostream>
using namespace std;
class Process
{
private:
	bool ForkedProcess = false;
	int PID, 
		AT, // Arrival time
		RT, // Response time
		CT, // CPU time
		FT, // CPU time
		TT, // Termination time
		TRT, // The total time a process spends in the system from its arrival to termination. TRT = TT - AT
		cpuArrivalTime, //THIS IS THE FIRST TIME ARRIVAL to cpu VARIABLE. SET THIS WHEN THE PROCESS FIRST ARRIVES AT A CPU 
		CTstored, // THIS IS THE LEFT OVER TIME. DECREMENT THIS USING THE METHOD TO REDUCE TIME REMAINING IN CPU RUN
		WT; // WT = TRT - CT

	
	Map<int,int> IO_R_D;
	LinkedList<Process*>* children = new LinkedList<Process*>; //null for childless processes
public:
	int getPID() const;
	LinkedList<Process*>* getChildren() const;
	int getAT() const;
	int getRT() const;
	int getCT() const;
	int getTT() const;
	int getTRT()const;
	int getWT()const;
	Map<int,int> getIO_R_D ()const;


	void setTT(int);

	void setFT(int ft);
	void setCpuArrivalTime(int);
	bool subRemainingTime(); 
	void setTRT();
	void setWT();
	bool find_by_pid(int pid);
	int getCTstored() const;
	friend ostream& operator<<(ostream& os, const Process& prcs);
	bool operator==(const Process &);
	bool operator< (const Process& other) const;
	bool operator> (const Process& other) const;
	void addChild(Process* const& Child);
	bool decrementIO(int timestep);

	Process(int pid, int at, int ct, Map<int,int> io_r_d);
	Process();
	Process(int pid) : PID(pid) {}
	void setForked();
	bool isForked();
};

