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
    
    //The VideoCapture object will be automatically released when the program ends
    return 0;
}