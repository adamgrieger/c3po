#include "KMeans.h"
#include "lodepng.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {

	// Argument parsing
	if (argc == 1) {
		// No image given
		std::cout << "Please specify an image to analyze." << std::endl;
	}
	else if (argc == 2) {
		// Image given but no amount of colors to generate
		std::cout << "Please specify how many colors you want to generate." << std::endl;
	}
	else if (argc == 3) {

		// Argument values given
		std::string file_name = argv[1];
		unsigned int num_colors = atoi(argv[2]);

		// Variables for LodePNG use
		std::vector<unsigned char> img;
		unsigned int width, height;

		// Decodes PNG and stores any error message
		unsigned int err_input = lodepng::decode(img, width, height, file_name);

		// Shows error if any and then exits program
		if (err_input) {
			std::cout << "Decoder Error " << err_input << ": " << lodepng_error_text(err_input) << std::endl;
			exit(1);
		}

		// Initializes KMeans object for image analysis
		KMeans test(img, width, height, num_colors);

		// Encodes quantized PNG and stores any error message
		unsigned int err_output = lodepng::encode("quantized_" + file_name, test.get_quantized_img(), width, height);

		// Show error if any and then exits program
		if (err_output) {
			std::cout << "Encoder Error " << err_output << ": " << lodepng_error_text(err_output) << std::endl;
			exit(1);
		}
	}
	else {
		std::cout << "Too many arguments." << std::endl;
	}

	return 0;
}