## **Softmax多分类问题**

---

## **3/16**

​	将测试数据（csv格式）读入，使用`pd.read.csv(‘文件路径’)`

​	将读入的数据分为x,y，使用:

​		`train_y = train_data.lioc[:, -1]`

​		`train_x = train_data.lioc[:,1 :13]`

#### 缺失值问题:

​	用`print(train_data.isnull(.sum())`可查看每列缺失数，如果删除缺失值的那一整行，最终数据只剩下678行，相比原本799行损失了超过10%，最终是采用np中的fillna填充平均值。

参考：[(32条消息) 【Python】实现对csv格式的数据读取_想飞的蓝笨笨的博客-CSDN博客_python读取csv数据格式](https://blog.csdn.net/qq_44762986/article/details/106706677?ops_request_misc={"request_id"%3A"164751091016780265478432"%2C"scm"%3A"20140713.130102334.."}&request_id=164751091016780265478432&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-1-106706677.142^v2^es_vector_control_group,143^v4^control&utm_term=python读取csv格式&spm=1018.2226.3001.4187)

[(32条消息) 缺失值的处理方法_zrjdds的博客-CSDN博客_缺失值](https://blog.csdn.net/zrjdds/article/details/50223091?ops_request_misc=&request_id=&biz_id=102&utm_term=缺失值&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-1-50223091.142^v2^es_vector_control_group,143^v4^control&spm=1018.2226.3001.4187)

[(32条消息) Python-pandas的fillna()方法-填充空值_shangyj17的博客-CSDN博客_python中fillna](https://blog.csdn.net/qq_17753903/article/details/89892631)

[(32条消息) Python 数据清洗之缺失数据填充fillna（）_求知者_123的博客-CSDN博客_data.fillna](https://blog.csdn.net/qq_21840201/article/details/81008566?ops_request_misc={"request_id"%3A"164751316316780269884519"%2C"scm"%3A"20140713.130102334.."}&request_id=164751316316780269884519&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~baidu_landing_v2~default-3-81008566.142^v2^es_vector_control_group,143^v4^control&utm_term=fillna填充&spm=1018.2226.3001.4187)

---

####  独热编码

​		Sotfmax最终输出的结果y_hat是一个5 * m （**5对应0-4共5种结果的概率，m是样本数）**的矩阵，每个值的范围在[0,1]，但数据集中的y是一个m*1的矩阵。因此需要做一个转化。一开始用的是一个for循环后来才知道这叫独热编码(one hot)，可以用`np.eye()`实现。

参考：[(32条消息) python之独热编码的实现_大彤小忆的博客-CSDN博客_python 独热编码的实现](https://blog.csdn.net/HUAI_BI_TONG/article/details/108179403?ops_request_misc={"request_id"%3A"164751174216780264055885"%2C"scm"%3A"20140713.130102334.."}&request_id=164751174216780264055885&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~baidu_landing_v2~default-3-108179403.142^v2^es_vector_control_group,143^v4^control&utm_term=python实现独热编码&spm=1018.2226.3001.4187)

[吴恩达《深度学习》L2W3作业 - Heywhale.com](https://www.heywhale.com/mw/project/5dde48f6ca27f8002c4a8396)

[[双语字幕\]吴恩达深度学习deeplearning.ai_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1FT4y1E74V?p=78)

---

3/17

模型构建出来，w和b基本不更新，cost下降缓慢，最终测试集预测结果全为同一种分类，准确率3%。可能是数据集问题，或者模型代码写错。

参考：[反向传播之一：softmax函数 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/37740860)

---

***\*3/18\****

解决了数据异常的问题，处理异常值方法：箱型图分析，3δ原则。用3δ原则并删除异常数值。

​		但是还是同样的情况，学习率稍微加大，就会出现nan，cost下降也很慢。后来调试才知道，用的是relu函数，而数据中负数占了很大比例，因此这些数据没有被激活，也就导致了最后预测得到全是相同的结果，因为这些特征根本没被学习到。出现nan的原因是初始化参数时权重w太小，多次循环后梯度消失。

[(33条消息) Python对CSV文件的一些处理方法(读取数据与数据预处理)_ty_:-)的博客-CSDN博客_python处理csv数据](https://blog.csdn.net/Zhong_ty/article/details/115008820?ops_request_misc={"request_id"%3A"164756639916780274173945"%2C"scm"%3A"20140713.130102334.."}&request_id=164756639916780274173945&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~baidu_landing_v2~default-3-115008820.142^v2^es_vector_control_group,143^v4^control&utm_term=csv数据预处理&spm=1018.2226.3001.4187)

[(33条消息) 数据清洗- Pandas 清洗“脏”数据（一）_Zhang,Xuewen的博客-CSDN博客_数据清洗](https://blog.csdn.net/weixin_35702861/article/details/83094537?ops_request_misc={"request_id"%3A"164756647516782089314987"%2C"scm"%3A"20140713.130102334.."}&request_id=164756647516782089314987&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-2-83094537.142^v2^es_vector_control_group,143^v4^control&utm_term=数据清洗&spm=1018.2226.3001.4187)

[(33条消息) 数据清洗中异常值（离群值）的判别和处理方法_dhr223的博客-CSDN博客_数据离群值的处理方法](https://blog.csdn.net/dhr223/article/details/107086239?ops_request_misc={"request_id"%3A"164756690616781683916852"%2C"scm"%3A"20140713.130102334.."}&request_id=164756690616781683916852&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-107086239.142^v2^es_vector_control_group,143^v4^control&utm_term=异常值处理&spm=1018.2226.3001.4187)

[(33条消息) Pandas csv 文件，按条件删除行_wzg2016的博客-CSDN博客_csv pandas 删除行](https://blog.csdn.net/Strive_For_Future/article/details/107811231?ops_request_misc=&request_id=&biz_id=102&utm_term=csv删除指定行&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-3-107811231.142^v2^es_vector_control_group,143^v4^control&spm=1018.2226.3001.4187)

[(33条消息) 常用激活函数（Sigmiod、Tanh、Softmax、ReLU、elu、LReLU、Softplus）函数表达式、特点、图像绘制（代码）---已解决_喵喵love的博客-CSDN博客_softmax激活函数图像](https://blog.csdn.net/qq_41603193/article/details/112120889)

---

***\*3/19\****

​		新数据暂时没什么可以处理的，就是数据量比较大，看着像是28*28的图片。之前一直用的4层节点，参考了一些资料后，决定从最简单的2层开始构建softmax模型，用的还是relu，因为这次数据都是大于0。

​		尝试了不同数量的神经元，最后用的m,125,10层，验证集精确到97%，测试集92%，偏差偏高，下一步准备再加一些优化方法，例如adam。

​		使用adam后验证集达到99.9%，测试集提升到96%。下一步先搞清楚adam原理，之后再了解特征工程，k-means，决策树，看看还有哪些可以用的，还有模型的评估。

参考：[[双语字幕\]吴恩达深度学习deeplearning.ai_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1FT4y1E74V?p=78)

[吴恩达《深度学习》L2W2作业 - Heywhale.com](https://www.heywhale.com/mw/project/5dd79f80f41512002ceb3ca7)

 