#pragma once

namespace pep
{
	enum class ButtonState
	{
		Down,
		PressedThisFrame,
		ReleasedThisFrame
	};

	enum class ControllerButton
	{
		DPad_Up		=0x0001,
		DPad_Down	=0x0002,
		DPad_Left	=0x0004,
		DPad_Right	=0x0008,

		Start	=0x0010,
		Back	=0x0020,

		Thumb_Left		=0x0040,
		Thumb_Right		=0x0080,
		Shoulder_Left	=0x0100,
		Shoulder_Right	=0x0200,

		Button_South	=0x1000,
		Button_East		=0x2000,
		Button_West		=0x4000,
		Button_North	=0x8000
	};

	enum class KeyboardKey
	{
		p_LBUTTON	=0x01,	//Left mouse button
		p_RBUTTON	=0x02,	//Right mouse button
		p_CANCEL	=0x03,	//Control - break processing
		p_MBUTTON	=0x04,	//Middle mouse button(three - button mouse)
		p_XBUTTON1	=0x05,	//X1 mouse button
		p_XBUTTON2	=0x06,	//X2 mouse button

		p_BACKSPACE	=0x08,	//BACKSPACE key
		p_TAB		=0x09,	//TAB key

		p_CLEAR		=0x0C,	//CLEAR key
		p_RETURN	=0x0D,	//ENTER key

		p_SHIFT		=0x10,	//SHIFT key
		p_CONTROL	=0x11,	//CTRL key
		p_ALT		=0x12,	//ALT key
		p_PAUSE		=0x13,	//PAUSE key
		p_CAPS		=0x14,	//CAPS LOCK key
		p_ESCAPE	=0x1B,	//ESC key

		p_SPACE		=0x20,	//SPACEBAR
		p_PAGEUP	=0x21,	//PAGE UP key
		p_PAGEDOWN	=0x22,	//PAGE DOWN key
		p_END		=0x23,	//END key
		p_HOME		=0x24,	//HOME key
		p_LEFT		=0x25,	//LEFT ARROW key
		p_UP		=0x26,	//UP ARROW key
		p_RIGHT		=0x27,	//RIGHT ARROW key
		p_DOWN		=0x28,	//DOWN ARROW key
		p_SELECT	=0x29,	//SELECT key
		p_PRINT		=0x2A,	//PRINT key
		p_EXECUTE	=0x2B,	//EXECUTE key
		p_SNAPSHOT	=0x2C,	//PRINT SCREEN key
		p_INSERT	=0x2D,	//INS key
		p_DELETE	=0x2E,	//DEL key

		p_0	=0x30,	//0 key
		p_1	=0x31,	//1 key
		p_2	=0x32,	//2 key
		p_3	=0x33,	//3 key
		p_4	=0x34,	//4 key
		p_5	=0x35,	//5 key
		p_6	=0x36,	//6 key
		p_7	=0x37,	//7 key
		p_8	=0x38,	//8 key
		p_9	=0x39,	//9 key

		p_A	=0x41,	//A key
		p_B	=0x42,	//B key
		p_C	=0x43,	//C key
		p_D	=0x44,	//D key
		p_E	=0x45,	//E key
		p_F	=0x46,	//F key
		p_G	=0x47,	//G key
		p_H	=0x48,	//H key
		p_I	=0x49,	//I key
		p_J	=0x4A,	//J key
		p_K	=0x4B,	//K key
		p_L	=0x4C,	//L key
		p_M	=0x4D,	//M key
		p_N	=0x4E,	//N key
		p_O	=0x4F,	//O key
		p_P	=0x50,	//P key
		p_Q	=0x51,	//Q key
		p_R	=0x52,	//R key
		p_S	=0x53,	//S key
		p_T	=0x54,	//T key
		p_U	=0x55,	//U key
		p_V	=0x56,	//V key
		p_W	=0x57,	//W key
		p_X	=0x58,	//X key
		p_Y	=0x59,	//Y key
		p_Z	=0x5A,	//Z key

		p_NUMPAD0	=0x60,	//Numeric keypad 0 key
		p_NUMPAD1	=0x61,	//Numeric keypad 1 key
		p_NUMPAD2	=0x62,	//Numeric keypad 2 key
		p_NUMPAD3	=0x63,	//Numeric keypad 3 key
		p_NUMPAD4	=0x64,	//Numeric keypad 4 key
		p_NUMPAD5	=0x65,	//Numeric keypad 5 key
		p_NUMPAD6	=0x66,	//Numeric keypad 6 key
		p_NUMPAD7	=0x67,	//Numeric keypad 7 key
		p_NUMPAD8	=0x68,	//Numeric keypad 8 key
		p_NUMPAD9	=0x69,	//Numeric keypad 9 key
		p_MULTIPLY	=0x6A,	//Multiply key
		p_ADD		=0x6B,	//Add key
		p_SEPARATOR	=0x6C,	//Separator key
		p_SUBTRACT	=0x6D,	//Subtract key
		p_DECIMAL	=0x6E,	//Decimal key
		p_DIVIDE	=0x6F,	//Divide key

		p_F1	=0x70,	//F1 key
		p_F2	=0x71,	//F2 key
		p_F3	=0x72,	//F3 key
		p_F4	=0x73,	//F4 key
		p_F5	=0x74,	//F5 key
		p_F6	=0x75,	//F6 key
		p_F7	=0x76,	//F7 key
		p_F8	=0x77,	//F8 key
		p_F9	=0x78,	//F9 key
		p_F10	=0x79,	//F10 key
		p_F11	=0x7A,	//F11 key
		p_F12	=0x7B,	//F12 key
		p_F13	=0x7C,	//F13 key
		p_F14	=0x7D,	//F14 key
		p_F15	=0x7E,	//F15 key
		p_F16	=0x7F,	//F16 key
		p_F17	=0x80,	//F17 key
		p_F18	=0x81,	//F18 key
		p_F19	=0x82,	//F19 key
		p_F20	=0x83,	//F20 key
		p_F21	=0x84,	//F21 key
		p_F22	=0x85,	//F22 key
		p_F23	=0x86,	//F23 key
		p_F24	=0x87,	//F24 key

		p_NUMLOCK	=0x90,	//NUM LOCK key
		p_SCROLL	=0x91,	//SCROLL LOCK key


		p_LSHIFT	=0xA0,	//Left SHIFT key
		p_RSHIFT	=0xA1,	//Right SHIFT key
		p_LCONTROL	=0xA2,	//Left CONTROL key
		p_RCONTROL	=0xA3,	//Right CONTROL key

		p_VOLUME_MUTE		=0xAD,	//Volume Mute key
		p_VOLUME_DOWN		=0xAE,	//Volume Down key
		p_VOLUME_UP			=0xAF,	//Volume Up key
		p_MEDIA_NEXT_TRACK	=0xB0,	//Next Track key
		p_MEDIA_PREV_TRACK	=0xB1,	//Previous Track key
		p_MEDIA_STOP		=0xB2,	//Stop Media key
		p_MEDIA_PLAY_PAUSE	=0xB3	//Play / Pause Media key
	};
}