//Copy Pasta by UF6

#pragma once
#include <vector>
#include <windows.h>
#include <TlHelp32.h>
#include <string>

/*
* How to use:
*	1. Create a Snapshot32 and SnapshotUtility32 object 
*	(pass the Snapshot32 object as an argument in the Utility. After that, you'll be able to use the utility)
*	2. take a snapshot, depending on your needs (takeSnapshot(...), the enum FlagType displays all the options)
*	3. if you're aiming at your own process, just use takeSnapshot(FlagType). If else, use the overloaded function.
*	4. Call the get-function, according to your snapshot
*
* DISCLAIMER - 32/64 BIT PROCESS CHANGES BEHAVIOUR
*/

typedef PROCESSENTRY32	 Process32;
typedef MODULEENTRY32	 Module32;
typedef tagTHREADENTRY32 Thread32;
typedef tagHEAPLIST32	 Heaplist32;

typedef std::vector<PROCESSENTRY32>		Processes32;
typedef std::vector<MODULEENTRY32>		Modules32;
typedef std::vector<tagTHREADENTRY32>	Threads32;
typedef std::vector<tagHEAPLIST32>		Heaplists32;

enum FlagType
{
	PROCESS = TH32CS_SNAPPROCESS, MODULE = TH32CS_SNAPMODULE,
	THREAD = TH32CS_SNAPTHREAD, HEAPLIST = TH32CS_SNAPHEAPLIST
};

class Snapshot32
{
public:
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

	std::vector<DWORD>		 GetAllProcessIDs();
	std::vector<std::string> GetAllProcessNames();

	std::string			GetProcessNameByID(DWORD identifier);
	std::vector<DWORD>  GetAllProcessIDsByName(std::string name);

	std::vector<std::string> GetModuleNames();

private:
	Snapshot32& snapshot;
};







