#pragma once

#include <dynohook/nat_hook.h>
#include <cstdint>

namespace dyno {
	class VHook final : public NatHook {
	public:
		VHook(std::uintptr_t fnAddress, const ConvFunc& convention);
		~VHook() override;

		bool hook() override;
		bool unhook() override;

		HookMode getMode() const override {
			return HookMode::VTableSwap;
		}

		const std::uintptr_t& getAddress() const override {
			return m_fnAddress;
		}

	private:
		// address of the original function
		std::uintptr_t m_fnAddress;
	};
}