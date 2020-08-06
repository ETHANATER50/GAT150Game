#pragma once

#include <windows.h>

namespace ew {
	struct Color {
		float r, g, b, a;

		Color() : r{ 0 }, g{ 0 }, b{ 0 }, a{ 1 } {};
		Color(float r, float g, float b, float a = 1.0f) : r{ r }, g{ g }, b{ b }, a{ a } {}

		float& operator [] (size_t index) { return (&r)[index]; }
		const float& operator [] (size_t index) const { return (&r)[index]; }

		void set(float _r, float _g, float _b) { r = _r; g = _g; b = _b; }

		Color operator + (const Color& c) const { return Color{ r + c.r, g + c.g, b + c.b }; }
		Color operator - (const Color& c) const { return Color{ r - c.r, g - c.g, b - c.b }; }
		Color operator * (const Color& c) const { return Color{ r * c.r, g * c.g, b * c.b }; }
		Color operator / (const Color& c) const { return Color{ r / c.r, g / c.g, b / c.b }; }

		Color operator + (float s) const { return Color{ r + s, g + s, b + s }; }
		Color operator - (float s) const { return Color{ r - s, g - s, b - s }; }
		Color operator * (float s) const { return Color{ r * s, g * s, b * s }; }
		Color operator / (float s) const { return Color{ r / s, g / s, b / s }; }
		
		Color& operator += (float s) { r += s, g += s, b += s; return *this; }
		Color& operator -= (float s) { r -= s, g -= s, b -= s; return *this; }
		Color& operator *= (float s) { r *= s, g *= s, b *= s; return *this; }
		Color& operator /= (float s) { r /= s, g /= s, b /= s; return *this; }
		
		Color& operator += (const Color& c) { r += c.r, g += c.g, b += c.b; return *this; }
		Color& operator -= (const Color& c) { r -= c.r, g -= c.g, b -= c.b; return *this; }
		Color& operator *= (const Color& c) { r *= c.r, g *= c.g, b *= c.b; return *this; }
		Color& operator /= (const Color& c) { r /= c.r, g /= c.g, b /= c.b; return *this; }

		friend std::istream& operator >> (std::istream& stream, Color& c);

		SDL_Color pack888() const;

		operator SDL_Color() const { return pack888(); }

		static const Color red;
		static const Color white;
		static const Color blue;
		static const Color green;

	};

	inline SDL_Color Color::pack888() const {
		SDL_Color color;
		color.r = static_cast<BYTE>(r * 255.0f);
		color.g = static_cast<BYTE>(g * 255.0f);
		color.b = static_cast<BYTE>(b * 255.0f);
		color.a = static_cast<BYTE>(a * 255.0f);

		return color;
	}
}