#include <opencv\highgui.h>
#include <opencv2/videoio.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <string>
#include <vector>

int main() {

	std::string test = "lava.mp4";

	cv::VideoCapture cap(test);

	cv::namedWindow("Average Color From Front Facing Camera", 1);
	cv::namedWindow("Feed", 1);

	cv::Mat saveImage;

	std::vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);

	for (;;) {
		cv::Mat frame;
		cv::Mat avgColor;
		cap >> frame;
		cap >> avgColor;
		if (!cap.read(frame)) {
			break;
		}
		cv::subtract(cv::Scalar::all(255), frame, frame);
		cv::Scalar c = cv::mean(avgColor);
		avgColor.setTo(c);
		cv::resize(avgColor, avgColor, cv::Size::Size_(2048, 2), 0, 0, cv::INTER_CUBIC);
		saveImage.push_back(avgColor);
		cv::imshow("Feed", frame);
		cv::imshow("Average Color From Front Facing Camera", avgColor);
		if (cv::waitKey(30) >= 0) break;
	}

	cv::transpose(saveImage, saveImage);

	cv::imwrite("lavaInvertedColorPalette.png", saveImage, compression_params);
	cap.release();
	cv::destroyAllWindows();

	return 0;
}