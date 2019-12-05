#pragma once

struct Block;

struct BlockLegacy {
	Block *getStateFromLegacyData(unsigned short) const;
};