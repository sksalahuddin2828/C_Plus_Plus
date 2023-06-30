#include <opencv2/opencv.hpp>

void make_1080p(cv::VideoCapture& cap)
{
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1920);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 1080);
}

void make_720p(cv::VideoCapture& cap)
{
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);
}

void make_480p(cv::VideoCapture& cap)
{
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
}

void change_res(cv::VideoCapture& cap, int width, int height)
{
    cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
}

cv::Mat rescale_frame(const cv::Mat& frame, double percent = 75)
{
    int width = static_cast<int>(frame.cols * percent / 100);
    int height = static_cast<int>(frame.rows * percent / 100);
    cv::Size dim(width, height);
    cv::Mat resized_frame;
    cv::resize(frame, resized_frame, dim, 0, 0, cv::INTER_AREA);
    return resized_frame;
}

int main()
{
    cv::VideoCapture cap(0);
    if (!cap.isOpened())
    {
        std::cout << "Failed to open the camera!" << std::endl;
        return -1;
    }

    make_720p(cap);

    while (true)
    {
        cv::Mat frame;
        cap.read(frame);

        frame = rescale_frame(frame, 30);

        cv::imshow("frame", frame);

        cv::Mat frame2 = rescale_frame(frame, 500);
        cv::imshow("frame2", frame2);

        if (cv::waitKey(20) == 'q')
            break;
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}
