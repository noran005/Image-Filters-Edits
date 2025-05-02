#include <iostream>
#include "Image_Class.h"

using namespace std;

// Function to adjust the brightness of an image
void adjust_brightness(Image& edited_image, double factor) {
    // Loop through each pixel of the image
    for (int i = 0; i < edited_image.width; ++i) {
        for (int j = 0; j < edited_image.height; ++j) {
            for (int k = 0; k < edited_image.channels; ++k) {
                // Get the intensity value of the pixel
                int intensity = edited_image(i, j, k);

                // Adjust the intensity based on the given factor
                intensity = intensity * factor;

                // Clamp the intensity value between 0 and 255
                if (intensity > 255) {
                    intensity = 255; // Clamp to maximum intensity
                }
                else if (intensity < 0) {
                    intensity = 0; // Clamp to minimum intensity
                }
                // Set the adjusted intensity back to the pixel
                edited_image(i, j, k) = intensity;
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

    while (true) {
        // Process the user's choice
        int choice;
        cout << "1 - darker\n2 - lighter\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Darker or lighter choice option
        if (choice == 1) {
            adjust_brightness(edited_image, 0.5);
            cout << "Reduced brightness for a darker effect." << endl;
        }
        else if (choice == 2) {
            adjust_brightness(edited_image, 1.5);
            cout << "Increased brightness for a lighter effect." << endl;
        }
        // Invalid choice option
        else {
            cout << "Invalid input. Please select '1' for darker or '2' for lighter to continue." << endl;
            continue;
        }

        if (edited_image.saveImage("building_adjusted_brightness.jpg")) {
            cout << "Image edited and saved successfully." << endl;
        }
        else {
            cout << "Failed to save edited image." << endl;
            return 1; // Exit the program if image saving fails
        }
        // Exit the loop after processing user's choice
        break;
    }

    return 0;
}
