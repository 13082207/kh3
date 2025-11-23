import cv2

# 2. 读取图片
img = cv2.imread("/home/csq/code/scripts/MDWHC.JPG")  # 注意：OpenCV默认读取为BGR格式

# 3. 转为灰度图（核心步骤）
gray_img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# 4. 保存结果（替换为输出路径）
cv2.imwrite("output_gray.JPG", gray_img)

# 可选：显示图片
cv2.imshow("Gray Image", gray_img)
cv2.waitKey(0)  # 按任意键关闭
cv2.destroyAllWindows()
