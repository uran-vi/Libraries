#pragma once
#include "UF6.h"

using namespace UF6;

typedef PROCESSENTRY32	 Process32;
typedef MODULEENTRY32	 Module32;
typedef tagTHREADENTRY32 Thread32;
typedef tagHEAPLIST32	 Heaplist32;

typedef std::vector<PROCESSENTRY32>		Processes32;
typedef std::vector<MODULEENTRY32>		Modules32;
typedef std::vector<tagTHREADENTRY32>	Threads32;
typedef std::vector<tagHEAPLIST32>		Heaplists32;


class Snapshot32
{
public:
	enum FlagType
	{
		PROCESS = TH32CS_SNAPPROCESS, MODULE = TH32CS_SNAPMODULE,
		THREAD = TH32CS_SNAPTHREAD, HEAPLIST = TH32CS_SNAPHEAPLIST
	};


	Processes32	GetProcesses32(); //ignores target process
	Modules32	GetModules32();	  //includes target process (th32ProcessID)
	Threads32	GetThreads32();	  //ignores target process
	Heaplists32	GetHeaplists32(); //includes target process (th32ProcessID)
	
	void	takeSnapshot(int flags, DWORD th32ProcessID); // process=0 equals own process

private:
	void	SetProcesses32ByHandle(HANDLE hSnapshot);
	void	SetModules32ByHandle(HANDLE hSnapshot);
	void	SetThreads32ByHandle(HANDLE hSnapshot);
	void	SetHeaplists32ByHandle(HANDLE hSnapshot);


	Processes32 processes32;
	Modules32	modules32;
	Threads32	threads32;
	Heaplists32	heaplists32;
};


class SnapshotUtility32
{
public:
	SnapshotUtility32() = delete;
	SnapshotUtility32(Snapshot32& snapshot) : snapshot(snapshot) {}

	void	takeSnapshot(int flags);
	void	takeSnapshot(int flags, DWORD th32ProcessID);

	Processes32 GetAllProcesses32();
	Processes32 GetProcesses32ByName(string name);
	Process32	GetProcess32ByID(DWORD identifier);

	Modules32 GetAllModules32();
	Modules32 GetModules32ByName(string name);
	Module32 GetModule32ByID(DWORD identifier);

private:
	Snapshot32& snapshot;
};







