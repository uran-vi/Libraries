//Copy Pasta by UF6

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <string>
#include <memory>
#include "BytePattern.h"

/*
* How to use (nop example):
*	1. Create an AsmNop object (parameter address indicates, where you manipulation takes place)
*	2. Determine how many nops you want to create via "SetNopAmount(size_t nops)"
*	3. use the virtual function "manipulate()" in order to write to memory
*
*	DISCLAIMER - "BytePattern.h" exists in UF6 Github as a repository
*/

class Asmmanip
{
public:
	Asmmanip(void* address);

	virtual void manipulate() = 0;
	void demanipulate();

	void* GetAddress();
	void SetAddress(void* address);

	bool IsManipulated();

protected:
	void SetManipulated(bool isManipulated);

	void initializeOpcodes(size_t length);
	std::string GetInitialOpcodes();

private:
	void *address;
	bool isManipulated = false;
	std::string initialOpcodes;
};


class AsmCustom : public Asmmanip
{
public:
	using Asmmanip::Asmmanip;

	void manipulate();

	void SetCustomOpcodes(BytePattern bp);
	BytePattern GetCustomOpcodes();

private:
	BytePattern opcodes;
};


class AsmDetour : public Asmmanip
{
public:
	using Asmmanip::Asmmanip;

	void manipulate();

	void SetDetourAddress(void* pDetour);
	void* GetDetourAddress();

private:
	void* pDetour;
};


class AsmNop : public Asmmanip
{
public:
	using Asmmanip::Asmmanip;

	void manipulate();

	void SetNopAmount(size_t nops);
	size_t GetNopAmount();

private:
	size_t nops;
};