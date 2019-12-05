#pragma once

#include <string>

struct ReadOnlyBinaryStream {
	void *vt;
	unsigned long offset;
	std::string unk2;
	std::string *buffer;
};