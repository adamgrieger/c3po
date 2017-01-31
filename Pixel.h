#ifndef PIXEL_H
#define PIXEL_H

// Forward declaration of Centroid class
class Centroid;

// Interface defining Pixel class
class Pixel {
public:
	Pixel(unsigned char, unsigned char, unsigned char, unsigned char);
	bool operator==(const Pixel &);
	unsigned char r, g, b, a;
	double dist_to_parent;
	Centroid* parent;
};

#endif