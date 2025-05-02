#include <iostream>
#include "Image_Class.h"

using namespace std;

// Function to convert a color image to grayscale
void convert_to_Grayscale(Image& edited_image) {
    // Loop through each pixel of the image
    for (int i = 0; i < edited_image.width; ++i) {
        for (int j = 0; j < edited_image.height; ++j) {
            unsigned int average_intensity = 0;

            // Calculate the average intensity across color channels
            for (int k = 0; k < edited_image.channels; ++k) {
                average_intensity += edited_image(i, j, k);
            }
            average_intensity /= edited_image.channels;
            for (int k = 0; k < edited_image.channels; ++k) {
                // Set all color channels to the calculated average intensity
                edited_image(i, j, k) = average_intensity;
            }
        }
    }
}

int main() {
    // Load the image
    Image edited_image;
    if (edited_image.loadNewImage("building.jpg")) {
        cout << "Image loaded successfully" << endl;
    }
    else {
        cout << "Failed to load image" << endl;
        return 1; // Exit the program if image loading fails
    }

    // Convert the loaded image to grayscale
    convert_to_Grayscale(edited_image);

    // Save the grayscale image
    if (edited_image.saveImage("building_grayscale.png")) {
        cout << "Grayscale image saved successfully." << endl;
    }
    else {
        cout << "Failed to save grayscale image." << endl;
        return 1; // Exit the program if image saving fails
    }

    return 0;
}
