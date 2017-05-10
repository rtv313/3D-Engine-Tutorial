#pragma once

namespace Profiler
{
	typedef void (*HookSlotFunction)();
	HookSlotFunction hookSlotFunctions[Profiler::Hook::SLOT_COUNT];

	bool RegisterFunction(int index, HookSlotFunction func)
	{
		hookSlotFunctions[index] = func;
		return true;
	}
}

#define DECLARE_HOOK_FUNCTION(index) extern "C" void HookFunctionASM##index(); \
																		 static bool autoRegisterFunction##index = Profiler::RegisterFunction(index, HookFunctionASM##index);

DECLARE_HOOK_FUNCTION(0)
DECLARE_HOOK_FUNCTION(1)
DECLARE_HOOK_FUNCTION(2)
DECLARE_HOOK_FUNCTION(3)
DECLARE_HOOK_FUNCTION(4)
DECLARE_HOOK_FUNCTION(5)
DECLARE_HOOK_FUNCTION(6)
DECLARE_HOOK_FUNCTION(7)
DECLARE_HOOK_FUNCTION(8)
DECLARE_HOOK_FUNCTION(9)
DECLARE_HOOK_FUNCTION(10)
DECLARE_HOOK_FUNCTION(11)
DECLARE_HOOK_FUNCTION(12)
DECLARE_HOOK_FUNCTION(13)
DECLARE_HOOK_FUNCTION(14)
DECLARE_HOOK_FUNCTION(15)
DECLARE_HOOK_FUNCTION(16)
DECLARE_HOOK_FUNCTION(17)
DECLARE_HOOK_FUNCTION(18)
DECLARE_HOOK_FUNCTION(19)
DECLARE_HOOK_FUNCTION(20)
DECLARE_HOOK_FUNCTION(21)
DECLARE_HOOK_FUNCTION(22)
DECLARE_HOOK_FUNCTION(23)
DECLARE_HOOK_FUNCTION(24)
DECLARE_HOOK_FUNCTION(25)
DECLARE_HOOK_FUNCTION(26)
DECLARE_HOOK_FUNCTION(27)
DECLARE_HOOK_FUNCTION(28)
DECLARE_HOOK_FUNCTION(29)
DECLARE_HOOK_FUNCTION(30)
DECLARE_HOOK_FUNCTION(31)
DECLARE_HOOK_FUNCTION(32)
DECLARE_HOOK_FUNCTION(33)
DECLARE_HOOK_FUNCTION(34)
DECLARE_HOOK_FUNCTION(35)
DECLARE_HOOK_FUNCTION(36)
DECLARE_HOOK_FUNCTION(37)
DECLARE_HOOK_FUNCTION(38)
DECLARE_HOOK_FUNCTION(39)
DECLARE_HOOK_FUNCTION(40)
DECLARE_HOOK_FUNCTION(41)
DECLARE_HOOK_FUNCTION(42)
DECLARE_HOOK_FUNCTION(43)
DECLARE_HOOK_FUNCTION(44)
DECLARE_HOOK_FUNCTION(45)
DECLARE_HOOK_FUNCTION(46)
DECLARE_HOOK_FUNCTION(47)
DECLARE_HOOK_FUNCTION(48)
DECLARE_HOOK_FUNCTION(49)
DECLARE_HOOK_FUNCTION(50)
DECLARE_HOOK_FUNCTION(51)
DECLARE_HOOK_FUNCTION(52)
DECLARE_HOOK_FUNCTION(53)
DECLARE_HOOK_FUNCTION(54)
DECLARE_HOOK_FUNCTION(55)
DECLARE_HOOK_FUNCTION(56)
DECLARE_HOOK_FUNCTION(57)
DECLARE_HOOK_FUNCTION(58)
DECLARE_HOOK_FUNCTION(59)
DECLARE_HOOK_FUNCTION(60)
DECLARE_HOOK_FUNCTION(61)
DECLARE_HOOK_FUNCTION(62)
DECLARE_HOOK_FUNCTION(63)
DECLARE_HOOK_FUNCTION(64)
DECLARE_HOOK_FUNCTION(65)
DECLARE_HOOK_FUNCTION(66)
DECLARE_HOOK_FUNCTION(67)
DECLARE_HOOK_FUNCTION(68)
DECLARE_HOOK_FUNCTION(69)
DECLARE_HOOK_FUNCTION(70)
DECLARE_HOOK_FUNCTION(71)
DECLARE_HOOK_FUNCTION(72)
DECLARE_HOOK_FUNCTION(73)
DECLARE_HOOK_FUNCTION(74)
DECLARE_HOOK_FUNCTION(75)
DECLARE_HOOK_FUNCTION(76)
DECLARE_HOOK_FUNCTION(77)
DECLARE_HOOK_FUNCTION(78)
DECLARE_HOOK_FUNCTION(79)
DECLARE_HOOK_FUNCTION(80)
DECLARE_HOOK_FUNCTION(81)
DECLARE_HOOK_FUNCTION(82)
DECLARE_HOOK_FUNCTION(83)
DECLARE_HOOK_FUNCTION(84)
DECLARE_HOOK_FUNCTION(85)
DECLARE_HOOK_FUNCTION(86)
DECLARE_HOOK_FUNCTION(87)
DECLARE_HOOK_FUNCTION(88)
DECLARE_HOOK_FUNCTION(89)
DECLARE_HOOK_FUNCTION(90)
DECLARE_HOOK_FUNCTION(91)
DECLARE_HOOK_FUNCTION(92)
DECLARE_HOOK_FUNCTION(93)
DECLARE_HOOK_FUNCTION(94)
DECLARE_HOOK_FUNCTION(95)
DECLARE_HOOK_FUNCTION(96)
DECLARE_HOOK_FUNCTION(97)
DECLARE_HOOK_FUNCTION(98)
DECLARE_HOOK_FUNCTION(99)
DECLARE_HOOK_FUNCTION(100)
DECLARE_HOOK_FUNCTION(101)
DECLARE_HOOK_FUNCTION(102)
DECLARE_HOOK_FUNCTION(103)
DECLARE_HOOK_FUNCTION(104)
DECLARE_HOOK_FUNCTION(105)
DECLARE_HOOK_FUNCTION(106)
DECLARE_HOOK_FUNCTION(107)
DECLARE_HOOK_FUNCTION(108)
DECLARE_HOOK_FUNCTION(109)
DECLARE_HOOK_FUNCTION(110)
DECLARE_HOOK_FUNCTION(111)
DECLARE_HOOK_FUNCTION(112)
DECLARE_HOOK_FUNCTION(113)
DECLARE_HOOK_FUNCTION(114)
DECLARE_HOOK_FUNCTION(115)
DECLARE_HOOK_FUNCTION(116)
DECLARE_HOOK_FUNCTION(117)
DECLARE_HOOK_FUNCTION(118)
DECLARE_HOOK_FUNCTION(119)
DECLARE_HOOK_FUNCTION(120)
DECLARE_HOOK_FUNCTION(121)
DECLARE_HOOK_FUNCTION(122)
DECLARE_HOOK_FUNCTION(123)
DECLARE_HOOK_FUNCTION(124)
DECLARE_HOOK_FUNCTION(125)
DECLARE_HOOK_FUNCTION(126)
DECLARE_HOOK_FUNCTION(127)