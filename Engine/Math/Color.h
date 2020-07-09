#pragma once

#include <Windows.h>
#include <iostream>

namespace gk
{
	struct Color
	{
		float r, g, b;

		Color() : r{ 0 }, g{ 0 }, b{ 0 } {};
		Color(float r, float g, float b) : r{ r }, g{ g }, b{ b } {};
		Color(int r, int g, int b) : r{ static_cast<float>(r) }, g{ static_cast<float>(g) }, b{ static_cast<float>(b) } {}

		float& operator [] (size_t index) { return (&r)[index]; }
		const float& operator [] (size_t index) const { return (&r)[index]; }

		void set(float r, float g, float b) { this->r = r; this->g = g; this->b = b; }

		Color operator + (const Color& c) const { return Color{ r + c.r, g + c.g, b + c.b }; }
		Color operator - (const Color& c) const { return Color{ r - c.r, g - c.g, b - c.b }; }
		Color operator * (const Color& c) const { return Color{ r * c.r, g * c.g, b * c.b }; }
		Color operator / (const Color& c) const { return Color{ r / c.r, g / c.g, b / c.b }; }

		Color operator + (float s) const { return Color{ r + s, g + s, b + s }; }
		Color operator - (float s) const { return Color{ r - s, g - s, b - s }; }
		Color operator * (float s) const { return Color{ r * s, g * s, b * s }; }
		Color operator / (float s) const { return Color{ r / s, g / s, b / s }; }

		Color& operator += (const Color& c) { r += c.r; g += c.g; b += c.b; return *this; }
		Color& operator -= (const Color& c) { r -= c.r; g -= c.g; b -= c.b; return *this; }
		Color& operator *= (const Color& c) { r *= c.r; g *= c.g; b *= c.b; return *this; }
		Color& operator /= (const Color& c) { r /= c.r; g /= c.g; b /= c.b; return *this; }

		Color& operator += (float s) { r += s; g += s; b += s; return *this; }
		Color& operator -= (float s) { r -= s; g -= s; b -= s; return *this; }
		Color& operator *= (float s) { r *= s; g *= s; b *= s; return *this; }
		Color& operator /= (float s) { r /= s; g /= s; b /= s; return *this; }

		operator COLORREF() const { return pack888(); }
		friend std::istream& operator >> (std::istream& stream, Color& c);

		COLORREF pack888() const;
	};

	inline COLORREF Color::pack888() const
	{
		BYTE _r = static_cast<BYTE>(r * 255.0f);
		BYTE _g = static_cast<BYTE>(g * 255.0f);
		BYTE _b = static_cast<BYTE>(b * 255.0f);

		return (_r) | (_g << 8) | (_b << 16);
	}
}