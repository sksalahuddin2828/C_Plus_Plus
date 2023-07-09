#include <opencv2/opencv.hpp>

void emptyFunction(int, void*)
{
    int threshold1 = cv2.getTrackbarPos("Threshold1", "Parameters");
    int threshold2 = cv2.getTrackbarPos("Threshold2", "Parameters");
    int area = cv2.getTrackbarPos("Area", "Parameters");
    std::cout << "Threshold1: " << threshold1 << std::endl;
    std::cout << "Threshold2: " << threshold2 << std::endl;
    std::cout << "Area: " << area << std::endl;
}

int main()
{
    int frameWidth = 640;
    int frameHeight = 480;

    cv::VideoCapture cap(0);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, frameWidth);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, frameHeight);

    cv::namedWindow("HSV");
    cv::resizeWindow("HSV", 640, 240);

    cv::createTrackbar("HUE Min", "HSV", 0, 179, emptyFunction);
    cv::createTrackbar("HUE Max", "HSV", 179, 179, emptyFunction);
    cv::createTrackbar("SAT Min", "HSV", 0, 255, emptyFunction);
    cv::createTrackbar("SAT Max", "HSV", 255, 255, emptyFunction);
    cv::createTrackbar("VALUE Min", "HSV", 0, 255, emptyFunction);
    cv::createTrackbar("VALUE Max", "HSV", 255, 255, emptyFunction);

    cv::Mat frame, imgHsv, mask, result, hStack;

    while (true)
    {
        cap.read(frame);

        if (frame.empty())
        {
            std::cout << "Failed to capture frame from the camera." << std::endl;
            break;
        }

        cv::cvtColor(frame, imgHsv, cv::COLOR_BGR2HSV);

        int hMin = cv::getTrackbarPos("HUE Min", "HSV");
        int hMax = cv::getTrackbarPos("HUE Max", "HSV");
        int sMin = cv::getTrackbarPos("SAT Min", "HSV");
        int sMax = cv::getTrackbarPos("SAT Max", "HSV");
        int vMin = cv::getTrackbarPos("VALUE Min", "HSV");
        int vMax = cv::getTrackbarPos("VALUE Max", "HSV");

        cv::Scalar lower(hMin, sMin, vMin);
        cv::Scalar upper(hMax, sMax, vMax);

        cv::inRange(imgHsv, lower, upper, mask);
        cv::bitwise_and(frame, frame, result, mask);

        cv::cvtColor(mask, mask, cv::COLOR_GRAY2BGR);

        cv::hconcat(std::vector<cv::Mat>{frame, mask, result}, hStack);

        cv::imshow("Horizontal Stacking", hStack);

        if (cv::waitKey(1) == 'q')
            break;
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}
