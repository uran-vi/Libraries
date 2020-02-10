#include "DynamicConsole.h"

void DynamicConsole::open()
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

void DynamicConsole::close()
{
	if (this->IsOpen())
	{
		FreeConsole();
		forbidConsoleAccess();
	}
}

void DynamicConsole::SetTitle(string title)
{
	this->title = title;
	SetConsoleTitle(title.c_str());
}

string DynamicConsole::GetTitle()
{
	return title;
}

bool DynamicConsole::IsOpen()
{
	return pConsoleController != nullptr;
}

void DynamicConsole::allowConsoleAccess()
{
	freopen_s(&pConsoleController, "CONOUT$", "w", stdout);
	EnableMenuItem(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_DISABLED);
}

void DynamicConsole::forbidConsoleAccess()
{
	fclose(pConsoleController);
	pConsoleController = nullptr;
}
