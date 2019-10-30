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
    const String keys = "{path p         |../data/dog.jpg   | path to file              }"
                        "{ksize k        |21                | Gaussian Blur Kernel Size }";
    
    CommandLineParser parser(argc, argv, keys);
    String path = parser.get<std::string>("path");
    int ksize = parser.get<int>("ksize");
    Mat image_gray, image_gray_blur, output;

    // Reads input image
    Mat image = imread(path, cv::IMREAD_UNCHANGED);

    // Resizes the image if needed
    //resize(image,image,Size(),0.5,0.5);

    cvtColor(image,image_gray,COLOR_BGR2GRAY);

    // Blurs the image with gaussian blur
    GaussianBlur(image_gray,image_gray_blur,Size(ksize,ksize),0,0);

    // Applies the dodge
    divide(image_gray, image_gray_blur,output,256,-1);

    // Show image
    showImage("sketch", output);
    
}
