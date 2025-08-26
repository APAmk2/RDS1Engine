#pragma once

constexpr char ENGINE_NAME[] = "RDS1 Engine";

constexpr bool FLAG(i32 flagpack, i32 flag) { return (flagpack & flag) != 0; }
constexpr void SETFLAG(i32 flagpack, i32 flag) { flagpack |= flag; }
constexpr void UNSETFLAG(i32 flagpack, i32 flag) { flagpack = (flagpack | flag) ^ flag; }