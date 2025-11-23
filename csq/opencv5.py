import cv2
import numpy as np

def advanced_overall_contour(image_path, output_path=None, dilate_size=5, iterations=2):
   
    # 读取图像
    image = cv2.imread("/home/csq/code/scripts/MDWHC.JPG")
    if image is None:
        print("无法读取图像")
        return
    
    # 转换为灰度图
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    
    # 使用高斯模糊减少噪声
    blurred = cv2.GaussianBlur(gray, (3, 3), 0)
    
    # 二值化处理
    _, binary = cv2.threshold(blurred, 0, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)
    
    # 形态学操作 - 先闭运算填充小孔洞，再膨胀连接元素
    kernel_close = np.ones((3, 3), np.uint8)
    closed = cv2.morphologyEx(binary, cv2.MORPH_CLOSE, kernel_close)
    
    # 膨胀操作连接相近元素
    kernel_dilate = np.ones((dilate_size, dilate_size), np.uint8)
    dilated = cv2.dilate(closed, kernel_dilate, iterations=iterations)
    
    # 查找最外层轮廓
    contours, hierarchy = cv2.findContours(
        dilated, 
        cv2.RETR_EXTERNAL,
        cv2.CHAIN_APPROX_SIMPLE
    )
    
    # 创建结果图像
    result = image.copy()
    
    # 绘制红色轮廓
    cv2.drawContours(result, contours, -1, (0, 0, 255), 3)
    
    # 显示处理过程
    cv2.imshow('Original', image)
    cv2.imshow('Overall Outer Contour', result)
    
    # 保存结果
    if output_path:
        cv2.imwrite(output_path, result)
    
    print(f"找到 {len(contours)} 个整体外轮廓")
    print(f"使用的参数: 膨胀核大小={dilate_size}, 迭代次数={iterations}")
    
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    
    return result, contours

# 使用示例
if __name__ == "__main__":
    image_path = "mdwhc.jpg"
    output_path = "advanced_overall_contour.jpg"
  
    result, contours = advanced_overall_contour(
        image_path, 
        output_path, 
        dilate_size=7,  # 增大这个值可以连接更远的元素
        iterations=3    # 增大这个值可以增强连接效果
    )
