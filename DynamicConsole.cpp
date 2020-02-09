//Copy Pasta by UF6

#include "DynamicConsole.h"

//Information regarding this library are in the header

void Console::open()
{
	if (!this->IsOpen())
	{	
		AllocConsole();
		allowConsoleAccess();
		if (!title.empty())
		{
			SetConsoleTitle(title.c_str());
		}
	}
}

void Console::close()
{
	if (this->IsOpen())
	{
		FreeConsole();
		forbidConsoleAccess();
	}
}

void Console::SetTitle(std::string title)
{
	this->title = title;
	SetConsoleTitle(title.c_str());
}

std::string Console::GetTitle()
{
	return title;
}

bool Console::IsOpen()
{
	return pConsoleController != nullptr;
}

void Console::allowConsoleAccess()
{
	freopen_s(&pConsoleController, "CONOUT$", "w", stdout);
	EnableMenuItem(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_DISABLED);
}

void Console::forbidConsoleAccess()
{
	fclose(pConsoleController);
	pConsoleController = nullptr;
}
