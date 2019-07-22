#include <USBHID.h>
#include "shortcuts.h"

struct refresh
{
	uint32_t t1;
	uint32_t t2;
	uint8_t hz;
};


uint32_t led_bitmap = 0;
// uint32_t led_bitmap = 0x8400210;		// corners


void setup() {
	delay(1000);
	Serial1.begin(9600, SERIAL_8O1);
	Serial1.write(0x01);
	delay(100);
	Serial1.write(0x06);
	delay(100);
	Serial1.read();
	Serial1.write(0x08);

	USBHID.begin(HID_KEYBOARD);
	Keyboard.begin();
}


void loop(){
	int s;
	if(Serial1.available())
	{
		s = Serial1.read();
		if(s>=0 && s<32)
		{
			key_pressed(s);
		}
		else if(s == 0x80)			// error on led msg
		{

		}
		else if(s == 0x81)		// led msg success
		{

		}
	}
}


void key_pressed(int key)
{
	led_bitmap = led_bitmap ^ (1 << (31 - key));

	led_bitmap = led_bitmap | (1 << (31));
//	led_bitmap = led_bitmap | (1 << (30));
//	led_bitmap = led_bitmap | (1 << (29));
	led_bitmap = led_bitmap | (1 << (28));
	led_bitmap = led_bitmap | (1 << (27));
//	led_bitmap = led_bitmap | (1 << (26));
//	led_bitmap = led_bitmap | (1 << (25));
//	led_bitmap = led_bitmap | (1 << (24));
//	led_bitmap = led_bitmap | (1 << (23));
	led_bitmap = led_bitmap | (1 << (22));
	led_bitmap = led_bitmap | (1 << (21));
	led_bitmap = led_bitmap | (1 << (20));
	led_bitmap = led_bitmap | (1 << (19));
	led_bitmap = led_bitmap | (1 << (18));
	led_bitmap = led_bitmap | (1 << (17));
	led_bitmap = led_bitmap | (1 << (16));
	led_bitmap = led_bitmap | (1 << (15));
	led_bitmap = led_bitmap | (1 << (14));
	led_bitmap = led_bitmap | (1 << (13));
	led_bitmap = led_bitmap | (1 << (12));
	led_bitmap = led_bitmap | (1 << (11));
	led_bitmap = led_bitmap | (1 << (10));
	led_bitmap = led_bitmap | (1 << (9));
	led_bitmap = led_bitmap | (1 << (8));
	led_bitmap = led_bitmap | (1 << (7));
	led_bitmap = led_bitmap | (1 << (6));
	led_bitmap = led_bitmap | (1 << (5));
	led_bitmap = led_bitmap | (1 << (4));
	led_bitmap = led_bitmap | (1 << (3));
	led_bitmap = led_bitmap | (1 << (2));
	led_bitmap = led_bitmap | (1 << (1));
	led_bitmap = led_bitmap | (1 << (0));

	led_toggle();


	switch(key)
	{
	case 0:
		shortcut(SAVE);
		break;
	case 1:
		break;
	case 3:
		shortcut(TASKBAR_2);
		break;
	case 4:
		shortcut(ESC);
		break;
	case 5:
		shortcut_toggle(5, SHIFT);
		break;
	case 6:
		shortcut_toggle(6, CTRL);
		break;
	case 7:
		shortcut_toggle(7, ALT);
		break;
	case 9:
		shortcut(DEL);
		break;
	case 10:
		shortcut(CASA);
		break;
	case 11:
		shortcut(CASB);
		break;
	case 12:
		shortcut(CASC);
		break;
	case 13:
		shortcut(CASD);
		break;
	case 14:
		shortcut(CASE);
		break;
	case 15:
		shortcut(CASF);
		break;
	case 16:
		shortcut(CASG);
		break;
	case 17:
		shortcut(CASH);
		break;
	case 18:
		shortcut(CASI);
		break;
	case 19:
		shortcut(CASJ);
		break;
	case 20:
		shortcut(CASK);
		break;
	case 21:
		shortcut(CASL);
		break;
	case 22:
		shortcut(CASM);
		break;
	case 23:
		shortcut(CASN);
		break;
	case 24:
		shortcut(CASO);
		break;
	case 25:
		shortcut(CASP);
		break;
	case 26:
		shortcut(CASQ);
		break;
	case 27:
		shortcut(CUT);
		break;
	case 28:
		shortcut(UNDO);
		break;
	case 29:
		shortcut(REDO);
		break;
	case 30:
		shortcut(COPY);
		break;
	case 31:
		shortcut(PASTE);
		break;
	default:
		break;
	}
}


void led_toggle()
{
	byte msg[] = {(led_bitmap >> 24) & 0xFF, (led_bitmap >> 16) & 0xFF, (led_bitmap >> 8) & 0xFF, led_bitmap & 0xFF};
	Serial1.write(0x94);
	Serial1.write(msg, 4);
}


void shortcut(const int *keys)
{
	for(size_t i=1; i<=keys[0]; i++)
	{
		Keyboard.press((char)keys[i]);
		delay(10);
	}

	for(size_t i=keys[0]; i>=1; i--)
	{
		Keyboard.release((char)keys[i]);
		delay(10);
	}
}


void shortcut_toggle(int key, const int *keys)
{
	if(led_bitmap & (1 << (31 - key)))
	{
		for(size_t i=1; i<=keys[0]; i++)
		{
			Keyboard.press((char)keys[i]);
			delay(10);
		}
	}
	else
	{
		for(size_t i=keys[0]; i>=1; i--)
		{
			Keyboard.release((char)keys[i]);
			delay(10);
		}
	}

	
}