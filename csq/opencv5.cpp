#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

/**
 * 提取整体外轮廓，忽略内部镂空和独立小元素
 * 
 * @param inputPath 输入图像路径
 * @param outputPath 输出图像路径（可选）
 * @param dilateSize 膨胀核大小，控制连接程度
 * @param iterations 膨胀迭代次数，控制连接强度
 * @return 处理后的图像和轮廓向量
 */
std::pair<Mat, std::vector<std::vector<Point>>> extractOverallContour(
    const string& inputPath, 
    const string& outputPath = "",
    int dilateSize = 5,
    int iterations = 2) {
    
    // 读取图像
    Mat image = imread(inputPath);
    if (image.empty()) {
        cerr << "无法读取图像: " << inputPath << endl;
        return {Mat(), {}};
    }
    
    // 转换为灰度图
    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    
    // 使用高斯模糊减少噪声
    Mat blurred;
    GaussianBlur(gray, blurred, Size(3, 3), 0);
    
    // 二值化处理
    Mat binary;
    threshold(blurred, binary, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
    
    // 形态学操作 - 先闭运算填充小孔洞，再膨胀连接元素
    Mat closed, dilated;
    Mat kernelClose = getStructuringElement(MORPH_RECT, Size(3, 3));
    morphologyEx(binary, closed, MORPH_CLOSE, kernelClose);
    
    // 膨胀操作连接相近元素
    Mat kernelDilate = getStructuringElement(MORPH_RECT, Size(dilateSize, dilateSize));
    dilate(closed, dilated, kernelDilate, Point(-1, -1), iterations);
    
    // 查找最外层轮廓
    std::vector<std::vector<Point>> contours;
    std::vector<Vec4i> hierarchy;
    findContours(dilated, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    
    // 创建结果图像
    Mat result = image.clone();
    
    // 绘制红色轮廓
    drawContours(result, contours, -1, Scalar(0, 0, 255), 3);
    
    // 显示处理过程
    namedWindow("Original", WINDOW_NORMAL);
    namedWindow("Binary", WINDOW_NORMAL);
    namedWindow("Dilated", WINDOW_NORMAL);
    namedWindow("Overall Outer Contour", WINDOW_NORMAL);
    
    imshow("Original", image);
    imshow("Binary", binary);
    imshow("Dilated", dilated);
    imshow("Overall Outer Contour", result);
    
    // 保存结果
    if (!outputPath.empty()) {
        imwrite(outputPath, result);
    }
    
    cout << "找到 " << contours.size() << " 个整体外轮廓" << endl;
    cout << "使用的参数: 膨胀核大小=" << dilateSize << ", 迭代次数=" << iterations << endl;
    
    waitKey(0);
    destroyAllWindows();
    
    return {result, contours};
}

std::pair<Mat, std::vector<std::vector<Point>>> extractOverallContourSimple(
    const string& inputPath, 
    const string& outputPath = "") {
    
    return extractOverallContour(inputPath, outputPath, 5, 2);
}

int main() {
    string imagePath = "/home/csq/code/scripts/MDWHC.JPG"; 
    string outputPath = "result_cpp.jpg"; 
    
    auto result = extractOverallContourSimple(imagePath, outputPath);
    
    return 0;
}
