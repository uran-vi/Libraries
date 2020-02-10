#include "Snapshot32.h"

Processes32 Snapshot32::GetProcesses32()
{
	return processes32;
}

Modules32 Snapshot32::GetModules32()
{
	return modules32;
}

Threads32 Snapshot32::GetThreads32()
{
	return threads32;
}

Heaplists32 Snapshot32::GetHeaplists32()
{
	return heaplists32;
}

void Snapshot32::takeSnapshot(int flags, DWORD th32ProcessID)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(flags, th32ProcessID);

	if (hSnapshot == INVALID_HANDLE_VALUE)
		return; // SEH IMPLEMENT

	if (PROCESS & flags)
		SetProcesses32ByHandle(hSnapshot);

	if (MODULE & flags)
		SetModules32ByHandle(hSnapshot);

	if (THREAD & flags)
		SetThreads32ByHandle(hSnapshot);

	if (HEAPLIST & flags)
		SetHeaplists32ByHandle(hSnapshot);
}

void Snapshot32::SetProcesses32ByHandle(HANDLE hSnapshot)
{
	processes32.clear();

	Process32 p_iterator;
	p_iterator.dwSize = sizeof(Process32);
	if (Process32First(hSnapshot, &p_iterator))
	{
		do
		{
			processes32.push_back(p_iterator);
		} while (Process32Next(hSnapshot, &p_iterator));
	}
}

void Snapshot32::SetModules32ByHandle(HANDLE hSnapshot)
{
	modules32.clear();

	Module32 m_iterator;
	m_iterator.dwSize = sizeof(Module32);
	if (Module32First(hSnapshot, &m_iterator))
	{
		do
		{
			modules32.push_back(m_iterator);
		} while (Module32Next(hSnapshot, &m_iterator));
	}
}

void Snapshot32::SetThreads32ByHandle(HANDLE hSnapshot)
{
	threads32.clear();

	Thread32 t_iterator;
	t_iterator.dwSize = sizeof(Thread32);
	if (Thread32First(hSnapshot, &t_iterator))
	{
		do
		{
			threads32.push_back(t_iterator);
		} while (Thread32Next(hSnapshot, &t_iterator));
	}
}

void Snapshot32::SetHeaplists32ByHandle(HANDLE hSnapshot)
{
	heaplists32.clear();

	Heaplist32 hl_iterator;
	hl_iterator.dwSize = sizeof(Heaplist32);
	if (Heap32ListFirst(hSnapshot, &hl_iterator))
	{
		do
		{
			heaplists32.push_back(hl_iterator);
			hl_iterator.dwSize = sizeof(Heaplist32);
		} while (Heap32ListNext(hSnapshot, &hl_iterator));
	}
}

void SnapshotUtility32::takeSnapshot(int flags)
{
	snapshot.takeSnapshot(flags,0);
}

void SnapshotUtility32::takeSnapshot(int flags, DWORD processID)
{
	snapshot.takeSnapshot(flags, processID);
}

Processes32 SnapshotUtility32::GetAllProcesses32()
{
	return snapshot.GetProcesses32();
}

Processes32 SnapshotUtility32::GetProcesses32ByName(string name)
{
	Processes32 result;
	Processes32 ps32 = snapshot.GetProcesses32();
	for (Process32 p32 : ps32)
	{
		if (p32.szExeFile == name)
			result.push_back(p32);
	}
	return result;
}

Process32 SnapshotUtility32::GetProcess32ByID(DWORD identifier)
{
	Processes32 ps32 = snapshot.GetProcesses32();
	for (Process32 p32 : ps32)
	{
		if (p32.th32ProcessID == identifier)
			return p32;
	}
	return Process32();
}

Modules32 SnapshotUtility32::GetAllModules32()
{
	return snapshot.GetModules32();
}

Modules32 SnapshotUtility32::GetModules32ByName(string name)
{
	Modules32 result;
	Modules32 ms32 = snapshot.GetModules32();
	for (Module32 m32 : ms32)
	{
		if (m32.szModule == name)
			result.push_back(m32);
	}
	return result;
}

Module32 SnapshotUtility32::GetModule32ByID(DWORD identifier)
{
	Modules32 ms32 = snapshot.GetModules32();
	for (Module32 m32 : ms32)
	{
		if (m32.th32ModuleID == identifier)
			return m32;
	}
	return Module32();
}
