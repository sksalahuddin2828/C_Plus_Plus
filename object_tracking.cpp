#include <opencv2/opencv.hpp>

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
        std::cout << "Failed to read frame." << std::endl;
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
            std::cout << "Failed to read frame." << std::endl;
            break;
        }

        // Update the tracker with the current frame
        bool success = tracker->update(frame, bbox);

        // If tracking is successful, draw the bounding box
        if (success) {
            cv::rectangle(frame, bbox, cv::Scalar(255, 0, 255), 3);
            cv::putText(frame, "Tracking", cv::Point(bbox.x, bbox.y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 255, 0), 2);
        } else {
            cv::putText(frame, "Lost", cv::Point(100, 75), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 0, 255), 2);
        }

        // Calculate and display FPS
        double fps = cv::getTickFrequency() / (cv::getTickCount() - frame.size.p[0]);
        cv::Scalar myColor;
        if (fps > 60) {
            myColor = cv::Scalar(20, 230, 20);
        } else if (fps > 20) {
            myColor = cv::Scalar(230, 20, 20);
        } else {
            myColor = cv::Scalar(20, 20, 230);
        }
        cv::rectangle(frame, cv::Point(15, 15), cv::Point(200, 90), cv::Scalar(255, 0, 255), 2);
        cv::putText(frame, "fps:", cv::Point(20, 40), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 0, 255), 2);
        cv::putText(frame, std::to_string((int)fps), cv::Point(75, 40), cv::FONT_HERSHEY_SIMPLEX, 0.7, myColor, 2);

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
