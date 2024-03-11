/**
 * Cesar Guerrero
 * 03/06/2024
 * Getting started with Images - OpenCV
 * 
 * Learning Topics:
 * - Reading an image
 * - Checking image attribtues like datatype and shape
 * - Matrix representation of an image
 * - Color Images and splitting/merging image channels
 * - Displaying images
 * - Saving images
*/

#include <iostream>
#include <string>
#include <chrono>
//OpenCV Libraries
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

int main(){

    //Reading in an image in grayscale
    std::cout << "Displaying grayscale matrix\n";
    cv::Mat gImage = cv::imread("images/checkerboard_18x18.png", 0);
    //This will show our matrix for this simple square image -- 18 rows and 18 columns
    std::cout << gImage << "\n\n";

    //Read in a color image
    std::cout << "Color matrix attributes\n";
    cv::Mat cImage = cv::imread("images/coca-cola-logo.png", 1);

    //Attributes -- This shows the resolution in pixels
    std::cout << "Pixel dimensions of our image: " << cImage.size << "\n";
    std::cout << "Data type of each matrix element: " << cImage.type() << "\n";
    std::cout << "Number of channels: " << cImage.channels() << "\n";

    //Now lets show our images
    cv::imshow("Grayscale Image", gImage);
    cv::waitKey(0);
    cv::imshow("Color Image", cImage);
    cv::waitKey(0);
    
    //Splitting and merging channels
    //Define a vector that will contain cv::Mat objects
    std::vector<cv::Mat> bgrChannels;
    cv::split(cImage, bgrChannels);
    //Show the individual channels -- Recall that 0 is black and 255 is white
    cv::imshow("Blue Channel", bgrChannels[0]);
    cv::waitKey(0);
    cv::imshow("Green Channel", bgrChannels[1]);
    cv::waitKey(0);
    cv::imshow("Red Channel", bgrChannels[2]);
    cv::waitKey(0);

    //Merge the channels back together
    cv::Mat mergedImage;
    cv::merge(bgrChannels, mergedImage);
    cv::imshow("Merged Image", mergedImage);
    cv::waitKey(0);

    

    return 0;
}

