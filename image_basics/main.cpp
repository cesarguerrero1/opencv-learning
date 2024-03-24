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

//Function Prototypes
void opencvBasics();
void imageManipulation();
void imageAnnotation();
void imageEnhancement();

int main(){

    //opencvBasics();
    //imageManipulation();
    //imageAnnotation();
    imageEnhancement();

    return 0;
}

void opencvBasics(){
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

    return;
}

void imageManipulation(){

    auto image = cv::imread("images/checkerboard_18x18.png", cv::IMREAD_GRAYSCALE);
    cv::imshow("Image Manipulation", image);
    cv::waitKey(0);
    
    std::cout << "Pixel at 0,0: " << (int)image.at<uchar>(0,0) << "\n";
    std::cout << "Pixel at 0,6: " << (int)image.at<uchar>(0,6) << "\n";

    //Modify pixels
    auto imageCopy = image.clone();
    imageCopy.at<uchar>(2,2) = 200;
    imageCopy.at<uchar>(2,3) = 200;
    imageCopy.at<uchar>(3,2) = 200;
    imageCopy.at<uchar>(3,3) = 200;
    std::cout << imageCopy << "\n";
    cv::imshow("Modified Image", imageCopy);
    cv::waitKey(0);

    //We can crop an image by doing the following:
    auto checkerboardColor = cv::imread("images/checkerboard_color.png", cv::IMREAD_COLOR);
    cv::imshow("Color Checkerboard", checkerboardColor);
    cv::waitKey(0);

    //(900,900) is the middle of that image
    cv::Range rowRange(700,1100);
    cv::Range colRange(700,1100);
    auto croppedCheckerboard = cv::Mat(checkerboardColor, rowRange, colRange);
    std::cout << "The size of the cropped image is: " << croppedCheckerboard.size << "\n";
    cv::imshow("Cropped Checkerboard", croppedCheckerboard);
    cv::waitKey(0);


    //Resizing Images
    cv::Mat resizedImage;
    //Notice that if we leave size as (0,0) we can specify the scaling factors in x and y
    cv::resize(croppedCheckerboard, resizedImage, cv::Size(), 2, 2);
    std::cout << "The new size of the image is: " << resizedImage.size << "\n";
    cv::imshow("Resized Checkerboard", resizedImage);
    cv::waitKey(0);

    //We can also maintain an aspect ratio
    cv::Mat resizedImage2;
    int width = 100;
    float aspectRatio = width / (float)croppedCheckerboard.size().width;
    int calculatedHeight = croppedCheckerboard.size().height * aspectRatio;
    cv::resize(croppedCheckerboard, resizedImage2, cv::Size(width, calculatedHeight)); 
    std::cout << "The new size of the image is: " << resizedImage2.size << "\n";
    cv::imshow("Resized Checkerboard 2", resizedImage2);
    cv::waitKey(0);


    //Flipping an image
    cv::Mat flippedImage;
    //0 is flipping vertically, 1 is flipping horizontally, -1 is flipping both
    cv::flip(checkerboardColor, flippedImage, -1);
    cv::imshow("Flipped Checkerboard", flippedImage);
    cv::waitKey(0);

    return;
};

void imageAnnotation(){
    //Read in the apollo image
    cv::Mat apolloImage = cv::imread("./images/Apollo_11_Launch.jpg", cv::IMREAD_COLOR);
    cv::imshow("Apollo Image", apolloImage);
    cv::waitKey(0);

    //Copying our image and adding a line
    cv::Mat apolloWithLine = apolloImage.clone();
    //Remember that openCV uses BGR -- cv::Scalar(blue, green, red, alpha)
    cv::line(apolloWithLine, cv::Point(200,100), cv::Point(400, 100), cv::Scalar(0,0,255,1), 5);
    cv::imshow("Apollo Image with Line", apolloWithLine);
    cv::waitKey(0);


    //Copying our image and adding a circle
    cv::Mat apolloWithCircle = apolloImage.clone();
    cv::circle(apolloWithCircle, cv::Point(900,500), 100, cv::Scalar(0,255,0,1), 5);
    cv::imshow("Apollo Image with Circle", apolloWithCircle);
    cv::waitKey(0);

    //Copying our image and adding a rectangle
    cv::Mat apolloWithRectangle = apolloImage.clone();
    cv::rectangle(apolloWithRectangle, cv::Point(500, 100), cv::Point(700,600), cv::Scalar(255,0,0,1), 5);
    cv::imshow("Apollo Image with Rectangle", apolloWithRectangle);
    cv::waitKey(0);

    //Copying our image and adding text
    cv::Mat apolloWithText = apolloImage.clone();
    cv::putText(apolloWithText, "Apollo 11 Launch", cv::Point(200, 700), cv::FONT_HERSHEY_TRIPLEX, 2.3, cv::Scalar(255,255,255,1), -1);
    cv::imshow("Apollo Image with Text", apolloWithText);
    cv::waitKey(0);

};

