#pragma once

#include <string>

struct ReadOnlyBinaryStream {
	void *vt;
	unsigned long offset;
	std::string unk2;
	std::string *buffer;
};

static_assert(offsetof(ReadOnlyBinaryStream, buffer) == 48);
static_assert(sizeof(ReadOnlyBinaryStream) == 56);