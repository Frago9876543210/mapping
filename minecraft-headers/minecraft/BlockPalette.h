#pragma once

#include <string>

struct BlockLegacy;

struct BlockPalette {
	BlockLegacy *getBlockLegacy(std::string const &) const;
};