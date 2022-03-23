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

​		os.walk: 遍历文件夹中的文件		

```python
for root, dirs, files in os.walk(operate_path):  
    #root:该文件路径 dirs:该文件中子文件夹名 files：该文件夹中的文件
	
```

​		os.path.join():连接多个文件路径，返回连接后的文件

​		os.listdir(path):返回该路径下的文件名的列表

​		filter(function,iterable):筛选列表中符合条件的数据  function:筛选条件 iterable:需要筛选的列表

​		os.makedirs(path):创建一个文件夹

#### 	参考：[(35条消息) 图片数据集划分为训练集、测试集、验证集_时晏未央的博客-CSDN博客](https://blog.csdn.net/weixin_46034116/article/details/119617009)

#### [(35条消息) Python - 将图片转化成numpy数组_Python全栈圈的博客-CSDN博客_图片转numpy](https://blog.csdn.net/weixin_39129504/article/details/86486380?ops_request_misc=&request_id=&biz_id=102&utm_term=python将图片转数据&utm_medium=distribute.pc_search_result.none-task-blog-2~blog~sobaiduweb~default-1-86486380.nonecase&spm=1018.2226.3001.4450)

---

#### 读取图片并计算均值方差

​		cv2：

```python
	cv2.imread("path")     # BGR格式   np.array()类型

​	cv2.imshow()   #显示图片
```

​		Image:

```python
	img = Image.open("path")  --RGB格式

​	img = np.array(img)   # 转化成numpy数组*

​	plt.imshow(img)

​	plt.show() # 显示图片
```

​		mean：

​			np.mean(img)

​			np.std(img)

---

## 3/23

#### 		git 操作：

​			git init #初始化库

​			git add . #添加

​			git commit -m  提交缓存区

​			git push -u origin master

​			git remote add origin git@....

​			git remote rm origin

​	一些问题：

​		上传文件后文件无法打开出现白色箭头：

​			1.删除上传文件夹里的.git文件

​			2.执行git rm --cached 文件名

​			3.执行git add .

​			4.执行git commit -m“注释”

​			5.执行git push origin 分支名
