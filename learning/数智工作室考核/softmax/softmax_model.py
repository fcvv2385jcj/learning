import numpy as np
import pandas as pd
from softmax_function import Softmax

# 创建类的对象
model = Softmax()

# 导入数据
train_data = pd.read_csv('../n_train.csv')
test_data = pd.read_csv('../n_test.csv')

# 分割数据及预处理
train_x, train_y, train_m = model.seperate_set(train_data, 0, 2000)
train_set_x, train_set_y, train_set_m = model.seperate_set(train_data, 0, 2000)
test_set_x, test_set_y, test_set_m = model.seperate_set(train_data, 10000, 12000)

test_x = test_data.iloc[:, 1:].T #去掉首列的索引列并转置
# 层数
layers = (train_x.shape[0], 128, 10)
parameters = model.l_layer_model(train_x, train_y, layers_dims=layers, learning_rate=0.12, lambd=0.7,num_iterations=800, print_cost=True)
# prediction = predict(test_x, parameters) #预测测试集并储存为csv文件
predict_train_label = model.predict_labels(train_set_x, train_set_y, parameters, set='training') #预测训练集
predict_test_label = model.predict_labels(test_set_x, test_set_y, parameters, set='validation') # 预测验证集