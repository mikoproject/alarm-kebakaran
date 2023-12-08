//Coba 1
//Coba 2
//coba 3
//coba 4
#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>


//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "TP-Link Boiler"
#define WIFI_PASSWORD "BatuBara123."

// Insert Firebase project API Key
#define API_KEY "AIzaSyDm4UG11Kfrqkk7rPUpSYTseTZq6vfyUUY"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://fir-fire-alarm-default-rtdb.firebaseio.com/"

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int intValue;
float floatValue;
bool signupOK = false;

int AG1 = 19;
int AG2 = 16;
int Efrata = 3;
int Gdkps = 1;
int WV2 = 26;
int SP3 = 4;
int WV1 = 21;
int SP2 = 22;
int GdgCD = 25;
int SP1 = 18;
int Gdgbng = 23;
int GdgAB = 17;
int Ptmas = 33;
int DP = 5;
int KfABC = 13;
int Kfpack = 2;
int KfAB = 32;
int Kfpers = 14;
int Sirine = 2;  //27

int count = 0;

int Sirine_PTmas;
int Sirine_AG1;
int Sirine_AG2;
int Sirine_DP;
int Sirine_ER;
int Sirine_Gdbng;
int Sirine_GdgreigeAB;
int Sirine_GdgreigeCD;
int Sirine_Gdkps;
int Sirine_Kf1AB;
int Sirine_Kf2ABC;
int Sirine_Kfpack;
int Sirine_Kfpers;
int Sirine_SP1;
int Sirine_SP2;
int Sirine_SP3;
int Sirine_WV1;
int Sirine_WV2;

boolean a1 = 0;
boolean a2 = 0;
boolean a3 = 0;
boolean a4 = 0;
boolean a5 = 0;
boolean a6 = 0;
boolean a7 = 0;
boolean a8 = 0;
boolean a9 = 0;
boolean a10 = 0;
boolean a11 = 0;
boolean a12 = 0;
boolean a13 = 0;
boolean a14 = 0;
boolean a15 = 0;
boolean a16 = 0;
boolean a17 = 0;
boolean a18 = 0;


