#include "Centroid.h"
#include "KMeans.h"
#include "Pixel.h"
#include <cmath>
#include <ctime>
#include <iostream>

KMeans::KMeans(std::vector<unsigned char> img, unsigned int w, unsigned int h, unsigned short int k) 
	: img(img), width(w), height(h), k(k)
{
	// Seeds RNG with current time
	srand((unsigned int) time(NULL));

	// Adds each pixel in the image to a list of Pixels
	for (size_t i = 0; i < img.size(); i += 4) {
		pixels.push_back(Pixel(img[i], img[i + 1], img[i + 2], img[i + 3]));
	}
	
	// Generates a specified number of empty Centroids
	for (int i = 0; i < k; i++) {
		centroids.push_back(Centroid());
	}

	// Picks a random Pixel and sets the first Centroid's RGB values to that Pixel's RGB values
	int idx = rand() % (width * height);
	centroids[0].set_color(img[idx * 4], img[idx * 4 + 1], img[idx * 4 + 2]);

	// Makes every Pixel a child of the first (and only non-empty) Centroid
	for (size_t i = 0; i < pixels.size(); i++) {
		centroids[0].add_child(pixels[i]);
	}

	// Calls the main procedure for k-means++
	std::cout << "Performing k-means++ clustering..." << std::endl;
	kpp_init();
	lloyd();

	// Prints out the resulting colors generated from the image
	print_centroids();
}

// Functions that returns a LodePNG-compatible list of the Pixels for the quantized image
std::vector<unsigned char> KMeans::get_quantized_img() {
	std::vector<unsigned char> quantized_img;

	// Adds the RGBA values of the list of Pixels to the quantized image
	for (size_t i = 0; i < pixels.size(); i++) {
		quantized_img.push_back((unsigned char) round(pixels[i].parent->r));
		quantized_img.push_back((unsigned char) round(pixels[i].parent->g));
		quantized_img.push_back((unsigned char) round(pixels[i].parent->b));
		quantized_img.push_back(pixels[i].a);
	}

	return quantized_img;
}

// Function that calculates the sum of squared distances of every Pixel
double KMeans::sum_squared_dist() {
	double squared_dist_sum = 0.0;

	// Goes through each Centroid adding the squared distances of Pixels to the sum
	for (size_t i = 0; i < k; i++) {
		squared_dist_sum += centroids[i].sum_children_squared_dist;
	}

	return squared_dist_sum;
}

// Function that uses k-mean++ seeding to optimally initialize the rest of the clusters
// This method of seeding uses a probability distribution of squared distances to spread clusters out
void KMeans::kpp_init() {
	// Seeds RNG with current time
	srand((unsigned int) time(NULL));

	// Executes for every Centroid that hasn't properly been initialized yet
	for (int i = 1; i < k; i++) {
		// Generate random distance value from probability distribution
		double rand_dist = ((double) rand() / RAND_MAX) * sum_squared_dist();
		double dist_sum = 0.0;

		// Goes through the Pixels to find the one that has been randomly selected
		for (size_t j = 0; j < pixels.size(); j++) {
			if (pow(dist_sum + pixels[j].dist_to_parent, 2) > rand_dist) {
				// Stops search and initializes the next Centroid with this Pixel's RGB values
				centroids[i].set_color(pixels[j].r, pixels[j].g, pixels[j].b);
				break;
			}
			else {
				// Adds distance to sum and keeps going
				dist_sum += pow(pixels[j].dist_to_parent, 2);
			}
		}

		// Reassigns the pixels up to the amount of Centroids that have currently been initialized
		reassign_pixels(i);
	}
}

// Function that goes through and updates Pixels and recalculates Centroids to make Centroids approach prominent colors
void KMeans::lloyd() {
	// Goes through 100 iterations of updating Pixels and recalculating Centroids
	for (int i = 0; i < 100; i++) {
		reassign_pixels(k - 1);
		recalculate_centroids();
	}
}

// Function that goes through all Pixels and assigns them to the nearest Centroid
void KMeans::reassign_pixels(int n) {
	for (size_t i = 0; i < pixels.size(); i++) {
		bool parent_changed = false;
		double min_dist = pixels[i].dist_to_parent;
		Centroid* min_centroid = pixels[i].parent;

		// Executes for each Centroid
		for (int j = 0; j <= n; j++) {
			// Calculates Euclidean distance from Pixel to Centroid
			double dist = Centroid::euclid_dist(pixels[i], centroids[j]);

			// Updates current minimum if this Centroid is currently closest to the Pixel
			if (dist < min_dist) {
				min_dist = dist;
				min_centroid = &centroids[j];
				parent_changed = true;
			}
		}

		// Removes the Pixel from its previous parent and adds it to a new Centroid
		if (parent_changed) {
			pixels[i].parent->remove_child(pixels[i]);
			min_centroid->add_child(pixels[i]);
		}
	}
}

// Recalculates every Centroid by taking the mean RGB values of their children
void KMeans::recalculate_centroids() {
	for (int i = 0; i < k; i++) {
		centroids[i].recalculate();
	}
}

// Prints out the resulting Centroid's RGB values
void KMeans::print_centroids() {
	for (int i = 0; i < k; i++) {
		std::cout << "(" << round(centroids[i].r) << ", " << round(centroids[i].g) << ", " << round(centroids[i].b) << ")" << std::endl;
	}
}