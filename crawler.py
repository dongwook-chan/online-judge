import requests
from requests.packages.urllib3.exceptions import InsecureRequestWarning
from bs4 import BeautifulSoup
import sys
import os


url = "https://www.acmicpc.net/problem/10998"

'''
# try to use proxy
proxy_host = "proxy.crawlera.com"
proxy_port = "8010"
proxy_auth = ":"
proxies = {
       "https": f"https://{proxy_auth}@{proxy_host}:{proxy_port}/",
       "http": f"http://{proxy_auth}@{proxy_host}:{proxy_port}/"
}

requests.packages.urllib3.disable_warnings(InsecureRequestWarning)
req = requests.get(url, proxies=proxies, verify=False)
'''

req = requests.get(url)
soup = BeautifulSoup(req.text,"html.parser")
tags = soup.findAll('pre', attrs={'class': 'sampledata'})
print(tags)

for i in range(len(tags)):
    file_type = "out" if i % 2 else "in"
    file_number = str(i // 2)
    file_name = file_type + file_number
    #with open(sys.argv[1], file_name), 'w') as fp:
    with open(os.path.join("BOJ/10998", file_name), 'w') as fp:
        fp.write(tags[i].get_text())