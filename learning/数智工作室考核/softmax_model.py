#!/usr/bin/env python
# author = 'elder ring$'
# time = 2022/3/19
# Project = two_layers
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import numpy


def relu(Z):
    A = np.maximum(0, Z)

    assert (A.shape == Z.shape)

    cache = Z
    return A, cache


def softmax(Z):
    Z_shift = Z - np.max(Z, axis=0)
    A = np.exp(Z_shift) / np.sum(np.exp(Z_shift), axis=0)

    cache = Z_shift

    return A, cache


def initialize_parameters_deep(layer_dims):
    np.random.seed(4)
    parameters = {}
    L = len(layer_dims)

    for l in range(1, L):
        parameters['W' + str(l)] = np.random.randn(layer_dims[l],
                                                   layer_dims[l - 1]) * np.sqrt(2. / layer_dims[l - 1])
        parameters['b' + str(l)] = np.zeros((layer_dims[l], 1))

    return parameters


def linear_forward(A, W, b):
    Z = np.dot(W, A) + b

    assert (Z.shape == (W.shape[0], A.shape[1]))
    cache = (A, W, b)

    return Z, cache


def linear_activation_forward(A_prev, W, b, activation):
    if activation == "softmax":

        Z, linear_cache = linear_forward(A_prev, W, b)
        A, activation_cache = softmax(Z)

    elif activation == "relu":

        Z, linear_cache = linear_forward(A_prev, W, b)
        A, activation_cache = relu(Z)

    assert (A.shape == (W.shape[0], A_prev.shape[1]))
    cache = (linear_cache, activation_cache)

    return A, cache


def L_model_forward(X, parameters):
    caches = []
    A = X
    L = len(parameters) // 2

    for l in range(1, L):
        A_prev = A
        A, cache = linear_activation_forward(A_prev, parameters['W' + str(l)], parameters['b' + str(l)],
                                             activation="relu")
        caches.append(cache)

    AL, cache = linear_activation_forward(A, parameters['W' + str(L)], parameters['b' + str(L)], activation="softmax")
    caches.append(cache)

    assert (AL.shape == (parameters['W' + str(L)].shape[0], X.shape[1]))

    return AL, caches


def compute_cost(AL, Y):
    m = Y.shape[1]
    cost = -(np.sum(Y * np.log(AL))) / float(m)
    # cost = np.squeeze(cost)
    assert (cost.shape == ())

    return cost


def compute_cost_with_regularization(AL, Y, parameters, lambd=0.7):
    m = Y.shape[1]
    L = len(parameters) // 2
    L2_regularization_cos = 0
    for l in range(1, L + 1):
        L2_regularization_cos += np.sum(np.square(parameters["W" + str(l)]))
    cost = compute_cost(AL, Y)
    cost_with_regularization = cost + (1. / m * lambd / 2) * L2_regularization_cos

    return cost_with_regularization


def linear_backward(dZ, cache):
    A_prev, W, b = cache
    m = A_prev.shape[1]

    dW = np.dot(dZ, A_prev.T) / float(m)
    db = np.sum(dZ, axis=1, keepdims=True) / float(m)
    dA_prev = np.dot(W.T, dZ)

    assert (dA_prev.shape == A_prev.shape)
    assert (dW.shape == W.shape)
    assert (db.shape == b.shape)

    return dA_prev, dW, db


def relu_backward(dA, cache):
    Z = cache
    dZ = np.array(dA, copy=True)

    dZ[Z <= 0] = 0

    assert (dZ.shape == Z.shape)

    return dZ


def softmax_backward(Y, cache):
    Z = cache

    s = np.exp(Z) / np.sum(np.exp(Z), axis=0)
    dZ = s - Y

    assert (dZ.shape == Z.shape)

    return dZ


