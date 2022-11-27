import json
import csv
import requests
import numpy
import pandas
import io

response = requests.get('http://api.steampowered.com/ISteamApps/GetAppList/v0002/?key=STEAMKEY&format=json', )
# response = requests.get('https://steamspy.com/api.php', {"request": "all"})
print (response.status_code)

# print (response.content)
jsonFile = response.json()

# print(jsonFile)
print ("done")
jsonFile = jsonFile["applist"]["apps"]
count = 0
total = 0
csv = open("games.csv", "w", encoding="utf-8")
for pair in jsonFile:
    if (count > 100):
        break
    total = total + 1
    appid = pair["appid"]
    name = pair["name"]
    print (appid, name)
    url2 = "http://store.steampowered.com/api/appdetails?appids=" + str(appid)
    print (url2)
    if (name == "" or name.count("Demo") != 0 or name.count("test") != 0
        or name.count("Beta") != 0 or name.count(",") != 0):
        print ("TRIGGERED")
        continue
        
    response2 = requests.get(url2)
    print (response2.status_code)
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
        print("Exceptoin thrown in GENRE")
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


csv.close()
print(total)
# jsonFile = jsonFile["apps"]
# dataframe = pandas.DataFrame.from_dict(jsonFile, orient='index')
# print ("created data frame")
# app_list = dataframe[['appid', 'name']].sort_values('appid').reset_index(drop=True)
# print ("sorted")
# dataframe.to_csv('C:/Users/zombi/OneDrive/Documents/COP3530/Project 3/unsorted.csv', index=False)
# app_list.to_csv('C:/Users/zombi/OneDrive/Documents/COP3530/Project 3/sorted.csv', index=False)
# print ("converted to csv")

# display first few rows
# print (app_list.head())
