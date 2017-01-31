#include "Centroid.h"
#include "Pixel.h"
#include <algorithm>

// Default constructor for Centroid
Centroid::Centroid()
	:r(0.0), g(0.0), b(0.0), sum_children_r(0), sum_children_g(0), sum_children_b(0), sum_children_squared_dist(0.0)
{
}

// Constructor for Centroid that takes in RGB values
Centroid::Centroid(unsigned char r, unsigned char g, unsigned char b)
	: r((double) r), g((double) g), b((double) b), sum_children_r(0), sum_children_g(0), sum_children_b(0), sum_children_squared_dist(0.0)
{
}

// Function that sets the RGB values for this Centroid
void Centroid::set_color(unsigned char r, unsigned char g, unsigned char b) {
	this->r = r, this->g = g; this->b = b;
}

// Function that adds a Pixel to this Centroid's list of children
void Centroid::add_child(Pixel& px) {
	// Adds parent information to the Pixel
	px.dist_to_parent = euclid_dist(px, *this);
	px.parent = this;

	// Updates this Centroid's children sums
	sum_children_r += px.r, sum_children_g += px.g, sum_children_b += px.b;
	sum_children_squared_dist += pow(px.dist_to_parent, 2);

	// Adds the Pixel to this Centroid's list of children
	children.push_back(px);
}

// Function that removes a Pixel from this Centroid's list of children
void Centroid::remove_child(Pixel& px) {
	// Creates an iterator that points to the first matching child
	std::vector<Pixel>::iterator pos = std::find(children.begin(), children.end(), px);

	// Only execute if a matching child was found
	if (pos != children.end()) {
		// Removes the Pixel from this Centroid's list of children
		children.erase(pos);

		// Updates this Centroid's children sums
		sum_children_squared_dist -= pow(px.dist_to_parent, 2);
		sum_children_r -= px.r, sum_children_g -= px.g, sum_children_b -= px.b;

		// Removes parent information from the Pixel
		px.dist_to_parent = std::numeric_limits<double>::max();
		px.parent = nullptr;
	}
}

// Function that recalculates this Centroid's RGB values by taking a mean of all children
void Centroid::recalculate() {
	r = (double) sum_children_r / children.size();
	g = (double) sum_children_g / children.size();
	b = (double) sum_children_b / children.size();
}

// Static function that calculates the Euclidean distance between a Pixel and Centroid
double Centroid::euclid_dist(const Pixel& px, const Centroid& c) {
	return sqrt(pow(px.r - c.r, 2) + pow(px.g - c.g, 2) + pow(px.b - c.b, 2));
}