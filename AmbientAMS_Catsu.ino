
  #define BLYNK_TEMPLATE_ID "TMPL6CScbsN0c"
  #define BLYNK_TEMPLATE_NAME "Ambient Air Monitoring System"
  #define BLYNK_AUTH_TOKEN "[Your Auth Token]"
  #include <LiquidCrystal_I2C.h>
  #include <light_CD74HC4067.h>
  #include <ESP8266WiFi.h>
  #include <BlynkSimpleEsp8266.h>
  #include <Wire.h>
  BlynkTimer timer;
  LiquidCrystal_I2C lcd(0x27, 20, 4);
  WiFiClient client;
  char auth[] = "[Your Auth Token]";
  char ssid[] = "[Your Network ID]";
  char pass[] = "[Your Network Pass]";





              // s0 s1 s2 s3: select pins
  CD74HC4067 mux(D0, D1, D2, D3);  // create a new CD74HC4067 object with its four select lines - 8,9,10,11


  const int SIG = A0; // Pin A0 - Connected to Sig pin of CD74HC4067

  void sendData() //to blynk 
  {
    mux.channel(15);
    int BlynkCO2 = analogRead(SIG); // Generates a digital number from 0 to 4095
    Blynk.virtualWrite(V0, BlynkCO2);
    delay(100);
    Serial.print("Blynk CO2 Value : ");
    Serial.print(BlynkCO2);
    Serial.println();

    mux.channel(12);
    int BlynkCH4 = analogRead(SIG); // Generates a digital number from 0 to 4095
    Blynk.virtualWrite(V1, BlynkCH4);
    delay(100);
    Serial.print("Blynk CH4 Value : ");
    Serial.print(BlynkCH4);
    Serial.println();
    
    mux.channel(9);
    int BlynkCO = analogRead(SIG); // Generates a digital number from 0 to 4095
    Blynk.virtualWrite(V2, BlynkCO);
    delay(100);
    Serial.print("Blynk CO Value : ");
    Serial.print(BlynkCO);
    Serial.println();

    mux.channel(0);
    int BlynkSM = analogRead(SIG); // Generates a digital number from 0 to 4095
    Blynk.virtualWrite(V3, BlynkSM);
    delay(100);
    Serial.print("Blynk Smoke Value : ");
    Serial.print(BlynkSM);
    Serial.println();
    Serial.println(" ");




  }



  

  void setup()
  {
      Serial.begin(115200);
      Blynk.begin(auth, ssid, pass);
      timer.setInterval(1000L, sendData);
      
      pinMode(SIG, INPUT); // Set as input for reading through signal pin
      

      Wire.begin(D5, D6);   //Use predefined PINS consts
      lcd.begin(20,4);      // The begin call takes the width and height. This
                      // Should match the number provided to the constructor.

      lcd.backlight();      // Turn on the backlight.

      lcd.home();

      lcd.setCursor(0, 0);  // Move the cursor at origin

      lcd.println("Connecting to WiFi..");
      delay(500);
      lcd.clear();
      Serial.println("Connecting to WiFi..");

      WiFi.begin(ssid, pass); //Wi-Fi Name & Password
      while (WiFi.status() != WL_CONNECTED)
      {
        delay(500);
        Serial.print(".");
      }
      delay(1000);
      lcd.clear();
      lcd.println(" ");
      lcd.println("WiFi connected");
      Serial.println(" ");
      Serial.println("WiFi connected");
      delay(1000);

      lcd.clear();
      lcd.setCursor(7, 0);
      lcd.print("CatSU");
      lcd.setCursor(4, 1);
      lcd.print("Ambient  Air ");
      lcd.setCursor(5, 2);
      lcd.print("Monitoring");
      lcd.setCursor(7, 3);
      lcd.print("System");
      delay(1000);
      lcd.clear();
    


  }


  void loop()
  {
    Blynk.run();
    timer.run();
    mux.channel(15);
    int valMQ135 = analogRead(SIG); 
    delay(500);

    mux.channel(12);
    int valMQ9 = analogRead(SIG); 
    delay(500);

    mux.channel(9);
    int valMQ7 = analogRead(SIG); 
    delay(500);

    
    mux.channel(0);
    int valMQ2 = analogRead(SIG); 
    delay(500);

    //MQ135 CARBON DIOXIDE
    lcd.setCursor(0, 0);
    lcd.print("CO2 Value: ");
    lcd.print(valMQ135);
    lcd.setCursor(16, 0);
    lcd.print("ppm");
    
    //MQ9 Methane
    lcd.setCursor(0, 1);
    lcd.print("CH4 Value: ");
    lcd.print(valMQ9);
    lcd.setCursor(16, 1);
    lcd.print("ppm");

    //MQ7 Methane
    lcd.setCursor(0, 2);
    lcd.print("CO  Value: ");
    lcd.print(valMQ7);
    lcd.setCursor(16, 2);
    lcd.print("ppm");
    


    //MQ2 Methane
    lcd.setCursor(0, 3);
    lcd.print("Smk Value: ");
    lcd.print(valMQ2);
    lcd.setCursor(16, 3);
    lcd.print("ppm");

    delay(2000);
    lcd.clear();

    //if (valMQ135 >= 180)
    //{
      //Blynk.logEvent("co2_alert", "High levels of Carbon Dioxide"); //notifies through the IoT platform
    //}
    

  }