def linear_activation_backward(dA, cache, activation):
    linear_cache, activation_cache = cache

    if activation == "relu":
        dZ = relu_backward(dA, activation_cache)
        dA_prev, dW, db = linear_backward(dZ, linear_cache)

    elif activation == "softmax":
        dZ = softmax_backward(dA, activation_cache)
        dA_prev, dW, db = linear_backward(dZ, linear_cache)

    return dA_prev, dW, db


def L_model_backward(Y, caches):
    grads = {}
    L = len(caches)

    current_cache = caches[L - 1]
    grads["dA" + str(L)], grads["dW" + str(L)], grads["db" + str(L)] = linear_activation_backward(Y, current_cache,
                                                                                                  activation="softmax")
    for l in reversed(range(L - 1)):
        current_cache = caches[l]
        dA_prev_temp, dW_temp, db_temp = linear_activation_backward(grads["dA" + str(l + 2)], current_cache,
                                                                    activation="relu")
        grads["dA" + str(l + 1)] = dA_prev_temp
        grads["dW" + str(l + 1)] = dW_temp
        grads["db" + str(l + 1)] = db_temp

    return grads


def initialize_adam(parameters):
    L = len(parameters) // 2
    v = {}
    s = {}

    for l in range(L):
        v["dW" + str(l + 1)] = np.zeros(parameters["W" + str(l + 1)].shape)
        v["db" + str(l + 1)] = np.zeros(parameters["b" + str(l + 1)].shape)
        s["dW" + str(l + 1)] = np.zeros(parameters["W" + str(l + 1)].shape)
        s["db" + str(l + 1)] = np.zeros(parameters["b" + str(l + 1)].shape)

    return v, s


def update_parameters_with_adam_and_regularization(parameters, m, grads, v, s, lambd, t=2, learning_rate=0.01,
                                                   beta1=0.9, beta2=0.999, epsilon=1e-8):
    L = len(parameters) // 2
    v_corrected = {}
    s_corrected = {}

    for l in range(L):
        v["dW" + str(l + 1)] = beta1 * v["dW" + str(l + 1)] + (1 - beta1) * grads['dW' + str(l + 1)]
        v["db" + str(l + 1)] = beta1 * v["db" + str(l + 1)] + (1 - beta1) * grads['db' + str(l + 1)]

        v_corrected["dW" + str(l + 1)] = v["dW" + str(l + 1)] / (1 - (beta1) ** t)
        v_corrected["db" + str(l + 1)] = v["db" + str(l + 1)] / (1 - (beta1) ** t)

        s["dW" + str(l + 1)] = beta2 * s["dW" + str(l + 1)] + (1 - beta2) * (grads['dW' + str(l + 1)] ** 2)
        s["db" + str(l + 1)] = beta2 * s["db" + str(l + 1)] + (1 - beta2) * (grads['db' + str(l + 1)] ** 2)

        s_corrected["dW" + str(l + 1)] = s["dW" + str(l + 1)] / (1 - (beta2) ** t)
        s_corrected["db" + str(l + 1)] = s["db" + str(l + 1)] / (1 - (beta2) ** t)

        parameters["W" + str(l + 1)] = parameters["W" + str(l + 1)] * (1 - learning_rate * lambd / m) - learning_rate * (
                v_corrected["dW" + str(l + 1)] / np.sqrt(s_corrected["dW" + str(l + 1)] + epsilon))
        parameters["b" + str(l + 1)] = parameters["b" + str(l + 1)] - learning_rate * (
                v_corrected["db" + str(l + 1)] / np.sqrt(s_corrected["db" + str(l + 1)] + epsilon))
    return parameters, v, s


def update_parameters(parameters, grads, learning_rate):
    L = len(parameters) // 2  # 层数

    for l in range(1, L + 1):
        parameters['W' + str(l)] -= learning_rate * grads['dW' + str(l)]
        parameters['b' + str(l)] -= learning_rate * grads['db' + str(l)]

    return parameters


