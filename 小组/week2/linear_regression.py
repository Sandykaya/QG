import pandas as pd
import numpy as np

# 读取数据集
data = pd.read_csv("boston_house_prices.csv", skiprows=2, header=None)

# 设置列名
data.columns = ["CRIM", "ZN", "INDUS", "CHAS", "NOX", "RM", "AGE", "DIS", "RAD", "TAX", "PTRATIO", "B", "LSTAT", "MEDV"]

# 分离特征和标签
X = data.drop(columns=["MEDV"])  # 特征
y = data["MEDV"]  # 标签

# 特征缩放（最小-最大缩放）
X = (X - np.min(X, axis=0)) / (np.max(X, axis=0) - np.min(X, axis=0))
# 添加偏置列
X = np.c_[np.ones(X.shape[0]), X]

# 数据集切分
def train_test_split_custom(X, y, test_size=0.2, random_state=None):
    """
    数据集切分函数
    :X: 特征
    :y: 标签
    :test_size: 测试集大小比例
    :random_state: 随机数种子
    :return: 切分后的训练集和测试集
    """
    if random_state:
        np.random.seed(random_state)

    num_samples = X.shape[0]
    test_indices = np.random.choice(num_samples, size=int(test_size * num_samples), replace=False)
    train_indices = np.delete(np.arange(num_samples), test_indices)

    X_train, X_test = X[train_indices], X[test_indices]
    y_train, y_test = y[train_indices], y[test_indices]

    return X_train, X_test, y_train, y_test


# 进行数据集切分
X_train, X_test, y_train, y_test = train_test_split_custom(X, y, test_size=0.2, random_state=42)


# 最小二乘法线性回归
def least_squares_regression(X, y):
    """
    最小二乘法线性回归
    :X: 特征
    :y: 标签
    :return: 参数
    """
    theta = np.linalg.inv(X.T @ X) @ X.T @ y
    return theta


# 梯度下降法线性回归
def gradient_descent(X, y, learning_rate=0.0001, num_iterations=100000):
    """
    梯度下降法线性回归
    :X: 特征
    :y: 标签
    :learning_rate: 学习率
    :num_iterations: 迭代次数
    :return: 参数
    """
    # 随机初始化参数
    theta = np.random.randn(X.shape[1])
    # 迭代更新参数
    for i in range(num_iterations):
        y_pred = X @ theta
        gradient = X.T @ (y_pred - y)
        theta -= learning_rate * gradient
    return theta


# 使用最小二乘法
theta_ls = least_squares_regression(X_train, y_train)
print("Least squares parameters：", theta_ls)

# 使用梯度下降法
theta_gd = gradient_descent(X_train, y_train)
print("Gradient descent parameters：", theta_gd)


# 使用最小二乘法预测
theta_ls = least_squares_regression(X_train, y_train)

# 在测试集上进行预测
y_pred_ls = np.dot(X_test, theta_ls)

# 计算最小二乘法的均方误差
mse_ls = np.mean((y_pred_ls - y_test) ** 2)
print("Mean square error of least squares：", mse_ls)

# 使用梯度下降法预测
theta_gd = gradient_descent(X_train, y_train)

# 在测试集上进行预测
y_pred_gd = np.dot(X_test, theta_gd)

# 计算梯度下降法的均方误差
mse_gd = np.mean((y_pred_gd - y_test) ** 2)
print("Mean square error of gradient descent：", mse_gd)

