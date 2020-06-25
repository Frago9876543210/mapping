#pragma once

#include <string>

struct ReadOnlyBinaryStream {
	void *vt;
	unsigned long offset;
	char filler[8]; //unknown field
	std::string ownedBuffer;
	std::string* buffer;
};

static_assert(offsetof(ReadOnlyBinaryStream, buffer) == 56);
static_assert(sizeof(ReadOnlyBinaryStream) == 64);
