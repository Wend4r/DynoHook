#pragma once

namespace dyno {
    enum class RelativeInstruction : uint8_t {
        CALL,
        BRANCH, // jcc, loopcc
        RIP_RELATIV
    };

    /**
     * @brief Decodes the target binary and provides utilities to work with assembly instructions
     *
     * Uses the Zydis Disassembler to analyse and/or relocate assembler instructions.
     */
    class Decoder {
    public:
        Decoder();
        ~Decoder();

        std::vector<int8_t> relocate(void* sourceAddress, size_t length, void* targetAddress, bool restrictedRelocation = false) const;
        void printInstructions(void* address, size_t byteCount) const;
        size_t getLengthOfInstructions(void* sourceAddress, size_t length) const;
        std::vector<int8_t*> findRelativeInstructionsOfType(void* startAddress, RelativeInstruction type, size_t length) const;
        bool calculateRipRelativeMemoryAccessBounds(void* sourceAddress, size_t length, int64_t& lowestAddress, int64_t& highestAddress) const;

    private:
        // we use a void pointer here since we can't forward declare the ZydisDecoder c typedef struct
        void* m_zydisDecoder;
    };
}