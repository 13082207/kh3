import cv2
import numpy as np

# 1. 读取图片
img = cv2.imread("/home/csq/code/scripts/MDWHC.JPG") 

# 2. 定义白色范围
lower_white = np.array([240, 240, 240])  # 白色下限
upper_white = np.array([255, 255, 255])  # 白色上限

# 3. 生成白色区域的掩码（mask）：白色区域为255，其他为0
mask = cv2.inRange(img, lower_white, upper_white)

# 4. 白色背景替换为黑色
img[mask != 0] = [0, 0, 0]  #[0,0,0]对应黑色

# 5. 保存/显示结果
cv2.imwrite("output_black_bg.JPG", img)
cv2.imshow("Black Background", img)
cv2.waitKey(0)
cv2.destroyAllWindows()
