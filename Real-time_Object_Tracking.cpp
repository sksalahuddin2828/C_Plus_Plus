#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Create a tracker object
    cv::Ptr<cv::Tracker> tracker = cv::TrackerKCF::create();

    // Open the video capture
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cout << "Failed to open video capture." << std::endl;
        return -1;
    }

    // Read the first frame from the video
    cv::Mat frame;
    if (!cap.read(frame)) {
        std::cout << "Failed to read video." << std::endl;
        return -1;
    }

    // Select the region of interest (ROI) for tracking
    cv::Rect2d bbox = cv::selectROI("Tracking", frame, false);

    // Initialize the tracker with the selected ROI
    tracker->init(frame, bbox);

    // Main loop for video processing
    while (true) {
        // Read a frame from the video
        if (!cap.read(frame)) {
            std::cout << "Failed to read video." << std::endl;
            break;
        }

        // Update the tracker with the current frame
        bool success = tracker->update(frame, bbox);

        // If tracking is successful, draw the bounding box
        if (success) {
            cv::rectangle(frame, bbox, cv::Scalar(0, 255, 255), 3);
            cv::putText(frame, "Tracking", cv::Point(bbox.x, bbox.y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.9, cv::Scalar(0, 255, 255), 2);
        } else {
            // If tracking is lost, display "Lost" message
            cv::putText(frame, "Lost", cv::Point(20, 40), cv::FONT_HERSHEY_SIMPLEX, 0.9, cv::Scalar(0, 0, 255), 2);
        }

        // Display the frame
        cv::imshow("Tracking", frame);

        // Exit the loop if 'q' is pressed
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    // Release the video capture and close windows
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
