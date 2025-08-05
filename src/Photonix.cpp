#include <Arduino.h>
#include <FastLED.h>

#include "Photonix.h"

using namespace Qybercom::Photonix;

void Photonix::_init (unsigned short pin, unsigned int length, String name) {
	this->_pin = pin;
	this->_length = length;
	this->_name = name;
	this->_initialized = false;

	this->_led = (CRGB*)malloc(sizeof(CRGB) * this->_length);
    switch (pin) {
        FLC_PINS
		default: break;
    }

	this->Brightness(255);
	this->Clear();
}

Photonix::Photonix (unsigned short pin, unsigned int length) {
	this->_init(pin, length, "");
}

Photonix::Photonix (unsigned short pin, unsigned int length, String name) {
	this->_init(pin, length, name);
}

unsigned short Photonix::Pin () {
	return this->_pin;
}

unsigned int Photonix::Length () {
	return this->_length;
}

String Photonix::Name () {
	return this->_name;
}

Photonix* Photonix::Brightness (int value) {
	FastLED.setBrightness(value);

	return this;
}

Photonix* Photonix::Set (unsigned int i, int r, int g, int b) {
	this->_led[i].setRGB(r, g, b);

	return this;
}

Photonix* Photonix::Show () {
	FastLED.show();

	return this;
}

Photonix* Photonix::SetAndShow (unsigned int i, int r, int g, int b) {
	return this->Set(i, r, g, b)->Show();
}

Photonix* Photonix::Fill (int r, int g, int b) {
	unsigned int i = 0;

	while (i < this->_length) {
		this->Set(i, r, g, b);

		i++;
	}

	return this;
}

Photonix* Photonix::FillAndShow (int r, int g, int b) {
	return this->Fill(r, g, b)->Show();
}

Photonix* Photonix::Clear () {
	return this->FillAndShow(0, 0, 0);
}

Photonix* Photonix::Sectors (unsigned int count) {
	this->_sectors = count;

	return this;
}

Photonix* Photonix::SectorFill (unsigned int sector, int r, int g, int b, bool clearOther, int start, int end, int areas) {
	int s = start < 0 ? 0 : start;//this->_ledStart;
	int e = end < 0 ? this->_length : end;//this->_ledStart + 45;
	int i = s;
	int sectorSize = (e - s/*0*//*this->_ledStart*/) / (this->_sectors / (areas < 1 ? 1 : areas));
	int sectorStart = 0/*s*//*0*//*this->_ledStart*/ + ((sector - 1) * sectorSize);
	int sectorEnd = sectorStart + sectorSize;

	//Serial.println("[led] " + String(sector) + String(" ") + String(s) + String(" ") + String(e) + String(" ") + String(sectorSize) + String(" ") + String(sectorStart) + String(" ") + String(sectorEnd));

	while (i < e) {
		if (i >= sectorStart && i < sectorEnd) this->Set(i, r, g, b);
		else {
			if (clearOther)
				this->Set(i, 0, 0, 0);
		}

		i++;
	}

	return this;
}

Photonix* Photonix::SectorFillAndShow (unsigned int sector, int r, int g, int b, bool clearOther, int start, int end, int areas) {
	return this->SectorFill(sector, r, g, b, clearOther, start, end, areas)->Show();
}

Photonix* Photonix::SectorClear (unsigned int sector, int start, int end, int areas) {
	return this->SectorFillAndShow(sector, 0, 0, 0, true, start, end, areas);
}

Photonix* Photonix::Lerp (int i, int r1, int g1, int b1, int r2, int g2, int b2, int step, int max, bool ret) {
	float t;

	if (ret) {
		max = max * 2;
		int mid = max / 2;

		if (step <= mid) {
			t = (float)step / (float)mid;
		}
		else {
			t = (float)(max - step) / (float)mid;
		}
	}
	else {
		t = (float)step / (float)max;
	}

	int r = (int)((1.0 - t) * r1 + t * r2);
	int g = (int)((1.0 - t) * g1 + t * g2);
	int b = (int)((1.0 - t) * b1 + t * b2);

	if (r < 0) r = 0; if (r > 255) r = 255;
	if (g < 0) g = 0; if (g > 255) g = 255;
	if (b < 0) b = 0; if (b > 255) b = 255;

	return this->Set(i, r, g, b);
}

bool Photonix::Initialized () {
	bool out = this->_initialized;

	this->_initialized = true;

	return out;
}

void Photonix::AnimationRainbow (unsigned long cursor, int r, int g, int b) {
	unsigned int i = 0;

	while (i < this->_length) {
		this->_led[i] = CHSV((cursor + i) * r, g, b);

		i++;
	}
}