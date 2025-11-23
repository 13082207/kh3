import cv2
import numpy as np
import math

def rotate_image_with_fill(img, angle):
    # 获取图像尺寸
    (h, w) = img.shape[:2]
    
    # 计算旋转中心
    center = (w // 2, h // 2)
    
    # 获取旋转矩阵
    M = cv2.getRotationMatrix2D(center, angle, 1.0)
    
    # 计算旋转后新图像的尺寸
    cos = np.abs(M[0, 0])
    sin = np.abs(M[0, 1])
    
    new_w = int((h * sin) + (w * cos))
    new_h = int((h * cos) + (w * sin))
    
    # 调整旋转矩阵，考虑新尺寸的平移
    M[0, 2] += (new_w - w) / 2
    M[1, 2] += (new_h - h) / 2
    
    return M, new_w, new_h

def get_background_color(img, sample_size=10):
    """
    通过采样图像四个角来检测背景颜色
    """
    h, w = img.shape[:2]
    
    # 采样四个角的区域
    corners = [
        img[0:sample_size, 0:sample_size],           # 左上
        img[0:sample_size, w-sample_size:w],         # 右上
        img[h-sample_size:h, 0:sample_size],         # 左下
        img[h-sample_size:h, w-sample_size:w]        # 右下
    ]
    
    # 计算平均颜色
    avg_color = np.zeros(3)
    for corner in corners:
        avg_color += np.mean(corner, axis=(0, 1))
    
    avg_color = avg_color / len(corners)
    
    return avg_color.astype(int)

def rotate_with_auto_fill(image_path, angle=45, output_path=None):
    # 读取图像
    img = cv2.imread(image_path)
    if img is None:
        print("无法读取图像")
        return
    
    # 获取背景颜色
    bg_color = get_background_color(img)
    print(f"检测到的背景颜色: {bg_color}")
    
    # 计算旋转参数
    M, new_w, new_h = rotate_image_with_fill(img, angle)
    
    # 执行旋转，使用检测到的背景颜色填充
    rotated = cv2.warpAffine(
        img, 
        M, 
        (new_w, new_h), 
        flags=cv2.INTER_CUBIC,
        borderMode=cv2.BORDER_CONSTANT, 
        borderValue=bg_color.tolist()
    )
    
    # 显示结果
    cv2.imshow('Original', img)
    cv2.imshow('Rotated', rotated)
    
    # 保存结果
    if output_path:
        cv2.imwrite(output_path, rotated)
    
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    
    return rotated

if __name__ == "__main__":
    image_path = "/home/csq/code/scripts/MDWHC.JPG" 
    output_path = "rotated_image.jpg"
    
    # 向左旋转45度（正角度表示逆时针旋转）
    rotated_img = rotate_with_auto_fill(
        image_path, 
        angle=45, 
        output_path=output_path
    )
