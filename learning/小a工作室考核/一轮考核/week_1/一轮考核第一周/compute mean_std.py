#!/usr/bin/env python
# author = 'elder ring$'
# time = 2022/3/22
# Project = compute
import os
import numpy as np
from PIL import Image
from matplotlib import pyplot as plt

#图片集的文件夹路径
dataset_dir = "第一轮考核数据集/split_marvel_dataset/test/black widow"
files = os.listdir(dataset_dir)  # 获得文件夹内的所有文件名称

# 显示图像
# plt.imshow(img)
# plt.show()
# print(img.shape)

# 计算该文件夹下所有图片的均值和方差
for i in range(len(files)):
    dir = os.path.join(dataset_dir,files[i])
    img = Image.open(dir)
    img = np.array(img)
    print("img" + str(i) + "_mean = " + str(np.mean(img)))
    print("std" + str(i) + "_std = " + str(np.std(img)))