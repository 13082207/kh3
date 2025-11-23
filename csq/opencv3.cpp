#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 1. 读取图片
    Mat img = imread("/home/csq/code/scripts/MDWHC.JPG");
    if (img.empty()) {
        cout << "无法读取图片！" << endl;
        return -1;
    }

    // 2. 白色背景转黑色
    Mat result = img.clone();
    for (int y = 0; y < result.rows; y++) {
        for (int x = 0; x < result.cols; x++) {
            Vec3b& pixel = result.at<Vec3b>(y, x);
            // 判定接近白色的像素
            if (pixel[0] >= 240 && pixel[1] >= 240 && pixel[2] >= 240) {
                pixel = Vec3b(0, 0, 0); // 设为黑色
            }
        }
    }

    // 3. 显示并保存结果
    imshow("TASK3_白色转黑色", result);
    imwrite("task3_result.png", result); // 保存处理后的图片

    waitKey(0);
    destroyAllWindows();
    return 0;
}
