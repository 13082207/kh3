#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat img = imread("/home/csq/code/scripts/MDWHC.JPG");
    if (img.empty()) {
        cout << "无法读取图片！" << endl;
        return -1;
    }

    // 2. 拆分BGR通道（OpenCV默认BGR顺序）
    vector<Mat> bgr_channels;
    split(img, bgr_channels);
    Mat R_channel = bgr_channels[2]; // 提取R通道
    Mat G_channel = bgr_channels[1]; // 提取G通道
    Mat B_channel = bgr_channels[0]; // 提取B通道

    // 3. 显示并保存单通道结果
    imshow("TASK4_R通道", R_channel);
    imshow("TASK4_G通道", G_channel);
    imshow("TASK4_B通道", B_channel);
    
    imwrite("task4_R_channel.png", R_channel);
    imwrite("task4_G_channel.png", G_channel);
    imwrite("task4_B_channel.png", B_channel);

    waitKey(0);
    destroyAllWindows();
    return 0;
}
