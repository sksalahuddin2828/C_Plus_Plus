#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    int frameWidth = 640;
    int frameHeight = 480;

    VideoCapture cap(0);
    cap.set(CAP_PROP_FRAME_WIDTH, frameWidth);
    cap.set(CAP_PROP_FRAME_HEIGHT, frameHeight);

    Mat img;
    while (true) {
        cap.read(img);

        // Perform image processing operations
        imwrite("result.jpg", img);

        imshow("Result", img);

        if (waitKey(1) & 0xFF == 'q') {
            break;
        }
    }

    cap.release();
    destroyAllWindows();

    return 0;
}
