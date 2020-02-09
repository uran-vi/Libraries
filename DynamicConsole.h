//Copy Pasta by UF6

#pragma once
#include <windows.h>
#include <string>

/* 
* How to use:
*	1. Create a Console object
*	2. Call SetTitle, in order to change the title (also works while the console's open)
*	3. Call its member function "open", to open the console
*	4. Cout/Print wherever you want (if the console isn't open during the cout, your application's gonna crash)
*	5. In order to close the console, call its member function "close"
*	
* DISCLAIMER - ONLY FOR COUTS (STDOUT), NO STDIN OR STDERR
*			 - ISN'T ABLE TO CREATE MULTIPLE CONSOLES
*/


class DynamicConsole
{
public:
	void open();
	void close();

	void SetTitle(std::string title);
	std::string GetTitle();

	bool IsOpen();

private:
	std::string title;
	FILE* pConsoleController = nullptr;

	void allowConsoleAccess();
	void forbidConsoleAccess();
};


