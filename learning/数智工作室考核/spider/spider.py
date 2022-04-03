from bs4 import BeautifulSoup  # 网页解析，获得数据
import re  # 正则表达式，进行文字匹配
import urllib.request, urllib.error  # 指定URL，获得网页数据
import xlwt  # 进行excel操作
import sqlite3  # 进行SQLite数据库操作


def main():
    #爬取网页的网址
    baseurl = "https://movie.douban.com/top250?start="
    # 爬取网页
    datalist = getDara(baseurl)
    savepath = "豆瓣电影Top250.xls"
    saveData(datalist,savepath)


findLink = re.compile(r'<a href="(.*?)">')  # 创建正则表达式对象，表示字符串格式
# 影片图片规则
findImgSrc = re.compile(r'<img.*src="(.*?)"', re.S)  # re.S 让换行符包含在提取的字符中，因为.不能识别换行符
# 影片中文片名
findTitle = re.compile(r'<span class="title">(.*)</span>')
# 影片评分
findRating = re.compile(r'<span class="rating_num" property="v:average">(.*?)</span>')
# 找到评价人数
findJudge = re.compile(r'<span>(\d*)人评价</span>')
# 找到概况
findInq = re.compile(r'<span class="inq">(.*)</span>')
# 影片相关信息
findBd = re.compile(r'<p class="">(.*?)</p>',re.S)

# 爬取网页
def getDara(baseurl):
    datalist = []
    # 获取网站url
    for i in range(0, 10):
        url = baseurl + str(i * 25)
        # 获取网站源代码
        html = askURL(url)
        # 解析数据 储存为树的结构
        soup = BeautifulSoup(html, "html.parser")
        for item in soup.find_all('div', class_="item"):  # 查找符合要求的字符串，形成列表
            # print(item)
            data = []
            item = str(item)
            #电影详情链接
            link = re.findall(findLink, item)[0]  # re通过正则表达式来查找指定字符串
            data.append(link)
            #海报链接
            imgSrc = re.findall(findImgSrc, item)[0]
            data.append(imgSrc)
            #电影名
            titles = re.findall(findTitle, item)
            if(len(titles) == 2):
                ctitle = titles[0]
                data.append(ctitle)
                otitle = titles[1].replace("/","")
                data.append(otitle)
            else:
                data.append(titles[0])
                data.append(' ')
            # 电影评分
            rating = re.findall(findRating, item)[0]
            data.append(rating)
            # 评分人数
            judgeNum = re.findall(findJudge,item)[0]
            data.append(judgeNum)
            # 电影概括
            Inq = re.findall(findInq, item)
            if(len(Inq) == 1):
                data.append(Inq)
            else:
                data.append(' ')
            datalist.append(data)
            # 影片相关信息
            bd = re.findall(findBd, item)[0]
            bd = re.sub('<br(\s+)?/>(\s)?',' ',bd) #去掉<br/>
            bd = re.sub('/',' ',bd) #替换/
            data.append(bd.strip())
            datalist.append(data)
    # print(datalist)
    return datalist


# 得到指定url网页的信息
def askURL(url):
    # 用户代理，表示我们是什么类型的机器，我们可以接受什么类型的文件
    head = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) "
                      "Chrome/99.0.4844.74 Safari/537.36 Edg/99.0.1150.55"}

    request = urllib.request.Request(url, headers=head)
    html = ""
    try:
        response = urllib.request.urlopen(request)  # 对网络源码进行utf-8的解码
        html = response.read().decode("utf-8")
        # print(html)
    except urllib.error.URLError as e:
        if hasattr(e, "code"):
            print(e.code)
        if hasattr(e, "reason"):
            print(e.reason)

    return html


# 保存数据
def saveData(datalist,savepath):
    book = xlwt.Workbook(encoding="uft-8")
    sheet = book.add_sheet("豆瓣电影Top250")
    col = ('电影详情链接',"图片链接","电影名","电影外国名","电影评分","评分人数","简介","影片相关信息")
    # 储存列名
    for i in range(0,8):
        sheet.write(0,i,col[i])
    # 储存数据
    for i in range(0,250+1):
        print("第%d条"%i)
        data = datalist[i]
        for j in range(0,8):
            sheet.write(i+1,j,data[j])

    book.save(savepath)


if __name__ == "__main__":
    main()
