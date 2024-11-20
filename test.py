# import required modules
import firebase_admin
from firebase_admin import db, credentials

import time

import os
from dotenv import load_dotenv

# Load .env
load_dotenv()

# authenticate to firebase
cred = credentials.Certificate(os.getenv("PATH_TO_CRED"))
firebase_admin.initialize_app(cred, {"databaseURL": os.getenv("FIREBASE_DB_URL")})

# creating reference to root node
ref = db.reference("/")

# ----------

# Read distance from database
i = 0   # just in case out of control, change to True when it's stable
distance = db.reference("/Sensor/distance").get()
print("Distance: ", distance)

# Assume use case: show changes if the value changes
while (i < 120):
    newDistance = db.reference("/Sensor/distance").get()
    difDistance = round(newDistance - distance, 10)
    print(difDistance)
    distance = newDistance

    if (abs(difDistance) >= 3):
        db.reference("/Result/led").set(True)
        time.sleep(1)
    else:
        db.reference("/Result/led").set(False)
    time.sleep(0.55)
    i += 1