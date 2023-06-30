#include <opencv2/opencv.hpp>

int main()
{
    std::string filename = "video.avi"; // Change the filename and format here (e.g., "video.mp4")
    double framesPerSecond = 24.0;
    std::string res = "720p"; // Change the resolution here (options: "480p", "720p", "1080p", "4k")

    cv::VideoCapture cap(0);
    cv::VideoWriter writer;
    cv::Size frameSize;
    int fourcc = cv::VideoWriter::fourcc('X', 'V', 'I', 'D'); // Change the fourcc code as per desired video format
    
    if (!cap.isOpened())
    {
        std::cout << "Failed to open the camera!" << std::endl;
        return -1;
    }

    if (res == "480p")
        frameSize = cv::Size(640, 480);
    else if (res == "720p")
        frameSize = cv::Size(1280, 720);
    else if (res == "1080p")
        frameSize = cv::Size(1920, 1080);
    else if (res == "4k")
        frameSize = cv::Size(3840, 2160);
    else
        frameSize = cv::Size(640, 480); // Default resolution: 480p

    writer.open(filename, fourcc, framesPerSecond, frameSize, true);

    if (!writer.isOpened())
    {
        std::cout << "Failed to create video writer!" << std::endl;
        return -1;
    }

    while (true)
    {
        cv::Mat frame;
        cap.read(frame);

        writer.write(frame);
        cv::imshow("frame", frame);

        if (cv::waitKey(1) == 'q')
            break;
    }

    cap.release();
    writer.release();
    cv::destroyAllWindows();

    return 0;
}
