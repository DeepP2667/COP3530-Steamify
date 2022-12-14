import json
import csv
import requests
import numpy
import pandas
import io
import time

response = requests.get('http://api.steampowered.com/ISteamApps/GetAppList/v0002/?key=STEAMKEY&format=json', )
print (response.status_code)
jsonFile = response.json()
print ("done")
jsonFile = jsonFile["applist"]["apps"]

count = 0
total = 0
bucketCounter = 0
startTime = int(time.time())
bucketTimeLimit = 300

csv = open("games.csv", "w", encoding="utf-8")
for pair in jsonFile:
    if (bucketCounter >= 200):
        print ("Bucket Counter Hit 20")
        print ("Current Count Written: " + str(count))
        bucketCounter = 0
        duration = int(time.time()) - startTime
        print (duration)
        timeLeft = bucketTimeLimit - duration
        if (timeLeft < bucketTimeLimit and timeLeft > 0):
            print ("going to sleep for " + str(timeLeft))
            time.sleep(timeLeft)
            startTime = int(time.time())
            print (bucketCounter)
        
    total = total + 1
    appid = pair["appid"]
    name = pair["name"]
    print (appid, name)
    url2 = "http://store.steampowered.com/api/appdetails?appids=" + str(appid)
    print (url2)
    if (name == "" or name.count("Demo") != 0 or name.count("test") != 0
        or name.count("Beta") != 0 or name.count(",") != 0):
        print ("TRIGGERED Name")
        continue
        
    response2 = requests.get(url2)
    bucketCounter = bucketCounter + 1
    print (response2.status_code)
    if (response2.status_code == 429):
        time.sleep(300)
        continue
    try:
        jsonFile2 = response2.json()[str(appid)]
    
        if (jsonFile2['success'] == False or jsonFile2['data']['type'] != "game"):
            print ("Page fake")
            continue
    
        # Need....
        gameData = jsonFile2['data']
        #Title
        title = gameData['name']
        #Genre
        genre = "Unknown"
        try:
            genre = gameData['genres'][0]['description']
        except:
            print("Exception thrown in GENRE")
        #Single/Muliplayer
        single = False
        multi = False
        try:
            for category in gameData['categories']:
                if (category['description'] == "Single-player"):
                    single = True
                if (category['description'] == "Multi-player"):
                    multi = True
                    break
        except:
            print ("Exception thrown in CATEGORY")
            single = True
        #Release Date/Year
        if (gameData['release_date']['coming_soon'] == True):
            releaseDate = "Coming soon"
        else:
            releaseDate = gameData['release_date']['date']

        print (title, genre, single, multi, releaseDate)
        sep = ", "
        
        
        csv.write(title + sep + genre + sep + str(single) + sep + str(multi) + sep + releaseDate + "\n")
        count = count + 1
        
        print ("CURRENT COUNT: " + str(count))

    except:
        print ("NoneType object detected")

csv.close()
print(total)