void setup() {
  Serial.begin(115200);
  pinMode(Ptmas, OUTPUT);
  digitalWrite(Ptmas, LOW);
  pinMode(AG1, OUTPUT);
  digitalWrite(AG1, LOW);
  pinMode(AG2, OUTPUT);
  digitalWrite(AG2, LOW);
  pinMode(Efrata, OUTPUT);
  digitalWrite(Efrata, LOW);
  pinMode(Gdkps, OUTPUT);
  digitalWrite(Gdkps, LOW);
  pinMode(WV2, OUTPUT);
  digitalWrite(WV2, LOW);
  pinMode(SP3, OUTPUT);
  digitalWrite(SP3, LOW);
  pinMode(WV1, OUTPUT);
  digitalWrite(WV1, LOW);
  pinMode(SP1, OUTPUT);
  digitalWrite(SP1, LOW);
  pinMode(SP2, OUTPUT);
  digitalWrite(SP2, LOW);
  pinMode(GdgCD, OUTPUT);
  digitalWrite(GdgCD, LOW);
  pinMode(Gdgbng, OUTPUT);
  digitalWrite(Gdgbng, LOW);
  pinMode(GdgAB, OUTPUT);
  digitalWrite(GdgAB, LOW);
  pinMode(DP, OUTPUT);
  digitalWrite(DP, LOW);
  pinMode(KfABC, OUTPUT);
  digitalWrite(KfABC, LOW);
  pinMode(Kfpack, OUTPUT);
  digitalWrite(Kfpack, LOW);
  pinMode(KfAB, OUTPUT);
  digitalWrite(KfAB, LOW);
  pinMode(Kfpers, OUTPUT);
  digitalWrite(Kfpers, LOW);
  pinMode(Sirine, OUTPUT);  //digitalWrite(Sirine, LOW);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback;  //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  count = count + 1;
  Serial.println(count);
  if (count > 30) {
    ESP.restart();
  }
  //digitalWrite(Ptmas,Firebase.getString("/PTmas").toInt())
  if (Firebase.RTDB.getString(&fbdo, "/PTmas")) {
    if (fbdo.stringData() == "1") {
      a1 = 1;
      //Firebase.RTDB.setInt(&fbdo, "/a1", 1);
      Serial.println("Alarm Kebakaran PT.MAS ON");
      digitalWrite(Ptmas, HIGH);
      //digitalWrite(Sirine, HIGH);
    }
    if (fbdo.stringData() == "0")

    {
      //Firebase.RTDB.setInt(&fbdo, "/a1", 0);
      a1 = 0;
      Serial.println("Alarm Kebakaran PT.MAS OFF");
      digitalWrite(Ptmas, LOW);
    }
  }
  if (Firebase.RTDB.getString(&fbdo, "/AG1")) {
    if (fbdo.stringData() == "1") {
      //Firebase.RTDB.setInt(&fbdo, "/a2", 1);
      a2 = 1;
      Serial.println("Alarm Kebakaran PT.AG1 ON");
      digitalWrite(AG1, HIGH);
      //digitalWrite(Sirine, HIGH);
    }
    if (fbdo.stringData() == "0") {
      //Firebase.RTDB.setInt(&fbdo, "/a2", 0);
      a2 = 0;
      Serial.println("Alarm Kebakaran PT.AG1 OFF");
      digitalWrite(AG1, LOW);
    }
  }
  if (Firebase.RTDB.getString(&fbdo, "/AG2")) {
    if (fbdo.stringData() == "1") {
      //Firebase.RTDB.setInt(&fbdo, "/a3", 1);
      a3 = 1;
      Serial.println("Alarm Kebakaran PT.AG2 ON");
      digitalWrite(AG2, HIGH);
      //digitalWrite(Sirine, HIGH);
    }
    if (fbdo.stringData() == "0") {
      //Firebase.RTDB.setInt(&fbdo, "/a3", 0);
      a3 = 0;
      Serial.println("Alarm Kebakaran PT.AG2 OFF");
      digitalWrite(AG2, LOW);
    }
  }
  if (Firebase.RTDB.getString(&fbdo, "/ER")) {
    if (fbdo.stringData() == "1") {
      //Firebase.RTDB.setInt(&fbdo, "/a4", 1);
      a4 = 1;
      Serial.println("Alarm Kebakaran PT.EFRATA ON");
      digitalWrite(Efrata, HIGH);
      //digitalWrite(Sirine, HIGH);
    }
    if (fbdo.stringData() == "0") {
      //Firebase.RTDB.setInt(&fbdo, "/a4", 0);
      a4 = 0;
      Serial.println("Alarm Kebakaran PT.EFRATA OFF");
      digitalWrite(Efrata, LOW);
    }
  }
  if (Firebase.RTDB.getString(&fbdo, "/Gdkps")) {
    if (fbdo.stringData() == "1") {
      //Firebase.RTDB.setInt(&fbdo, "/a5", 1);
      a5 = 1;
      Serial.println("Alarm Kebakaran Gudang Kapas ON");
      digitalWrite(Gdkps, HIGH);
      //digitalWrite(Sirine, HIGH);
    }
    if (fbdo.stringData() == "0") {
      //Firebase.RTDB.setInt(&fbdo, "/a5", 0);
      a5 = 0;
      Serial.println("Alarm Kebakaran Gudang Kapas OFF");
      digitalWrite(Gdkps, LOW);
    }
  }
  if (Firebase.RTDB.getString(&fbdo, "/WV2")) {
    if (fbdo.stringData() == "1") {
      //Firebase.RTDB.setInt(&fbdo, "/a6", 1);
      a6 = 1;
      Serial.println("Alarm Kebakaran Weaving 2 ON");
      digitalWrite(WV2, HIGH);
      //digitalWrite(Sirine, HIGH);
    }
    if (fbdo.stringData() == "0") {
      //Firebase.RTDB.setInt(&fbdo, "/a6", 0);
      a6 = 0;
      Serial.println("Alarm Kebakaran Weaving 2 OFF");
      digitalWrite(WV2, LOW);
    }
  }
  if (Firebase.RTDB.getString(&fbdo, "/SP3")) {
    if (fbdo.stringData() == "1") {
      //Firebase.RTDB.setInt(&fbdo, "/a7", 1);
      a7 = 1;
      Serial.println("Alarm Kebakaran Spinning 3 ON");
      digitalWrite(SP3, HIGH);
      //digitalWrite(Sirine, HIGH);
    }
    if (fbdo.stringData() == "0") {
      //Firebase.RTDB.setInt(&fbdo, "/a7", 0);
      a7 = 0;
      Serial.println("Alarm Kebakaran Spinning 3 OFF");
      digitalWrite(SP3, LOW);
    }
  }
  if (Firebase.RTDB.getString(&fbdo, "/WV1")) {
    if (fbdo.stringData() == "1") {
      //Firebase.RTDB.setInt(&fbdo, "/a8", 1);
      a8 = 1;
      Serial.println("Alarm Kebakaran Weaving 1 ON");
      digitalWrite(WV1, HIGH);
      //digitalWrite(Sirine, HIGH);
    }
    if (fbdo.stringData() == "0") {
      //Firebase.RTDB.setInt(&fbdo, "/a8", 0);
      a8 = 0;
      Serial.println("Alarm Kebakaran Weaving 1 OFF");
      digitalWrite(WV1, LOW);
    }
  }
  if (Firebase.RTDB.getString(&fbdo, "/TOH")) {
    if (fbdo.stringData() == "1") {
      //Firebase.RTDB.setInt(&fbdo, "/a9", 1);
      a9 = 1;
      Serial.println("Alarm Kebakaran Spinning 1 ON");
      digitalWrite(SP1, HIGH);
      //digitalWrite(Sirine, HIGH);
    }
    if (fbdo.stringData() == "0") {
      //Firebase.RTDB.setInt(&fbdo, "/a9", 0);
      a9 = 0;
      Serial.println("Alarm Kebakaran Spinning 1 OFF");
      digitalWrite(SP1, LOW);
    }
  }
  if (Firebase.RTDB.getString(&fbdo, "/SP2")) {
    if (fbdo.stringData() == "1") {
      //Firebase.RTDB.setInt(&fbdo, "/a10", 1);
      a10 = 1;
      Serial.println("Alarm Kebakaran Spinning 2 ON");
      digitalWrite(SP2, HIGH);
      //digitalWrite(Sirine, HIGH);
    }
    if (fbdo.stringData() == "0") {
      //Firebase.RTDB.setInt(&fbdo, "/a10", 0);
      a10 = 0;
      Serial.println("Alarm Kebakaran Spinning 2 OFF");
      digitalWrite(SP2, LOW);
    }
  }
  if (Firebase.RTDB.getString(&fbdo, "/GdgreigeCD")) {
    if (fbdo.stringData() == "1") {
      //Firebase.RTDB.setInt(&fbdo, "/a11", 1);
      a11 = 1;
      Serial.println("Alarm Kebakaran Gudang Greige CD ON");
      digitalWrite(GdgCD, HIGH);
      //digitalWrite(Sirine, HIGH);
    }
    if (fbdo.stringData() == "0") {
      //Firebase.RTDB.setInt(&fbdo, "/a11", 0);
      a11 = 0;
      Serial.println("Alarm Kebakaran Gudang Greige CD OFF");
      digitalWrite(GdgCD, LOW);
    }
  }
  if (Firebase.RTDB.getString(&fbdo, "/Gdbng")) {
    if (fbdo.stringData() == "1") {
      //Firebase.RTDB.setInt(&fbdo, "/a12", 1);
      a12 = 1;
      Serial.println("Alarm Kebakaran Gudang Benang ON");
      digitalWrite(Gdgbng, HIGH);
      //digitalWrite(Sirine, HIGH);
    }
    if (fbdo.stringData() == "0") {
      //Firebase.RTDB.setInt(&fbdo, "/a12", 0);
      a12 = 0;
      Serial.println("Alarm Kebakaran Gudang Benang OFF");
      digitalWrite(Gdgbng, LOW);
    }
  }
  if (Firebase.RTDB.getString(&fbdo, "/GdgreigeAB")) {
    if (fbdo.stringData() == "1") {
      //Firebase.RTDB.setInt(&fbdo, "/a13", 1);
      a13 = 1;
      Serial.println("Alarm Kebakaran Gudang Greige AB ON");
      digitalWrite(GdgAB, HIGH);
      //digitalWrite(Sirine, HIGH);
    }
    if (fbdo.stringData() == "0") {
      //Firebase.RTDB.setInt(&fbdo, "/a13", 0);
      a13 = 0;
      Serial.println("Alarm Kebakaran Gudang Greige AB OFF");
      digitalWrite(GdgAB, LOW);
    }
  }
  if (Firebase.RTDB.getString(&fbdo, "/DP")) {
    if (fbdo.stringData() == "1") {
      //Firebase.RTDB.setInt(&fbdo, "/a14", 1);
      a14 = 1;
      Serial.println("Alarm Kebakaran DP ON");
      digitalWrite(DP, HIGH);
      //digitalWrite(Sirine, HIGH);
    }
    if (fbdo.stringData() == "0") {
      //Firebase.RTDB.setInt(&fbdo, "/a14", 0);
      a14 = 0;
      Serial.println("Alarm Kebakaran DP OFF");
      digitalWrite(DP, LOW);
    }
  }
  if (Firebase.RTDB.getString(&fbdo, "/Kf2ABC")) {
    if (fbdo.stringData() == "1") {
      //Firebase.RTDB.setInt(&fbdo, "/a15", 1);
      a15 = 1;
      Serial.println("Alarm Kebakaran Konfeksi 2 ABC ON");
      digitalWrite(KfABC, HIGH);
      //digitalWrite(Sirine, HIGH);
    }
    if (fbdo.stringData() == "0") {
      //Firebase.RTDB.setInt(&fbdo, "/a15", 0);
      a15 = 0;
      Serial.println("Alarm Kebakaran Konfeksi 2 ABC OFF");
      digitalWrite(KfABC, LOW);
    }
  }
  if (Firebase.RTDB.getString(&fbdo, "/Kfpack")) {
    if (fbdo.stringData() == "1") {
      //Firebase.RTDB.setInt(&fbdo, "/a16", 1);
      a16 = 1;
      Serial.println("Alarm Kebakaran Konfeksi Packing ON");
      digitalWrite(Kfpack, HIGH);
      //digitalWrite(Sirine, HIGH);
    }
    if (fbdo.stringData() == "0") {
      //Firebase.RTDB.setInt(&fbdo, "/a16", 0);
      a16 = 0;
      Serial.println("Alarm Kebakaran Konfeksi Packing OFF");
      digitalWrite(Kfpack, LOW);
    }
  }
  if (Firebase.RTDB.getString(&fbdo, "/Kf1AB")) {
    if (fbdo.stringData() == "1") {
      //Firebase.RTDB.setInt(&fbdo, "/a17", 1);
      a17 = 1;
      Serial.println("Alarm Kebakaran Konfeksi 1 AB ON");
      digitalWrite(KfAB, HIGH);
      //digitalWrite(Sirine, HIGH);
    }
    if (fbdo.stringData() == "0") {
      //Firebase.RTDB.setInt(&fbdo, "/a17", 0);
      a17 = 0;
      Serial.println("Alarm Kebakaran Konfeksi 1 AB OFF");
      digitalWrite(KfAB, LOW);
    }
  }
  if (Firebase.RTDB.getString(&fbdo, "/Kfpers")) {
    if (fbdo.stringData() == "1") {
      //Firebase.RTDB.setInt(&fbdo, "/a18", 1);
      a18 = 1;
      Serial.println("Alarm Kebakaran Konfeksi Persiapan ON");
      digitalWrite(Kfpers, HIGH);
      //digitalWrite(Sirine, HIGH);
    }
    if (fbdo.stringData() == "0") {
      //Firebase.RTDB.setInt(&fbdo, "/a18", 0);
      a18 = 0;
      Serial.println("Alarm Kebakaran Konfeksi Persiapan Off");
      digitalWrite(Kfpers, LOW);
    }
  }
  if (a1 == 1 || a2 == 1 || a3 == 1 || a4 == 1 || a5 == 1 || a6 == 1 || a7 == 1 || a8 == 1 || a9 == 1 || a10 == 1 || a11 == 1 || a12 == 1 || a13 == 1 || a14 == 1 || a15 == 1 || a16 == 1 || a17 == 1 || a18 == 1) {
    digitalWrite(Sirine, HIGH);
  }
  if (a1 == 0 && a2 == 0 && a3 == 0 && a4 == 0 && a5 == 0 && a6 == 0 && a7 == 0 && a8 == 0 && a9 == 0 && a10 == 0 && a11 == 0 && a12 == 0 && a13 == 0 && a14 == 0 && a15 == 0 && a16 == 0 && a17 == 0 && a18 == 0) {
    digitalWrite(Sirine, LOW);
  }
}
