#include "BytePattern.h"

BytePattern::BytePattern()
{
}

BytePattern::BytePattern(string raw_pattern, string mask)
{
	SetRawPattern(raw_pattern);
	SetMask(mask);
}

BytePattern::BytePattern(string hex_pattern, string mask, bool isMaskInPattern)
{
	if (isMaskInPattern)
	{
		SetHexPatternWithMask(hex_pattern);
	}
	else
	{
		SetHexPattern(hex_pattern);
		SetMask(mask);
	}
	
}

bool BytePattern::operator==(LPCCHAR pattern)
{
	bool res = true;
	string maxMask = GetMaximizedMask();
	for (int i = 0; i < this->pattern.size(); i++)
	{
		if (this->pattern.at(i) != pattern[i])
		{
			if(maxMask.at(i) != '?')
				res = false;
		}	
	}
	return res;
}

DWORD BytePattern::indexIn(LPCCHAR base, size_t size)
{
	for (byte i = 0; i < size; i++)
	{
		if (*this == (i + base))
			return (i);
	}
	return -1;
}

vector<DWORD> BytePattern::indexesIn(LPCCHAR base, size_t size)
{
	vector<DWORD> res;
	for (byte i = 0; i < size; i++)
	{
		if (*this == (i + base))
			res.push_back((i));
	}
	return res;
}

vector<byte> BytePattern::GetPattern()
{
	return pattern;
}

void BytePattern::SetPattern(vector<byte> pattern)
{
	this->pattern = pattern;
}

string BytePattern::GetRawPattern()
{
	string res;
	for (int i = 0; i < pattern.size(); i++)
		res.push_back((char)pattern.at(i));
	return res;
}

void BytePattern::SetRawPattern(string pattern)
{
	this->pattern.clear();
	for (int i = 0; i < pattern.size(); i++)
		this->pattern.push_back(pattern.at(i));
}

string BytePattern::GetHexPattern()
{
	string res;
	LPCHAR asciiBuffer = new char[2];
	for (int i = 0; i < pattern.size(); i++)
	{
		_itoa(pattern.at(i), asciiBuffer, 16);

		if (pattern.at(i) < 0x10)
		{
			res.push_back('0');
			res.push_back(asciiBuffer[0]);
		}
		else
		{
			res.push_back(asciiBuffer[0]);
			res.push_back(asciiBuffer[1]);
		}

		res.push_back(' ');
	}

	return res;
}

void BytePattern::SetHexPattern(string pattern)
{
	this->pattern.clear();

	LPCHAR ittok = strtok(const_cast<char*>(pattern.c_str()), " ");
	while (ittok != nullptr)
	{
		this->pattern.push_back(strtol(ittok, nullptr, 16));
		ittok = strtok(NULL, " ");
	}
	delete ittok;
}

void BytePattern::SetHexPatternWithMask(string pattern)
{
	this->pattern.clear();
	this->mask.clear();

	LPCHAR ittok = strtok(const_cast<char*>(pattern.c_str()), " ");
	while (ittok != nullptr)
	{
		if (*ittok == '?')
		{
			mask.push_back('?');
			this->pattern.push_back(NULL);
		}
		else
		{
			mask.push_back('x');
			this->pattern.push_back(strtol(ittok, nullptr, 16));
		}
		ittok = strtok(NULL, " ");
	}
	delete ittok;
}

string BytePattern::GetMask()
{
	return mask;
}

void BytePattern::SetMask(string mask)
{
	this->mask = mask;
}

string BytePattern::GetMaximizedMask()
{
	string res = mask;

	while (res.size() < pattern.size())
		res.push_back('x');
	
	while (res.size() > pattern.size())
		res.pop_back();

	return res;
}

