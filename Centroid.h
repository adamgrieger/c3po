#ifndef CENTROID_H
#define CENTROID_H

#include "Pixel.h"
#include <vector>

// Forward declaration of Pixel class
class Pixel;

// Interface defining Centroid class
class Centroid {
public:
	Centroid();
	Centroid(unsigned char, unsigned char, unsigned char);
	double r, g, b;
	unsigned int sum_children_r, sum_children_g, sum_children_b;
	double sum_children_squared_dist;
	void set_color(unsigned char, unsigned char, unsigned char);
	void add_child(Pixel &);
	void remove_child(Pixel &);
	void recalculate();
	static double euclid_dist(const Pixel &, const Centroid &);
private:
	std::vector<Pixel> children;
};

#endif