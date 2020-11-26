#pragma once
#include <bitset>
#include <cstdint>

using EntityID = std::uint32_t;
const EntityID MAX_ENTITIES = 1000000;
using ComponentID = std::uint8_t;
const ComponentID MAX_COMPONENTS = 100000;
using Signature = std::bitset<MAX_COMPONENTS>;