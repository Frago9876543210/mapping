#pragma once

struct CompoundTag;

struct Block {
	char filler[24];
	CompoundTag tag;
};