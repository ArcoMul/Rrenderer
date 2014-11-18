#pragma once

#include "Rrenderer.h"

namespace Rr
{
	union ColorU {
		// first representation (member of union) 
		struct asRGBA {
			unsigned char a, b, g, r;
		} asRGBA;

		// second representation (member of union) 
		unsigned int asInt;
	};

	class RRENDERER_API Color
	{
	public:
		Color() {
			setRgba(1, 0, 0, 1);
		}
		Color(int r, int g, int b, int a) {
			setRgba(r, g, b, a);
		}
		void setRgba(int r, int g, int b, int a) {
			this->r(r);
			this->g(g);
			this->b(b);
			this->a(a);
		}
		void r(int r) {
			value.asRGBA.r = r;
		}
		void g(int g) {
			value.asRGBA.g = g;
		}
		void b(int b) {
			value.asRGBA.b = b;
		}
		void a(int a) {
			value.asRGBA.a = a;
		}
		unsigned char r() {
			return value.asRGBA.r;
		}
		unsigned char g() {
			return value.asRGBA.g;
		}
		unsigned char b() {
			return value.asRGBA.b;
		}
		unsigned char a() {
			return value.asRGBA.a;
		}
		~Color() {

		}
	private:
		ColorU value;
	};
}

