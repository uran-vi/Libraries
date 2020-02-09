//Copy Pasta by UF6

#include "Asmmanip.h"

//Information regarding this library are in the header

Asmmanip::Asmmanip(void* address)
{
	SetAddress(address);
}

void Asmmanip::demanipulate()
{
	if (IsManipulated())
	{
		DWORD oldProtect;
		size_t length = GetInitialOpcodes().length();
		VirtualProtect(GetAddress(), length, PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy(reinterpret_cast<char*>(GetAddress()), GetInitialOpcodes().c_str(), length);
		VirtualProtect(GetAddress(), length, oldProtect, 0);

		SetManipulated(false);
	}

}

void* Asmmanip::GetAddress()
{
	return address;
}

void Asmmanip::SetAddress(void* address)
{
	if (!IsManipulated())
	{
		this->address = address;
	}
}

bool Asmmanip::IsManipulated()
{
	return isManipulated;
}

void Asmmanip::SetManipulated(bool isManipulated)
{
	this->isManipulated = isManipulated;
}

void Asmmanip::initializeOpcodes(size_t length)
{
	initialOpcodes.clear();

	DWORD oldProtect;
	VirtualProtect(GetAddress(), length, PAGE_EXECUTE_READ, &oldProtect);
	initialOpcodes.assign(reinterpret_cast<char*>(GetAddress()), length);
	VirtualProtect(GetAddress(), length, oldProtect, 0);
}

std::string Asmmanip::GetInitialOpcodes()
{
	return initialOpcodes;
}

void AsmNop::manipulate()
{
	if (!IsManipulated())
	{
		initializeOpcodes(nops);

		DWORD oldProtect;
		VirtualProtect(GetAddress(), nops, PAGE_EXECUTE_READWRITE, &oldProtect);
		memset(GetAddress(), '\x90', nops);
		VirtualProtect(GetAddress(), nops, oldProtect, 0);

		SetManipulated(true);
	}
}

void AsmNop::SetNopAmount(size_t nops)
{
	this->nops = nops;
}

size_t AsmNop::GetNopAmount()
{
	return nops;
}

void AsmCustom::manipulate()
{
	if (!IsManipulated())
	{
		size_t opcodes_length = opcodes.GetMask().length();
		initializeOpcodes(opcodes_length);

		DWORD oldProtect;
		VirtualProtect(GetAddress(), opcodes_length, PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy(reinterpret_cast<char*>(GetAddress()), opcodes.GetRawPattern().c_str(), opcodes_length);
		VirtualProtect(GetAddress(), opcodes_length, oldProtect, 0);

		SetManipulated(true);
	}
}

void AsmCustom::SetCustomOpcodes(BytePattern bp)
{
	opcodes = bp;
}

BytePattern AsmCustom::GetCustomOpcodes()
{
	return opcodes;
}

void AsmDetour::manipulate()
{
	if (!IsManipulated())
	{
		initializeOpcodes(5);

		DWORD oldProtect;
		VirtualProtect(GetAddress(), 5, PAGE_EXECUTE_READWRITE, &oldProtect);
		*(reinterpret_cast<char*>(GetAddress())) = '\xE9';
		*(reinterpret_cast<DWORD*>((char*)GetAddress() + 0x1)) = ((char*)GetDetourAddress() - ((char*)GetAddress() + 0x5));
		VirtualProtect(GetAddress(), 5, oldProtect, 0);

		SetManipulated(true);
	}
}

void AsmDetour::SetDetourAddress(void* pDetour)
{
	this->pDetour = pDetour;
}

void* AsmDetour::GetDetourAddress()
{
	return pDetour;
}
