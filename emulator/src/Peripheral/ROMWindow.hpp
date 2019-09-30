#pragma once
#include "../Config.hpp"

#include "Peripheral.hpp"
#include "../Chipset/MMURegion.hpp"

#include <vector>

namespace casioemu
{
	class ROMWindow : public Peripheral
	{
		std::vector<MMURegion> regions;

	public:
		using Peripheral::Peripheral;

		void Initialise();
		void Uninitialise();
		void Tick();
		void Frame();
		void UIEvent(SDL_Event &event);
	};
}

