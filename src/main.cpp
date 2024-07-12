#include <iostream>

#include <WiFi.h>
// #include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include <ArduinoJson.h>
#include "listCollection.h"
#include "../.variables/variables.h" //Modify path according to your need
// #include "putvariables.h"

const char* ssid; 
const char* password;

AsyncWebServer server(80);

void setup() {

    Serial.begin(9600);
    // Initialize SPIFFS
    if(!SPIFFS.begin(true)){
        Serial.println("An Error has occurred while mounting SPIFFS");
        return ;
    }

    const char* ssid = SSID; //Enter your WiFi Name here
    const char* password = SSID_PASSWORD; // Enter your WiFi Password here

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }

    // Print ESP32 Local IP Address
    Serial.println(WiFi.localIP());

    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/index.html", "text/html");
    });
    
    // Route to load style.css file
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/style.css", "text/css");
    });

    // Route to serve the collections as JSON
    server.on("/collections", HTTP_GET, [](AsyncWebServerRequest *request){
        DynamicJsonDocument doc(2048); // Adjust size as needed
        JsonArray collectionsArray = doc.createNestedArray("collections");

        for (int i = 0; i < sizeof(collections) / sizeof(collections[0]); ++i) {
        JsonObject collection = collectionsArray.createNestedObject();
        collection["name"] = collections[i].name;
        JsonArray effectsArray = collection.createNestedArray("elements");

        for (int j = 0; j < sizeof(collections[i].elements) / sizeof(Element); ++j) {
            if (collections[i].elements[j].name == nullptr) break; // Stop at the end marker

            JsonObject effect = effectsArray.createNestedObject();
            effect["name"] = collections[i].elements[j].name;
            effect["elements"] = collections[i].elements[j].raw_element;
            JsonArray settingsArray = effect.createNestedArray("settings");

            for (int k = 0; k < sizeof(collections[i].elements[j].settings) / sizeof(int); ++k) {
            if (collections[i].elements[j].settings[k] == 0) break; // Stop at the end marker
            settingsArray.add(collections[i].elements[j].settings[k]);
            }
        }
        }

        String jsonString;
        serializeJson(doc, jsonString);
        request->send(200, "application/json", jsonString);
    });

    // Start server
    server.begin();
}

void loop() {
    Serial.println("Waiting...");
    delay(5000);
    // No particular goal here
}