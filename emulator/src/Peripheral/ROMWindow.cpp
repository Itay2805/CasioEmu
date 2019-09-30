#include "ROMWindow.hpp"

#include "../Data/HardwareId.hpp"
#include "../Logger.hpp"
#include "../Chipset/MMU.hpp"
#include "../Emulator.hpp"
#include "../Chipset/Chipset.hpp"

#include <string>

namespace casioemu
{
	MMURegion SetupRegion(size_t region_base, size_t size, size_t rom_base, bool strict_memory, Emulator& emulator, std::string description = {})
	{
		uint8_t *data = emulator.chipset.rom_data.data();
		auto offset = (ssize_t) rom_base - (ssize_t) region_base;
		if (description.empty())
			description = "ROM/Segment" + std::to_string(region_base >> 16);

		MMURegion::WriteFunction write_function = strict_memory ? [](MMURegion *region, size_t address, uint8_t data) {
			logger::Info("ROM::[region write lambda]: attempt to write %02hhX to %06zX\n", data, address);
			region->emulator->HandleMemoryError();
		} : [](MMURegion *, size_t, uint8_t) {
		};

		MMURegion region;
		if (offset >= 0)
			region.Setup(region_base, size, description, data + offset, [](MMURegion *region, size_t address) {
				return ((uint8_t *)(region->userdata))[address];
			}, write_function, emulator);
		else
			region.Setup(region_base, size, description, data + rom_base, [](MMURegion *region, size_t address) {
				return ((uint8_t *)(region->userdata))[address - region->base];
			}, write_function, emulator);

		return region;
	}

	void ROMWindow::Initialise()
	{
		bool strict_memory = emulator.argv_map.find("strict_memory") != emulator.argv_map.end();

		switch (emulator.hardware_id)
		{ // Initializer list cannot be used with move-only type: https://stackoverflow.com/q/8468774
		case HW_ES_PLUS:
			regions.emplace_back(SetupRegion(0x00000, 0x08000, 0x00000, strict_memory, emulator));
			regions.emplace_back(SetupRegion(0x10000, 0x10000, 0x10000, strict_memory, emulator));
			regions.emplace_back(SetupRegion(0x80000, 0x10000, 0x00000, strict_memory, emulator));
			break;

		case HW_CLASSWIZ:
			regions.emplace_back(SetupRegion(0x00000, 0x0D000, 0x00000, strict_memory, emulator));
			regions.emplace_back(SetupRegion(0x10000, 0x10000, 0x10000, strict_memory, emulator));
			regions.emplace_back(SetupRegion(0x20000, 0x10000, 0x20000, strict_memory, emulator));
			regions.emplace_back(SetupRegion(0x30000, 0x10000, 0x30000, strict_memory, emulator));
			regions.emplace_back(SetupRegion(0x50000, 0x10000, 0x00000, strict_memory, emulator));
			break;
		}
	}

	void ROMWindow::Uninitialise()
	{
	}

	void ROMWindow::Tick()
	{
	}

	void ROMWindow::Frame()
	{
	}

	void ROMWindow::UIEvent(SDL_Event &)
	{
	}
}
