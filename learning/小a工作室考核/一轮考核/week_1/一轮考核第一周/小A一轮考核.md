### ***小A一轮考核*** 

---

## 3/21

### 		需要学习：		

#### 				python：类，文件处理

#### 				线代：张量

#### 				概率论：

​			- 随机事件及其运算 

​			\- 概率的定义及性质 

​			\- 条件概率 [可选] 

​			- 随机变量- 常用连续分布、多维随机变量及其分布 

​			- 大数定律与中心极限定理 [可选] 

​			\- 统计量及其分布 [可选] 

### **任务：**

​		处理图片，用python将数据集自动分为7:3的训练集和测试集。将图片转为数据，再计算均值和方差。

---

## 3/22

#### 	python os库：处理系统的文件

```python
		#os.walk: 遍历文件夹中的文件
    	import os
​		for root, dirs, files in os.walk(operate_path):#root:该文件路径 dirs:该文件中子文件夹名 files：该文件夹中的文件
​		os.path.join() # 连接多个文件路径，返回连接后的文件路径
​		os.listdir(path) # 返回该路径下的文件名的列表
​		filter(function,iterable) # 筛选列表中符合条件的数据  function:筛选条件 iterable:需要筛选的列表
​		os.makedirs(path) # 创建一个文件夹
```



#### 	参考：[(35条消息) 图片数据集划分为训练集、测试集、验证集_时晏未央的博客-CSDN博客](https://blog.csdn.net/weixin_46034116/article/details/119617009)

#### [(35条消息) Python - 将图片转化成numpy数组_Python全栈圈的博客-CSDN博客_图片转numpy](https://blog.csdn.net/weixin_39129504/article/details/86486380?ops_request_misc=&request_id=&biz_id=102&utm_term=python将图片转数据&utm_medium=distribute.pc_search_result.none-task-blog-2~blog~sobaiduweb~default-1-86486380.nonecase&spm=1018.2226.3001.4450)

---

#### 读取图片并计算均值方差

​		cv2方法：

```python
	cv2.imread("path")     # BGR格式   np.array()类型
​	cv2.imshow()   #显示图片
```

​		Image方法:

```python
	img = Image.open("path")  #RGB格式
​	img = np.array(img) # 转化成numpy数组*
​	plt.imshow(img)
​	plt.show() # 显示图片

​	np.mean(img) # 均值
​	np.std(img)	# 方差
```

---

## 3/23

#### 		git 操作：

#### 			上传新文件：

​				1.`git init` #初始化库

​				2.`git pull origin master` # 将远程仓库里面的项目拉下来

​				3.`git add` . # 添加

​					 `git rm -r --cached file` # 删除file文件夹

​				4.`git commit -m ` # 提交缓存区

​				5.`git remote add origin git@.... ` # 建立远程库和本地库连接

​				6.`git push -u origin master `  # 推送

​			`git remote rm origin`

​			 `Switched to branch 'master' ` #切换分支

#### 		一些问题：

​			上传文件后文件无法打开出现白色箭头：

​			1.删除上传文件夹里的.git文件

​			2.执行git rm --cached 文件名

​			3.执行git add .

​			4.执行git commit -m“注释”

​			5.执行git push origin 分支名

#### **面向对象**：

​	封装：隐藏实现的细节，只留下一个借口给用户使用。

​	继承：在一个类的基础上建立新的类。

​	多态：父类经过子类重写，会出现多个版本。

**类(class)：**将数据和对数据的操作封装。

​	抽象类：不能够创建对象的类，包含抽象方法。

​	init:类的初始化，在创建类的实例时调用

​	私有属性：`self.__private_attrs`，在命名前加__，表示无法从外部访问

​	私有方法：`def __private_method`，在命名前加__，表示无法从外部访问，只能从内部调用

​	`super().__init__`:继承父类的方法，这里表示继承父类初始化

---

## 3/25

### 特征工程：从原始数据中获得更多信息，获得更好的训练数据，使机器学习算法达到最佳性能。

#### 	**1   特征选择**

​	从特征集合中挑选一组最具统计意义的特征集合，达到降维效果。

​	常用方法：

​		filter（刷选器）：计算时间上更高效，但不考虑特征间的相关性。

​		wrapper（封装器）：考虑到特征间的相关性，但在特征数量少时容易过拟合，特征数量多时计算时间	   		更长。

