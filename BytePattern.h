#pragma once
#include "UF6.h"

using namespace UF6;

class BytePattern
{
public:
	BytePattern();
	BytePattern(string raw_pattern, string mask);
	BytePattern(string hex_pattern, string mask, bool isMaskInPattern);
	
	bool operator == (LPCCHAR pattern);

	DWORD indexIn(LPCCHAR base, size_t size);
	vector<DWORD> indexesIn(LPCCHAR base, size_t size);

	vector<byte> GetPattern();
	void SetPattern(vector<byte> pattern);

	string GetRawPattern();
	void SetRawPattern(string pattern);

	string GetHexPattern();
	void SetHexPattern(string pattern);
	void SetHexPatternWithMask(string pattern);

	string GetMask();
	void SetMask(string mask);

private:
	vector<byte> pattern;
	string mask;

	string GetMaximizedMask();
};
