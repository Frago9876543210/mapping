#pragma once

#include "ReadOnlyBinaryStream.h"

struct BinaryStream : ReadOnlyBinaryStream {
	std::string unk11;
	std::string* unk2;

	BinaryStream();

	void write(const void *, unsigned long);

	void writeUnsignedShort(unsigned short);

	void writeUnsignedVarInt(unsigned int);

	template<typename T>
	void writeType(const T &);
};

static_assert(sizeof(BinaryStream) == 104);
