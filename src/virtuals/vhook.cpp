#include <dynohook/log.h>
#include <dynohook/virtuals/vhook.h>

using namespace dyno;

VHook::VHook(std::uintptr_t fnAddress, const ConvFunc& convention) : NatHook(convention), m_fnAddress{fnAddress} {
	assert(fnAddress != 0 && "Function address cannot be null");
}

VHook::~VHook() {
	if (m_hooked) {
		unhook();
	}
}

bool VHook::hook() {
	assert(!m_hooked);
	if (m_hooked) {
		DYNO_LOG_WARN("Vhook failed: hook already present");
		return false;
	}
	// create the bridge function
	if (!createBridge()) {
		DYNO_LOG_ERR("Failed to create bridge");
		return false;
	}
	m_hooked = true;
	return true;
}

bool VHook::unhook() {
	assert(m_hooked);
	if (!m_hooked) {
		DYNO_LOG_ERR("Vhook failed: no hook present");
		return false;
	}
	m_hooked = false;
	// restore should be handled by holder
	return true;
}