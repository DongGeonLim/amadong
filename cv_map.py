import cv2
import numpy as np
import math

background_img = np.zeros(shape=(500, 300, 3), dtype=np.uint8)
rangE = cv2.imread("cat3.jpg")
line_img = cv2.line(img=rangE, pt1=(400, 200), pt2=(800, 800), color=(100, 200, 200), thickness=2)
cv2.imshow('cat', rangE)
cv2.waitKey(0)

blue_color = (255, 0, 0)
green_color = (0, 255, 0)
red_color = (0, 0, 255)

