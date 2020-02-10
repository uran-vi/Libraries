#pragma once
#include <UF6.h>
#include "BytePattern.h"

using namespace UF6;

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