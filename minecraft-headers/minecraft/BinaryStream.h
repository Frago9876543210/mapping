#pragma once

#include "ReadOnlyBinaryStream.h"

struct BinaryStream : ReadOnlyBinaryStream {
	std::string unk11;
	std::string* unk2;

	BinaryStream();

	void write(void const *, unsigned long);

	void writeUnsignedShort(unsigned short);

	void writeUnsignedVarInt(unsigned int);

	template<typename T>
	void writeType(T const &);
};

static_assert(sizeof(BinaryStream) == 104);
