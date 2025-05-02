#include <iostream>
#include "Image_class.h"
#include <cmath>

using namespace std;

void convert_to_Grayscale(Image& edited_image) {
    for (int i = 0; i < edited_image.width; ++i) {
        for (int j = 0; j < edited_image.height; ++j) {
            unsigned int average_intensity = 0;
            for (int k = 0; k < edited_image.channels; ++k) {
                average_intensity += edited_image(i, j, k);
            }
            average_intensity /= edited_image.channels;
            for (int k = 0; k < edited_image.channels; ++k) {
                edited_image(i, j, k) = average_intensity;
            }
        }
    }
}

void edge_detection(Image& image) {
    Image edges(image.width, image.height);
    for (int i = 0; i < edges.height; ++i) {
        for (int j = 0; j < edges.width; ++j) {
            edges(j, i, 0) = edges(j, i, 1) = edges(j, i, 2) = 255;
        }
    }

    int h_sobel[3][3] = {{-1, 0, 1},{-2, 0, 2},{-1, 0, 1}};
    int v_sobel[3][3] = {{-1, -2, -1},{0,  0,  0},{1,  2,  1}};

    for (int i = 1; i < image.height - 1; ++i) {
        for (int j = 1; j < image.width - 1; ++j) {
            int h_sum = 0;
            int v_sum = 0;

            for (int x = -1; x <= 1; ++x) {
                for (int y = -1; y <= 1; ++y) {
                    int x_index = x + 1 , y_index = y + 1;
                    int pixel_value = image(j + y, i + x, 0);
                    h_sum += pixel_value * h_sobel[x_index][y_index];
                    v_sum += pixel_value * v_sobel[x_index][y_index];
                }
            }

            if ( sqrt(pow(h_sum, 2) + pow(v_sum, 2))  > 100 ) {
                edges(j, i, 0) = edges(j, i, 1) = edges(j, i, 2) = 0;
            }
        }
    }

    image = edges;
}

int main() {
    Image image;
    image.loadNewImage("photographer.bmp");

    convert_to_Grayscale(image);

    edge_detection(image);

    if (image.saveImage("result.jpg")) {
        cout << "Image saved successfully." << endl;
    }

    return 0;
}
