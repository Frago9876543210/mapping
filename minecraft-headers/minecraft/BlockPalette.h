#pragma once

#include <string>

struct BlockLegacy;

struct BlockPalette {
	BlockLegacy *getBlockLegacy(const std::string &) const;
	const Block *getBlock(const unsigned int & blockRuntimeId) const;
	size_t getNumBlockRuntimeIds() const;
};