def l_layer_model(X, Y, layers_dims, learning_rate=0.1, lambd=0.7, num_iterations=3000, print_cost=False):
    np.random.seed(1)
    grads = {}
    costs = []  # 储存cost函数
    m = X.shape[1]  # 样本数

    # 初始化参数
    parameters = initialize_parameters_deep(layers_dims)
    v, s = initialize_adam(parameters)
    for i in range(0, num_iterations + 1):
        # 前向传播

        AL, caches = L_model_forward(X, parameters)
        # 计算损失函数
        # cost = compute_cost(AL, Y)
        cost = compute_cost_with_regularization(AL, Y, parameters, lambd)

        # 反向传播
        grads = L_model_backward(Y, caches)

        # 更新参数
        # parameters = update_parameters(parameters, grads, learning_rate)
        parameters, v, s = update_parameters_with_adam_and_regularization(parameters, m, grads, v, s, lambd)

        # 每迭代100次输出一次cost
        if print_cost and i % 100 == 0:
            print("Cost after iteration {}: {}".format(i, np.squeeze(cost)))
        if print_cost and i % 100 == 0:
            costs.append(cost)

    # 损失函数图像

    plt.plot(np.squeeze(costs))
    plt.ylabel('cost')
    plt.xlabel('iterations (per tens)')
    plt.title("Learning rate =" + str(learning_rate))
    plt.show()

    return parameters


# 将y转为独热编码
def convert_to_onehot(Y, C):
    Y = np.eye(C)[Y.reshape(-1)].T
    return Y


# 预测训练集
def predict_labels(X, y, parameters, set='training'):
    m = X.shape[1]
    W1 = parameters["W1"]
    b1 = parameters["b1"]
    W2 = parameters["W2"]
    b2 = parameters["b2"]

    # 前向传导
    probs, caches = L_model_forward(X, parameters)

    # 独热编码转数字
    y = np.argmax(y, axis=0)
    predict_label = np.argmax(probs, axis=0)
    if set == 'training':
        print("Training_Accuracy: " + str(np.sum((predict_label == y) / float(m))))
    elif set == 'validation':
        print("Validation_Accuracy: " + str(np.sum((predict_label == y) / float(m))))
    return predict_label


# 预测测试集
def predict(X, parameters):
    m = X.shape[1]

    W1 = parameters["W1"]
    b1 = parameters["b1"]
    W2 = parameters["W2"]
    b2 = parameters["b2"]

    # 前向传导
    probs, caches = L_model_forward(X, parameters)

    # 独热编码转数字
    predict_label = np.argmax(probs, axis=0)

    # 储存结果为csv模式
    numpy.savetxt('predict_label.csv', predict_label, fmt='%d', )

    return predict_label


# 划分数据为训练集和验证集以及预处理
def seperate_set(data, start, end):
    data_x = data.iloc[start:end, 1:-1].T  # m*n
    data_x = data_x / 255
    data_y = data.iloc[start:end, -1]
    data_m = data_y.shape[0]
    data_y = data_y.values.reshape([data_m, 1])
    data_y = convert_to_onehot(data_y, 10)
    return data_x, data_y, data_m


train_data = pd.read_csv('n_train.csv')
test_data = pd.read_csv('n_test.csv')

train_x, train_y, train_m = seperate_set(train_data, 0, 1000)
# train_set_x, train_set_y, train_set_m = seperate_set(train_data, 0, 300)
# test_set_x, test_set_y, test_set_m = seperate_set(train_data, 10000, 10300)

test_x = test_data.iloc[:, 1:].T

layers = (train_x.shape[0], 128, 10)
parameters = l_layer_model(train_x, train_y, layers_dims=layers, learning_rate=0.12, lambd=0.7,num_iterations=1000,
                           print_cost=True)

prediction = predict(test_x, parameters)
# predict_train_label = predict_labels(train_set_x, train_set_y, parameters, set='training')
# predict_test_label = predict_labels(test_set_x, test_set_y, parameters, set='validation')
