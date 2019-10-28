#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void showImage(String name, Mat image)
{
    imshow(name, image);
    waitKey(0);
}

void saveImage(String name, Mat image)
{
    // Compression parameters for imwrite
    vector<int> compression_params;
    compression_params.push_back(IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);

    // Clears the output folder (Only works in Linux! I didn't want to include a lib dependency to do cross-plataform checking)
    system("exec rm -r ../output/*");

    imwrite("../output/" + name + ".png", image);
}

int main(int argc, const char **argv)
{
    // Arguments {name first_letter | default_value | description }
    const String keys = "{path p         |../data/dog.jpg   | path to file          }"
                        "{sigma s        |3                 | Standard Deviation    }"
                        "{kernel_size k  |3                 | Sharpening Kernel Size}";
    
    CommandLineParser parser(argc, argv, keys);
    String path = parser.get<std::string>("path");
    int sigma = parser.get<int>("sigma");
    int kernel_size = parser.get<int>("kernel_size");
    Mat image_gray, image_gray_inverted, output;

    // Reads input image
    Mat image = imread(path, cv::IMREAD_UNCHANGED);

    // Resizes the image if needed
    //resize(image,image,Size(),0.5,0.5);

    cvtColor(image,image_gray,COLOR_BGR2GRAY);

    // Inverts the image
    image_gray_inverted = 255 - image_gray;

    // Blurs the image with gaussian blur
    GaussianBlur(image_gray_inverted,image_gray_inverted,Size(),sigma,sigma);

    // Applies the dodge
    divide(image_gray, 255 - image_gray_inverted,output,256,-1);

    // Show image
    showImage("sketch", output);
    
}
