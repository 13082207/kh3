import cv2
import numpy as np

# 1. 读取图片 + 转为RGB格式（OpenCV默认BGR，先转RGB）
img = cv2.imread("/home/csq/code/scripts/MDWHC.JPG") 
rgb_img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

# 分离R、G、B通道并保存
r, g, b = cv2.split(rgb_img)

cv2.imshow("Single R Channel", r)
cv2.imshow("Single G Channel", g)
cv2.imshow("Single B Channel", b)

cv2.waitKey(0)
cv2.destroyAllWindows()
