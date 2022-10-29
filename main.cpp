#include <iostream>
#include <Windows.h>
#include "opencv2/opencv.hpp"

#define WIDTH 60
#define HEIGHT 45
#define TOTAL WIDTH * HEIGHT

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
            // If red (All values are same in grey scale) value is less than or equal to 150 (Dark Pixel)
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


    if (!capture.isOpened()) {
        std::cout << "Error opening file" << std::endl;
        return 1;
    }

    // Read Frames
    while (1) {
        cv::Mat frame;

        capture >> frame;

        if (frame.empty())
            break;

        render_frame(frame, Display);

        Sleep(1.0 / 30); // Breakpoint Here
    }

    capture.release();

	std::cin.get();
}