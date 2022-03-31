# %load function.py
#!/usr/bin/env python
# author = 'elder ring$'
# time = 2022/3/30
# Project = function
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split


class Network(object):
    def __init__(self, num_weights):
        # 随机初始化权重w
        np.random.seed(0)
        self.w = np.random.randn(1, num_weights)
        self.b = 0

    def linear_forward(self, x):
        z = np.dot(self.w, x.T) + self.b
        return z
    
    def Normalization(self, X):
        maximums, minimums, avgs = X.max(axis=0), X.min(axis=0), \
                                   X.sum(axis=0) / X.shape[0]
        # 对数据进行归一化处理
        for i in range(X.shape[1]):
            # print(maximums[i], minimums[i], avgs[i])
            X[:, i] = (X[:, i] - avgs[i]) / (maximums[i] - minimums[i])

        return X
    
    def cost(self, z, y):
#         num_samples = y.shape[1]
#         cost = (np.square(y-z)).sum()/ (2 * m)
        error = z - y
        num_samples = error.shape[1]
        cost = error * error
        cost = np.sum(cost) / num_samples / 2
        return cost

    def gradient(self, x, y, z):
        m = x.shape[0]
#         dw = 1. / m * np.dot(z-y, x)
        dw = 1. / m * np.sum((z-y).T * x, axis=0)
        db = 1. / m * np.sum(z-y)
        return dw, db

    def updata(self, dw, db, learning_rate=0.01):
        self.w = self.w - learning_rate * dw
        self.b = self.b - learning_rate * db

    def train(self, x, y, num_iterations=3000, learning_rate=0.01):
        m = x.shape[0]
        costs = []
        y = y.reshape(1,-1)
        for i in range(1, num_iterations + 1):
            np.random.shuffle(x)
            z = self.linear_forward(x)
            cost = self.cost(z, y)
            dw, db = self.gradient(x, y, z)
            self.updata(dw,db,learning_rate)
            # 每迭代100次输出一次cost
            if i % 100 == 0:
                print("Cost after iteration {}: {}".format(i, np.squeeze(cost)))
            if i % 100 == 0:
                costs.append(cost)

        # 损失函数图像
        plt.plot(np.squeeze(costs))
        plt.ylabel('cost')
        plt.xlabel('iterations (per tens)')
        plt.title("Learning rate =" + str(learning_rate))
        plt.show()
        return costs