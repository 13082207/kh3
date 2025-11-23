#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 1. 读取图像
    string imagePath = "/home/csq/code/scripts/MDWHC.JPG";
    Mat originalImage = imread(imagePath);
    
    if (originalImage.empty()) {
        cout << "错误：无法读取图像！" << endl;
        return -1;
    }
    
    // 2. 设置旋转角度（向左旋转45度）
    double angle = 45.0;
    
    // 3. 计算旋转参数
    int originalHeight = originalImage.rows;
    int originalWidth = originalImage.cols;
    
    Point2f center(originalWidth / 2.0f, originalHeight / 2.0f);
    Mat rotationMatrix = getRotationMatrix2D(center, angle, 1.0);
    
    // 4. 计算旋转后的图像尺寸
    double cosAngle = abs(rotationMatrix.at<double>(0, 0));
    double sinAngle = abs(rotationMatrix.at<double>(0, 1));
    
    int newWidth = int((originalHeight * sinAngle) + (originalWidth * cosAngle));
    int newHeight = int((originalHeight * cosAngle) + (originalWidth * sinAngle));
    
    // 5. 调整旋转矩阵
    rotationMatrix.at<double>(0, 2) += (newWidth - originalWidth) / 2.0;
    rotationMatrix.at<double>(1, 2) += (newHeight - originalHeight) / 2.0;
    
    // 6. 执行旋转
    Mat rotatedImage;
    Scalar whiteColor(255, 255, 255); 
    warpAffine(originalImage, rotatedImage, rotationMatrix, Size(newWidth, newHeight),
               INTER_CUBIC, BORDER_CONSTANT, whiteColor);
    
    // 7. 显示结果
    namedWindow("原始图像", WINDOW_NORMAL);
    namedWindow("旋转后图像", WINDOW_NORMAL);
    
    imshow("原始图像", originalImage);
    imshow("旋转后图像", rotatedImage);
    
    // 8. 保存结果
    imwrite("rotated_image.jpg", rotatedImage);
    cout << "旋转完成！图像已保存为 rotated_image.jpg" << endl;
    
    waitKey(0);
    destroyAllWindows();
    
    return 0;
}
