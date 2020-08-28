#include <minecraft/BinaryStream.h>
#include <minecraft/CompoundTag.h>
#include <minecraft/Block.h>
#include <minecraft/BlockLegacy.h>
#include <minecraft/BlockPalette.h>
#include <minecraft/Level.h>
#include <minecraft/Minecraft.h>
#include <minecraft/ServerInstance.h>

#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>

void generate_legacy_block_map(ServerInstance *serverInstance) {
	auto palette = serverInstance->getMinecraft()->getLevel()->getBlockPalette();

	std::ifstream input("required_block_states.json");

	auto stream = new BinaryStream();

	auto json = nlohmann::json::object();
	input >> json;

	for (auto &object : json["minecraft"].items()) {
		const auto &name = "minecraft:" + object.key();
		auto blockLegacy = palette->getBlockLegacy(name);
		for (auto &it : object.value()) {
			auto state = it.get<unsigned short>();

			if (name == "minecraft:cocoa" && state >= 12) {
				continue;
			}

			std::cout << "Processing " << name << " " << state << std::endl;

			auto block = blockLegacy->getStateFromLegacyData(state);

			stream->writeUnsignedVarInt(name.length());
			stream->write(name.c_str(), name.length());
			stream->writeUnsignedShort(state);
			stream->writeType(block->tag);
		}
	}

	std::ofstream output("output");
	output << *stream->buffer;
	output.close();
	delete stream;
}

void generate_palette(ServerInstance *serverInstance) {
	auto palette = serverInstance->getMinecraft()->getLevel()->getBlockPalette();
	unsigned int numStates = palette->getNumBlockRuntimeIds();
	std::cout << "Number of blockstates: " << numStates << std::endl;

	auto paletteStream = new BinaryStream();
	for (unsigned int i = 0; i < numStates; i++) {
		auto state = palette->getBlock(i);
		paletteStream->writeType(state->tag);
	}

	std::ofstream paletteOutput("palette.nbt");
	paletteOutput << *paletteStream->buffer;
	paletteOutput.close();
	delete paletteStream;
	std::cout << "Wrote palette to output file palette.nbt" << std::endl;
}

extern "C" void modloader_on_server_start(ServerInstance *serverInstance) {
	generate_legacy_block_map(serverInstance);
	generate_palette(serverInstance);
}