void imageEnhancement(){
    
    //Read in our image
    auto image = cv::imread("images/New_Zealand_Coast.jpg", cv::IMREAD_COLOR);
    cv::imshow("New Zealand Coast", image);
    cv::waitKey(0);

    //Matrix variables
    cv::Mat darkerImage;
    cv::Mat brighterImage;

    //Scalar
    auto intensity = cv::Scalar(50,50,50);
    //Brightness Changes
    cv::add(image, intensity, brighterImage);
    cv::subtract(image, intensity, darkerImage);
    cv::imshow("Brighter New Zealand Coast", brighterImage);
    cv::waitKey(0);
    cv::imshow("Darker New Zealand Coast", darkerImage);
    cv::waitKey(0);


    //Contrast Changes
    cv::Mat lowContrastImage;
    cv::Mat highContrastImage;
    cv::Mat contrastImage;

    //Change constrant
    cv::multiply(image, .8, lowContrastImage);
    cv::multiply(image, 1.2, highContrastImage);
    cv::convertScaleAbs(image, contrastImage, 2, 0);

    cv::imshow("Low Contrast New Zealand Coast", lowContrastImage);
    cv::waitKey(0);
    cv::imshow("High Contrast New Zealand Coast", highContrastImage);
    cv::waitKey(0);
    cv::imshow("Contrast New Zealand Coast", contrastImage);
    cv::waitKey(0);


    //Thresholding
    cv::Mat building = cv::imread("images/building-windows.jpg", cv::IMREAD_GRAYSCALE);
    cv::Mat thresholdImage;
    cv::threshold(building, thresholdImage, 125, 255, cv::THRESH_BINARY);
    cv::imshow("Thresholded Building", thresholdImage);
    cv::waitKey(0);

    //Thresholding Application - Parsing Sheetmusic
    cv::Mat sheetMusic = cv::imread("images/Piano_Sheet_Music.png", cv::IMREAD_GRAYSCALE);
    cv::Mat thresholdSheetMusic;
    cv::threshold(sheetMusic, thresholdSheetMusic, 65, 255, cv::THRESH_BINARY);
    cv::imshow("Thresholded Sheet Music", thresholdSheetMusic);
    cv::waitKey(0);

    //Adaptive Thresholding - Parsing Sheetmusic
    cv::Mat adaptiveThresholdSheetMusic;
    cv::adaptiveThreshold(sheetMusic, adaptiveThresholdSheetMusic, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 11, 7);
    cv::imshow("Adaptive Thresholded Sheet Music", adaptiveThresholdSheetMusic);
    cv::waitKey(0);


    //Bitwise Operations
    cv::Mat coke = cv::imread("images/coca-cola-logo.png", cv::IMREAD_COLOR);
    cv::Mat colorCheck = cv::imread("images/checkerboard_color.png", cv::IMREAD_COLOR);

    //Make sure the checkerboard is the same size as the coke image
    int width = coke.size().width;
    float aspectRatio = width / (float)(colorCheck.size().width);
    int calculatedHeight = colorCheck.size().height * aspectRatio;
    cv::resize(colorCheck, colorCheck, cv::Size(width, calculatedHeight));
    std::cout << "The size of the checkerboard is: " << colorCheck.size << "\n";

    //Coca Cola mask
    cv::Mat cokeGrey;
    cv::cvtColor(coke, cokeGrey, cv::COLOR_BGR2GRAY);
    cv::Mat cokeMaskRegular;
    cv::Mat cokeMaskInverse;
    cv::threshold(cokeGrey, cokeMaskRegular, 127, 255, cv::THRESH_BINARY);
    cv::threshold(cokeGrey, cokeMaskInverse, 127, 255, cv::THRESH_BINARY_INV);
    cv::imshow("Coca Cola Mask", cokeMaskRegular);
    cv::waitKey(0);
    cv::imshow("Coca Cola Inverse Mask", cokeMaskInverse);
    cv::waitKey(0);

    //Apply the mask
    cv::Mat imgBackground;
    cv::bitwise_and(colorCheck, colorCheck, imgBackground, cokeMaskRegular);
    cv::imshow("Coca Cola Mask Applied", imgBackground);
    cv::waitKey(0);

    cv::Mat imgForeground;
    cv::bitwise_and(coke, coke, imgForeground, cokeMaskInverse);
    cv::imshow("Coca Cola Inverse Mask Applied", imgForeground);
    cv::waitKey(0);

    //Finally combine the two images
    cv::Mat finalImage;
    cv::add(imgBackground, imgForeground, finalImage);
    cv::imshow("Final Image", finalImage);
    cv::waitKey(0);


    return;
};