#include <iostream>
#include "Image_class.h"
#include <string>

using namespace std;

// Function to resize an image to the fixed dimensions
void resize_image(Image& image, int new_width, int new_height) {
    // Calculate scaling factors for width and height
    double width_ratio = image.width / (double)new_width;
    double height_ratio = image.height / (double)new_height;

    // Create a new image with the wanted dimensions
    Image resized_image(new_width, new_height);

    // Resize the image using nearest neighbor interpolation
    for (int i = 0; i < new_width; ++i) {
        for (int j = 0; j < new_height; ++j) {
            // Calculate the corresponding pixel position in the original image
            int start_i = i * width_ratio, start_j = j * height_ratio;

            // Ensure the new pixel position is within bounds
            int end_i = min(start_i, image.width - 1);
            int end_j = min(start_j, image.height - 1);

            for (int k = 0; k < image.channels; ++k) {
                // Closest neighbor interpolation
                resized_image(i, j, k) = image(end_i, end_j, k);
            }
        }
    }

    // Update the original image with the resized image
    image = resized_image;
}

// Function to merge two images based on the dimensions
void merge_images(const Image& first_image, const Image& second_image, Image& result_image, string &choice) {
    // Calculate the dimensions of the merged image
    int max_width = max(first_image.width, second_image.width);
    int max_height = max(first_image.height, second_image.height);
    int min_width = min(first_image.width, second_image.width);
    int min_height = min(first_image.height, second_image.height);

    // First case : Images are the same size
    if (first_image.width == second_image.width && first_image.height == second_image.height) {
        result_image = Image(max_width, max_height);
        for (int i = 0; i < max_width; ++i) {
            for (int j = 0; j < max_height; ++j) {
                for (int k = 0; k < result_image.channels; ++k) {
                    // Merge pixel values directly by averaging
                    result_image(i, j, k) = (first_image(i, j, k) + second_image(i, j, k)) / 2;
                }
            }
        }
    }
    // Second case : Images are different sizes
    else {
        // Case : Resize both images to the largest dimensions
        if (choice == "1") {
            // Create a result image with the dimensions of the merged images
            result_image = Image(max_width, max_height);
            Image resized_first_image = first_image;
            Image resized_second_image = second_image;
            resize_image(resized_first_image, max_width, max_height);
            resize_image(resized_second_image, max_width, max_height);

            // Merge the resized images
            for (int i = 0; i < max_width; ++i) {
                for (int j = 0; j < max_height; ++j) {
                    for (int k = 0; k < result_image.channels; ++k) {
                        // Merge pixel values directly by averaging
                        result_image(i, j, k) = (resized_first_image(i, j, k) + resized_second_image(i, j, k)) / 2;
                    }
                }
            }
        }
        // Case : Merge the common area of the smaller width and height
        else if (choice == "2") {
            // Create a result image with the dimensions of the merged images
            result_image = Image(min_width, min_height);

            // Merge the common area
            for (int i = 0; i < min_width; ++i) {
                for (int j = 0; j < min_height; ++j) {
                    for (int k = 0; k < result_image.channels; ++k) {
                        // Merge pixel values directly by averaging
                        result_image(i, j, k) = (first_image(i, j, k) + second_image(i, j, k)) / 2;
                    }
                }
            }
        }
    }
}

int main() {
    Image first_image, second_image, result_image;
    string choice;

    // Load the images
    first_image.loadNewImage("toy1.jpg");
    second_image.loadNewImage("toy2.jpg");

    while (true) {
        // Display menu options
        cout << "Available options:" << endl;
        cout << "1. Resize both images to the largest dimensions then merge." << endl;
        cout << "2. Merge the common area of the smaller width and height." << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // Validate the user's choice
        if (choice == "1" || choice == "2") {
            // Exit the loop if the choice is valid
            break;
        }
        // Invalid input option
        else {
            cout << "Invalid input. Please enter '1' or '2' to continue." << endl;
        }
    }
    // Call the function to merge the images based on user's choice
    merge_images(first_image, second_image, result_image, choice);

    // Save the merged image
    if (result_image.saveImage("merged_image.jpg")) {
        cout << "The image saved successfully." << endl;
    }

    return 0;
}
