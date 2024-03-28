/**
 * Cesar Guerrero
 * 03/28/24
 * 
 * Edge Detection in Frames from Video Feed
*/

#include <iostream>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
//We need access to image processing methods
#include <opencv2/imgproc.hpp>

enum class previewMethod{
    PREVIEW, //No Filtering
    BLUR, //Blurring Filter
    FEATURES, //Corner Feature Detector
    CANNY //Canny Edge Detector
};

struct cornerFeatureDetails{
    int maxCorners; //Max corners the algorithm will return
    double qualityLevel; //Corner feature with highest quality level is multiplied by this value and used as a threshold for feature corner detection
    double minDistance; //How close two corner features can be
    int blockSize; //Size of the pixel neighborhood
};

int main(){

    cornerFeatureDetails cornerFeature{500, 0.2, 15, 9};

    //Grab our camera -- Default
    cv::VideoCapture camera(0);
    cv::Mat videoFrame;
    auto imageFilter = previewMethod::PREVIEW;

    //32 is the Space Bar -- Recall that waitKey(0) means wait FOREVER
    while(true){
        //Read in a frame
        camera.read(videoFrame);

        if(videoFrame.empty()){
            std::cerr << "Error: Video Feed is empty\n";
            break;
        }

        //Handle image processing
        cv::Mat result;
        cv::Mat frameGray;
        cv::Mat corners;
        switch(imageFilter){
            case previewMethod::PREVIEW:
                result = videoFrame;
                break;
            case previewMethod::BLUR:
                cv::blur(videoFrame, result, cv::Size(10, 10));
                break;
            case previewMethod::FEATURES:
                result = videoFrame;
                cv::cvtColor(videoFrame, frameGray, cv::COLOR_BGR2GRAY); //Make a copy of our video frame in grayscale
                //Computes Corner Features
                cv::goodFeaturesToTrack(frameGray, corners, cornerFeature.maxCorners, cornerFeature.qualityLevel, cornerFeature.minDistance, cv::Mat(), cornerFeature.blockSize);
                //The corners matrix will have the x and y coordinates of the corners
                if(!corners.empty()){
                    for(int i = 0; i < corners.rows; i++){
                        //cv::circle(matrixToDrawIn, center, radius, color, line thickness)
                        cv::circle(result, cv::Point(corners.at<float>(i, 0), corners.at<float>(i, 1)), 10, cv::Scalar(0, 0, 255), 1);
                    }
                }
                break;
            case previewMethod::CANNY:
                cv::Canny(videoFrame, result, 80, 150);
                //We don't want to overwrite the original frame -- We want to display the result
                videoFrame = result;
                break;
        }

        //Display the frame
        cv::imshow("Video Feed", result);

        //Give the user a chance to change the filters
        auto keyPress = cv::waitKey(1);
        //Spacebar
        if(keyPress == 32){
            break;
        }else if(keyPress == 'c'){
            std::cout << "Canny Edge Detection\n";
            imageFilter = previewMethod::CANNY;
        }else if(keyPress == 'b'){
            std::cout << "Blurring Filter\n";
            imageFilter = previewMethod::BLUR;
        }else if(keyPress == 'f'){
            std::cout << "Corner Feature Detection\n";
            imageFilter = previewMethod::FEATURES;
        }else if(keyPress == 'p'){
            std::cout << "Preview\n";
            imageFilter = previewMethod::PREVIEW;
        };
    }

    //We don't have to release anything. The destructor will take care of it
    return 0;
}