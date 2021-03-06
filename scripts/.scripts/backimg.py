import requests
import os
import io
from datetime import date,timedelta
from PIL import Image

retry = 150
savePath = os.path.expanduser('~') + '/Pictures/Wallpapers/daily.png'
bingUrl = 'https://cn.bing.com'
bingPicUrl = bingUrl + '/HPImageArchive.aspx?format=js&idx=0&n=1&mkt=zh-CN'

def getImg(url):
    try:
        r = requests.get(url)
        result = r.json()
        picUrl = bingUrl + result['images'][0]['url']
        print(picUrl)
        img = requests.get(picUrl).content
        return img
    except Exception as e:
        print("fail to get.", e)
        return False

def saveFile(path, img):
    if os.path.exists(path):
        yesterday = date.today() - timedelta(days=1)
        os.rename(path, os.path.join(os.path.dirname(path), yesterday.strftime("%Y%m%d")+".png"))

    try:
        tmpIm = Image.open(io.BytesIO(img))
        tmpIm.save(path, "png", optimize=True)
    except Exception as e:
        print(e)



# download and save
os.system('feh --bg-scale ' + savePath)

img = False
num = 0
#for num in range(0, retry):
while True:
    print("try to get img. retry count:", num+1)
    num = num + 1
    img = getImg(bingPicUrl)
    if False != img :
        break

saveFile(savePath, img)

os.system('feh --bg-scale ' + savePath)
