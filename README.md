# Test the data processing stream between ESP, Firebase and Python

## Before you move on
"This project is a personal testing initiative and is not intended for teaching purposes. It is neither an official course nor designed as primary learning material. Please refrain from using it as a main resource for educational purposes."

## Warning
"Use this project with caution. It is a personal test project and not intended for educational purposes. Proceed at your own risk."

# Data Processing Stream

1. Sensor -> ESP
2. ESP -> Firebase
3. Firebase -> Python
4. Python -> Firebase
5. Firebase -> ESP

# Requirements needed to run

## Install package/library for Python

### 1. Python

- Check if Python is installed.
    ```
    py --version
    ```

- If it said Python is not installed, you can go to [Python.org](https://www.python.org/downloads/) to install it.

    > [!IMPORTANT]  
    > You must check the section "Add Python to PATH" while installing.
    - Check again if Python is installed.
        ```
        py --version
        ```
### 2. Firebase-admin

- To connect to Firebase, you need to install firebase_admin package.
    ```
    pip install firebase-admin
    ```
### 3. Python-dotenv

- To use variables from .env file to Python files, you should install python-dotenv package.
    ```
    pip install python-dotenv
    ```

## Board/Library needs for Arduino app

### Board
- **esp8266** by ESP8266

### Library

- **Firebase Arduino Client Library for ESP8266 and ESP32** by Mobizt

    > [!WARNING]  
    > At the time I wrote this file I realized that the above library has been deprecated, you can use **Firebase** by Rupak Poddar, but it needs changing some codes by yourself.

## Download Credentials.json

1. Go to your Firebase project (if you don't have, create one).
2. Click on the setting on the right of the **Project Overview** on sidebar > **Project settings**.
3. Click on **Service accounts** tab.
4. Click **Generate new private key** button.
5. Move the download file to your Python project.

## Permission for Firebase
- Each below section shows as each Project shortcut on Firebase.

### 1. Authentication
- Requiring Anonymous provider
    1. Go to Authentication shortcut.
    2. Go to Sign-in method.
    3. Click **Add new provider** button.
    4. Select **Anonymous**.

### 2. Realtime Database

1. Go to Realtime Database shortcut.
2. Choose **Create database**.
3. Choose your closest Realtime Database location to your location and click Next.
4. Choose **Start in test mode** and click Enable.
5. In database, create 2 nodes:
    - Sensor
        - distance: 0 (number)
    - Result
        - led: false (boolean)

## Environment variables

### Python file
1. Copy .env.example file to the same folder
2. Rename to .env
3. Add value to variables
    - FIREBASE_DB_URL: Database URL of Firebase (looks like this: \<your profile name\>.\<RT DB location\>.firebasedatabase.app/)
    - PATH_TO_CRED: Credentials file downloaded from Firebase.

### Arduino file
- Add value to variables
    - WIFI_SSID: your wifi name
    - WIFI_PASSWORD: your wifi password
    - API_KEY: Firebase API Key (Beside Project Overview: Project settings > General > Web API Key)
    - DATABASE_URL: Database URL of Firebase (see above)


# Accessories
- 1x Most types supported ESP (from now I will call as ESP)
- 1x Led
- 1x Resistor
- 1x Ultrasonic sensor (HC-SR04)
- 1x Breadboard (optional)
- Wires

# Connect accessories together
- Uh ... It's hard to describe and I don't have time to draw it so I will say simple.
- Before move on, remember that you can connect pin from accessory to ESP using Breadboard as bridge connection.
    - HC-SR04
        - (VCC) connects to 5V pin on ESP.
        - (GND) connects to GND pin on ESP.
        - (Trigger) connects to TRIG_PIN defined on ino file.
        - (Echo) connects to ECHO_PIN defined on ino file.
    - Led
        - (+) connects to Resistor.
        - (-) connects to GND pin on ESP.
    - Resistor
        - One is connected to (+) led.
        - The other connects to 5V pin on ESP.

# Upload ino file to ESP

1. Open Arduino app.
2. Upload ino file.
3. You're good to go.

# So what's now?

I guess you can run the project now, run both ESP, Python file and see the result.

If it doesn't work as expected, you can visit the below link I provided, ask GPT, contact me if you know me or open issue on Github. All are possibles but I will contact with you if I have time.

This repo is small so I don't expect it too much, but this is my hobby to write code and this README file.

Finally, thank you for reading this repo. Wish you have a good day and no bug!

# Learn sources
- [05 Firebase Realtime Database + ESP32 | How to save sensor data & read data to control devices?](https://youtu.be/aO92B-K4TnQ) by Education is Life (joed goh)
- [How to Connect Your Python Application to Firebase Realtime Database](https://youtu.be/BnrkTpgH5Vc) by All About Python.
*Thank you so much for teaching me about coding this.*
