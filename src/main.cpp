#include <minecraft/BinaryStream.h>
#include <minecraft/CompoundTag.h>
#include <minecraft/Block.h>
#include <minecraft/BlockLegacy.h>
#include <minecraft/BlockPalette.h>
#include <minecraft/Level.h>
#include <minecraft/Minecraft.h>
#include <minecraft/ServerInstance.h>

#include <fstream>
#include <json.hpp>
#include <iostream>

extern "C" void modloader_on_server_start(ServerInstance *serverInstance) {
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
}