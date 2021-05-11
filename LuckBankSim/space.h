#pragma once
class Space
{
private:

	static int spacesCount;

public:
	Space();
	virtual  int getNumSpaces() = 0;
};