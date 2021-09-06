import cv2

originalImage = cv2.imread("4kcolored.jpeg")
grayImage = cv2.cvtColor(originalImage, cv2.COLOR_BGR2GRAY)
cv2.imwrite("4kbw.jpeg", grayImage)