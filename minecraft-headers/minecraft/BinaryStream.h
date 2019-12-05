#pragma once

#include "ReadOnlyBinaryStream.h"

struct BinaryStream : ReadOnlyBinaryStream {
	char filler[8];
	std::string unk11;

	void write(void const *, unsigned long);

	void writeUnsignedShort(unsigned short);

	void writeUnsignedVarInt(unsigned int);

	template<typename T>
	void writeType(T const &);
};

extern "C" void *_ZN12BinaryStreamC2Ev(BinaryStream *);