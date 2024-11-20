# import required modules
import firebase_admin
from firebase_admin import db, credentials

import os
from dotenv import load_dotenv

# Load .env
load_dotenv()

# authenticate to firebase
cred = credentials.Certificate(os.getenv("PATH_TO_CRED"))
firebase_admin.initialize_app(cred, {"databaseURL": os.getenv("FIREBASE_DB_URL")})

# creating reference to root node
ref = db.reference("/")

# retrieving data from root node
print(ref.get())

distance = db.reference("/Sensor/distance").get()
print(distance)

# import random number for demonstration set operation
import random
random_int = random.randint(1, 100)

# set operation
db.reference("/Seed").set(random_int)
print(ref.get())

# update operation (update existing value)
db.reference("/").update({"Programming Language": "Python"})
print(ref.get())

# update operation (add new key value)
db.reference("/").update({"Suggestions": ["Good", "OK"]})
print(ref.get())

# push operation
db.reference("/Suggestions").push().set("Not bad")
print(ref.get())

# If you use {"Suggestions": "Good"}, 
# it can be overwrite by the command in push operation

# transaction
def increment_transaction(current_val):
    return current_val + 1

db.reference("/run_id").transaction(increment_transaction)
print(ref.get())

# delete operation
db.reference("/Programming Language").delete()
print(ref.get())

# Learn on: https://youtu.be/BnrkTpgH5Vc