/**
 * Cesar Guerrero
 * 03/24/24
 * 
 * Accessing Video using OpenCV
 * 
*/

#include <opencv2/videoio.hpp> //Library for video capture
#include <opencv2/highgui.hpp> //Library for GUI
#include <iostream>

int main(){
    
    //This will default to the first camera
    cv::VideoCapture captureSource(0);

    //We are going to use a while loop to continuously display the video feed
    cv::Mat frame;
    //NOTE: 27 is the ASCII value for the ESC key
    while(cv::waitKey(1) != 27){
        //Read the video frame and send it to the Mat object
        captureSource.read(frame);
        if(frame.empty()){
            std::cerr << "Error: Video Feed is empty\n";
            break;
        }

        cv::imshow("Video Feed", frame);
        
    }

    //This is redudant - The destructure will automatically release the VideoCapture object
    captureSource.release();

    //Writing to a video file to disk
    cv::VideoCapture videoSource;
    videoSource.open("./race_car.mp4");
    if(videoSource.isOpened() == false){
        std::cerr << "Error: Video file not found\n";
        return 1;
    }

    //Writing to a video file
    cv::Size frameSize(videoSource.get(cv::CAP_PROP_FRAME_WIDTH), videoSource.get(cv::CAP_PROP_FRAME_HEIGHT)); //Get the frame size
    std::cout << "Number of Frames: " << videoSource.get(cv::CAP_PROP_FRAME_COUNT) << std::endl;
    //Create a videoWriter Object
    cv::VideoWriter aviWriter("race_care_out.avi", cv::VideoWriter::fourcc('M','J','P','G'), 10, frameSize);
    cv::VideoWriter mp4Writer("race_car_out.mp4", cv::VideoWriter::fourcc('m', 'p', '4', 'v'), 10, frameSize);

    cv::Mat videoFrame;
    while(videoSource.read(videoFrame)){
        //Now that we have our video frame, we can write it to the video file
        aviWriter.write(videoFrame);
        mp4Writer.write(videoFrame);
    }

    //Now we can release the video source and the video writer -- This is REDUNDANT
    videoSource.release();
    aviWriter.release();
    mp4Writer.release();

    return 0;
}