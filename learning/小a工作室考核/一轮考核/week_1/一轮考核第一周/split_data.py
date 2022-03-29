#!/usr/bin/env python
# author = 'elder ring$'
# time = 2022/3/22
# Project = split——data
import os
import random
import shutil


# 创建保存图像的文件夹
def makedir(new_dir):
    if os.path.exists(new_dir) is not True:
        os.makedirs(new_dir)


random.seed(1)

# 原图像数据集路径
dataset_dir = "C:/Users/33903/Desktop/小a工作室考核/第一轮考核数据集/第一轮考核数据集/marvel"

# 划分后的数据集路径 相对路径
split_dir = "第一轮考核数据集/split_marvel_dataset"
train_dir = os.path.join(split_dir, "train")
test_dir = os.path.join(split_dir, "test")

# 划分比例
train_pct = 0.7
test_pct = 0.3

# 划分
for root, dirs, files in os.walk(dataset_dir):
    for sub_dir in dirs:  # 遍历datase_dir内的文件夹
        imgs = os.listdir(os.path.join(root, sub_dir))  # 以列表形式储存目标文件夹的所有文件名
        imgs = list(filter(lambda x: x.endswith('.jpg'), imgs))  # 获取以jpg结尾的文件名
        random.shuffle(imgs)  # 打乱顺序
        img_count = len(imgs)
        train_point = int(img_count * train_pct)  # 分配给训练集的图片数量
        test_point = int(img_count * test_pct)  # 分配给测试集的图片数量

        for i in range(img_count):  # 遍历每一张图片
            if i < train_point:
                out_dir = os.path.join(train_dir, sub_dir)
            else:
                out_dir = os.path.join(test_dir, sub_dir)
            makedir(out_dir)
            target_path = os.path.join(out_dir, imgs[i])  # 保存路径
            src_path = os.path.join(dataset_dir, sub_dir, imgs[i])  # 原目标文件路径
            shutil.copy(src_path, target_path)  # 复制图片
