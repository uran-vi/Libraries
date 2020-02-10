#pragma once
#include <UF6.h>

using namespace UF6;

class DynamicConsole
{
public:
	void open();
	void close();

	void SetTitle(string title);
	string GetTitle();

	bool IsOpen();

private:
	string title;
	FILE* pConsoleController = nullptr;

	void allowConsoleAccess();
	void forbidConsoleAccess();
};


