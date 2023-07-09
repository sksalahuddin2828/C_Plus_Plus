#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Create a VideoCapture object
    cv::VideoCapture capture(0); // Adjust the camera index if needed

    if (!capture.isOpened()) {
        std::cout << "Failed to open video capture." << std::endl;
        return -1;
    }

    // Create a Mat object to store the frame
    cv::Mat frame;

    // Main loop for video capture
    while (true) {
        // Read a frame from the video capture
        if (capture.read(frame)) {
            // Print the shape of the frame (height, width, channels)
            std::cout << "Shape: " << frame.size() << std::endl;

            // Display the frame
            cv::imshow("Frame", frame);
        } else {
            std::cout << "Failed to read frame" << std::endl;
            break;
        }

        // Exit the loop if 'q' is pressed
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    // Release the video capture and close the window
    capture.release();
    cv::destroyAllWindows();

    return 0;
}