​		Embeded（集成方法）：让学习器自主选择学习特征。

​		特征选择过程包括产生过程，评价函数，停止准则，验证过程。

​					<img src="https://2022sterben.oss-cn-beijing.aliyuncs.com/img/image-20220329150643558.png" alt="image-20220329150643558" style="zoom: 67%;" />		

​		

#### 	2   **特征提取**

​	将原始数据重新组合特征得到新的特征，达到降维效果。

​	方法：主成分分析（PCA），独立成分分析（ICA），线性判别分析（LDA）可用属于无监督模型实现。

#### 	3  特征构建

​	从原始数据中人工的构建新的特征，将原始数据分出多个特征。

参考：

[(34条消息) 机器学习之特征工程_拾毅者的博客-CSDN博客_特征工程](https://blog.csdn.net/Dream_angel_Z/article/details/49388733?ops_request_misc=%7B%22request%5Fid%22%3A%22164853665416780264091059%22%2C%22scm%22%3A%2220140713.130102334..%22%7D&request_id=164853665416780264091059&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-5-49388733.142^v5^pc_search_insert_es_download,143^v6^register&utm_term=特征工程&spm=1018.2226.3001.4187)

---

### Sklearn库

​	包含六大任务模块：分类、回归、聚类、降维、模型选择和预处理。

---

## 3/26

### K-means聚类算法

​		用于数据的处理，属于无监督学习。将数据集样本划分为若干个不相交的子集，每个子集对应某些特征。K代表取k个样本作为簇中心。means代表取每个聚类中数据的均值作为该簇的中心或称质心，用该质心对该簇进行描述。

实现算法主要四点：1 簇个数的选择   2 计算各样本到簇中心的距离  3 更新簇中心  4 重复2,3直到簇中心不移动

####  实现步骤

一.K值选择

​	由用户决定或者直接给定。

二.距离度量

​	欧式距离、曼哈顿距离、余弦相似度。

三.新质点计算

​	对分类后的k个簇，重新计算各簇内的质点。

四.停止K-means

​	当簇的质心不再改变，或者到达限定次数。如果没结束则重复2,3步骤。

---

## 3/27

### 信息熵

​	通过事件所有发生概率计算事件所含信息量的期望。

​	<img src="C:\Users\33903\AppData\Roaming\Typora\typora-user-images\image-20220329201153466.png" alt="image-20220329201153466" style="zoom:80%;" />

#### 	三个性质：

1. 单调性，发生概率越高，携带的信息量越小。
2. 非负性。
3. 累加性，多个随机事件同时发生的不确定性量度可以用各事件的不确定性量度的和表示。

### 条件熵

​	y在x的条件下的信息熵。对于y消除了对x的不确定性。

​	![image-20220329202441507](https://2022sterben.oss-cn-beijing.aliyuncs.com/img/image-20220329202441507.png)

### 互信息

​	表示两个随机事件的相关性

​	![image-20220329203147221](https://2022sterben.oss-cn-beijing.aliyuncs.com/img/image-20220329203147221.png)

​	表示事件X在减去知道Y事件后仍然不知道的事。

### 相对熵

​	衡量两个随机变量的差距。

<img src="https://2022sterben.oss-cn-beijing.aliyuncs.com/img/image-20220329210111246.png" alt="image-20220329210111246" style="zoom:80%;" />



---

### 决策树

​	用于分类问题。对数据的某一特征进行测试，根据检测结果分配到子节点，不断进行递归检测，直到叶节点，最后归类到叶节点的类中。基本思想以信息熵为度量构造一颗熵值下降最快的树。

​	主要步骤：特征选择、决策树生成、决策树修剪。

#### 	1.决策树的构造

​	信息增益：划分数据前后信息的变化。用互信息表示。

​		例如：特征A对训练数据集D的信息增益g(D,A)，定义为集合D的经验熵H(D)与特征A给定条件下D的经验条件熵H(D|A)之差，即：

​		![image-20220329212431211](https://2022sterben.oss-cn-beijing.aliyuncs.com/img/image-20220329212431211.png)

​	信息增益比：信息增益与训练集D的信息熵之比。

​		![image-20220329212647277](https://2022sterben.oss-cn-beijing.aliyuncs.com/img/image-20220329212647277.png)

#### 	2.决策树的生成和修剪

​		....
