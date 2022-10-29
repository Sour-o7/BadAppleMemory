#include <iostream>
#include <Windows.h>
#include "opencv2/opencv.hpp"

#define WIDTH 60
#define HEIGHT 45
#define TOTAL WIDTH * HEIGHT
#define FILE_COUNT 1000


void render_frame(cv::Mat& frame, char* memoryDisplay)
{

    // Shrink Image
    cv::Mat shrunk_image;
    cv::resize(frame, shrunk_image, cv::Size(WIDTH, HEIGHT));

    // Iterate over frame rows
    for (int i = 0; i < HEIGHT; i++)
    {
        // Iterate over frame columns
        for (int k = 0; k < WIDTH; k++)
        {
            // If black pixel
            if (shrunk_image.at<cv::Vec3b>(i, k)[0] <= 150)
            {
                // Update memory cell
                memoryDisplay[(i * WIDTH) + k] += 1;
            }
        }
    }
}

int main()
{
	char Display[TOTAL];


	for (int i = 0; i < TOTAL; i++)
	{
        Display[i] = '\0';
	}

    // Open mp4

    cv::VideoCapture capture("BadApple.mp4");


//    cv::VideoWriter video("Exported.mp4", cv::VideoWriter::fourcc('M', 'P', '4', 'V'), 30, cv::Size(frame_width, frame_height));

    if (!capture.isOpened()) {
        std::cout << "Error opening file" << std::endl;
        return 1;
    }

    int frame_number = 0;

    // Read Frames
    while (1) {
        cv::Mat frame;

        capture >> frame;

        if (frame.empty())
            break;

        render_frame(frame, Display);
//        std::cout << frame_number << std::endl;
        Sleep(1.0 / 30);
        frame_number++;
    }

    capture.release();

	std::cin.get();
}