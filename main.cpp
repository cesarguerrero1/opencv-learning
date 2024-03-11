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
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

int main(){

    //Reading in an image in grayscale
    std::cout << "Displaying grayscale matrix\n";
    cv::Mat gImage = cv::imread("images/checkerboard_18x18.png", 0);
    //This will show our matrix for this simple square image -- 18 rows and 18 columns
    std::cout << gImage << "\n\n";

    std::cout << "Grayscale matrix attributes\n";
    std::cout << "Pixel dimensions of our image: " << gImage.size << "\n";
    std::cout << "Data type of each matrix element: " << gImage.type() << "\n";
    std::cout << "Number of channels: " << gImage.channels() << "\n";

    //Read in a color image
    std::cout << "Color matrix attributes\n";
    cv::Mat cImage = cv::imread("images/coca-cola-logo.png", 1);
    std::cout << "Pixel dimensions of our image: " << cImage.size << "\n";
    std::cout << "Data type of each matrix element: " << cImage.type() << "\n";
    std::cout << "Number of channels: " << cImage.channels() << "\n";

    //Now lets show our images
    cv::imshow("Grayscale Image", gImage);
    cv::waitKey(0);
    cv::imshow("Color Image", cImage);
    cv::waitKey(0);
    
    //Splitting and merging channels
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

    //Convert color spaces
    cv::Mat convertedImage;
    cv::cvtColor(cImage, convertedImage, cv::COLOR_BGR2RGB);
    cv::imshow("Converted Image - We went from GBR(OpenCV Default) to RGB", convertedImage);
    cv::waitKey(0);
    
    //Modifying a color channel
    cv::Mat nzImage = cv::imread("images/New_Zealand_Lake.jpg", 1);
    cv::imshow("Original New Zealand Image", nzImage);
    cv::waitKey(0);
    //Convert to HSV - modify the hue channel - convert back to BGR
    cv::Mat nzImageCopy;
    cv::cvtColor(nzImage, nzImageCopy, cv::COLOR_BGR2HSV);

    std::vector<cv::Mat> hsvChannels;
    cv::split(nzImageCopy, hsvChannels);
    //Modify the hue channel
    hsvChannels[0] += 50;
    //Merge the channels back together and convert back to BGR
    cv::Mat modifiedNZImage;
    cv::merge(hsvChannels, modifiedNZImage);
    cv::cvtColor(modifiedNZImage, modifiedNZImage, cv::COLOR_HSV2BGR);
    cv::imshow("Modified New Zealand Image", modifiedNZImage);
    cv::waitKey(0);

    //Save the Modified New Zealand Image
    cv::imwrite("images/mod_new_zealand.jpg", modifiedNZImage);

    return 0;
}

