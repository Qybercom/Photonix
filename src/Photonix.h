#pragma once

#include <Arduino.h>
#include <FastLED.h>

namespace Qybercom {
	namespace Photonix {
		#define FLC(n) case n: FastLED.addLeds<WS2812, n, GRB>(this->_led, this->_length); break;
		#define FLC_PINS \
		    FLC(0)  FLC(1)  FLC(2)  FLC(3)  FLC(4)  FLC(5) \
			FLC(11) FLC(12) FLC(13) FLC(14) FLC(15) FLC(16) FLC(17) FLC(18) FLC(19) \
			FLC(21) FLC(22) FLC(23) FLC(25) FLC(26) FLC(27) FLC(32) FLC(33)

		class Photonix {
			private:
				CRGB* _led;
				unsigned short _pin;
				unsigned int _length;
				String _name;
				bool _initialized;
				unsigned int _sectors;

				void _init(unsigned short pin, unsigned int length, String name);

			public:
				Photonix(unsigned short pin, unsigned int length);
				Photonix(unsigned short pin, unsigned int length, String name);

				unsigned short Pin();
				unsigned int Length();
				String Name();

				Photonix* Brightness(int value);

				Photonix* Set(unsigned int i, int r, int g, int b);
				Photonix* Show();
				Photonix* SetAndShow(unsigned int i, int r, int g, int b);

				Photonix* Fill(int r, int g, int b);
				Photonix* FillAndShow(int r, int g, int b);
				Photonix* Clear();
				Photonix* Lerp(int i, int r1, int g1, int b1, int r2, int g2, int b2, int step, int max, bool ret);

				Photonix* Sectors(unsigned int count);
				Photonix* SectorFill(unsigned int sector, int r, int g, int b, bool clearOther = false, int start = -1, int end = -1, int areas = -1);
				Photonix* SectorFillAndShow(unsigned int sector, int r, int g, int b, bool clearOther = false, int start = -1, int end = -1, int areas = -1);
				Photonix* SectorClear(unsigned int sector, int start = -1, int end = -1, int areas = -1);

				bool Initialized();

				void AnimationRainbow(unsigned long cursor, int r = 5, int g = 255, int b = 150);
		};
	}
}