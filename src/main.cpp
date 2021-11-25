
#include <opencv2/opencv.hpp>

bool contourTouchesImageBorder(const std::vector<cv::Point>& contour, const cv::Size& imageSize)
{
	cv::Rect bb = cv::boundingRect(contour);

	bool retval = false;

	int xMin, xMax, yMin, yMax;

	xMin = 0;
	yMin = 0;
	xMax = imageSize.width - 1;
	yMax = imageSize.height - 1;

	// Use less/greater comparisons to potentially support contours outside of 
	// image coordinates, possible future workarounds with cv::copyMakeBorder where
	// contour coordinates may be shifted and just to be safe.
	// However note that bounding boxes of size 1 will have their start point
	// included (of course) but also their and with/height values set to 1 
	// but should not contain 2 pixels.
	// Which is why we have to -1 the "search grid"
	int bbxEnd = bb.x + bb.width - 1;
	int bbyEnd = bb.y + bb.height - 1;
	if (bb.x <= xMin ||
		bb.y <= yMin ||
		bbxEnd >= xMax ||
		bbyEnd >= yMax)
	{
		retval = true;
	}

	return retval;
}


void testContourBorderCheck()
{
	std::vector<std::string> filenames =
	{
		"0_single_pixel_top_left.png",
		"1_left_no_touch.png",
		"1_left_touch.png",
		"2_right_no_touch.png",
		"2_right_touch.png",
		"3_top_no_touch.png",
		"3_top_touch.png",
		"4_bot_no_touch.png",
		"4_bot_touch.png"
	};

	// Load example image
	//std::string path = "C:/Temp/!Testdata/ContourBorderDetection/test_1/";
	std::string path = "../Testdata/ContourBorderDetection/test_1/";

	for (int i = 0; i < filenames.size(); ++i)
	{
		//std::string filename = "circle3BorderDistance0.png";
		std::string filename = filenames.at(i);
		std::string fqn = path + filename;
		cv::Mat img = cv::imread(fqn, cv::IMREAD_GRAYSCALE);

		cv::Mat processedImage;
		img.copyTo(processedImage);

		// Create copy for contour extraction since cv::findContours alters the input image
		cv::Mat workingCopyForContourExtraction;
		processedImage.copyTo(workingCopyForContourExtraction);

		std::vector<std::vector<cv::Point>> contours;
		// Extract contours 
		cv::findContours(workingCopyForContourExtraction, contours, cv::RetrievalModes::RETR_EXTERNAL, cv::ContourApproximationModes::CHAIN_APPROX_SIMPLE);

		// Prepare image for contour drawing
		cv::Mat drawing;
		processedImage.copyTo(drawing);
		cv::cvtColor(drawing, drawing, cv::COLOR_GRAY2BGR);

		// Draw contours
		cv::drawContours(drawing, contours, -1, cv::Scalar(255, 255, 0), 1);

		//cv::imwrite(path + "processedImage.png", processedImage);
		//cv::imwrite(path + "workingCopyForContourExtraction.png", workingCopyForContourExtraction);
		//cv::imwrite(path + "drawing.png", drawing);

		const auto imageSize = img.size();
		bool liesOnBorder = contourTouchesImageBorder(contours.at(0), imageSize);
		// std::cout << "lies on border: " << std::to_string(liesOnBorder);
		std::cout << filename << " lies on border: "
			<< liesOnBorder;
		std::cout << std::endl;
		std::cout << std::endl;

		cv::imshow("processedImage", processedImage);
		cv::imshow("workingCopyForContourExtraction", workingCopyForContourExtraction);
		cv::imshow("drawing", drawing);
		cv::waitKey();

		//cv::Size imageSize = workingCopyForContourExtraction.size();
		for (auto c : contours)
		{
			if (contourTouchesImageBorder(c, imageSize))
			{
				// Do your thing...
				int asdf = 0;
			}
		}
		for (auto c : contours)
		{
			if (contourTouchesImageBorder(c, imageSize))
			{
				// Do your thing...
				int asdf = 0;
			}
		}
	}

}

int main(int argc, char** argv)
{
	testContourBorderCheck();
	return 0;
}
