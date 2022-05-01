#pragma once

namespace pep
{
	enum class ControllerButton
	{
		DPad_Up = 0x0001,
		DPad_Down = 0x0002,
		DPad_Left = 0x0004,
		DPad_Right = 0x0008,
		Start = 0x0010,
		Back = 0x0020,
		Thumb_Left = 0x0040,
		Thumb_Right = 0x0080,
		Shoulder_Left = 0x0100,
		Shoulder_Right = 0x0200,
		Button_South = 0x1000,
		Button_East = 0x2000,
		Button_West = 0x4000,
		Button_North = 0x8000
	};

	enum class ButtonState
	{
		Down,
		Pressed,
		Released
	};

}