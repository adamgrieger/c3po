#include "Pixel.h"
#include <cfloat>

// Constructor for Pixel that takes in RGBA values
Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	: r(r), g(g), b(b), a(a), dist_to_parent(DBL_MAX), parent(nullptr)
{
}

// Overloaded == operator for Pixel comparisons
bool Pixel::operator==(const Pixel& px) {
	return (r == px.r) && (g == px.g) && (b == px.b) && (a == px.a) && (dist_to_parent == px.dist_to_parent);
}