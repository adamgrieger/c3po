#ifndef KMEANS_H
#define KMEANS_H

#include "Centroid.h"
#include "Pixel.h"
#include <vector>

// Interface defining KMeans class
class KMeans {
public:
	KMeans(std::vector<unsigned char>, unsigned int, unsigned int, unsigned short int);
	std::vector<unsigned char> get_quantized_img();
private:
	double sum_squared_dist();
	void kpp_init();
	void lloyd();
	void reassign_pixels(int);
	void recalculate_centroids();
	void print_centroids();
	const std::vector<unsigned char> img;
	const unsigned int width;
	const unsigned int height;
	const unsigned short int k;
	std::vector<Pixel> pixels;
	std::vector<Centroid> centroids;
	std::vector<Centroid> old_centroids;
};

#endif