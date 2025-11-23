#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    auto img = cv::imread("../src/MDWHC.PNG");
    if (img.empty()) {
        std::cout << "错误：图片没有找到！" << std::endl;
        return -1;
    }

    cv::imshow("img", img);

    // 正确的cvtColor用法
    cv::Mat gray_img;
    cv::cvtColor(img, gray_img, cv::COLOR_BGR2GRAY);
    cv::imshow("gray_img", gray_img);  // 显示灰度图

    cv::waitKey(0);
    return 0;
}
