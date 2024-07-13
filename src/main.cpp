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

    server.on("/collection", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/collection.html", "text/html");
    });

    // Route to serve the collections as JSON
    server.on("/api/collections", HTTP_GET, [](AsyncWebServerRequest *request){
        DynamicJsonDocument doc(2048); // Adjust size as needed
        // Create an object for all the collections, like a degree 1
        JsonArray collectionsArray = doc.createNestedArray("collections"); // Print 1

        // Iterate through all the collections
        for (int i = 0; i < sizeof(collections) / sizeof(collections[0]); ++i) {
        // Create a JSON Object for each collection
        JsonObject collection = collectionsArray.createNestedObject();

        // Add the name of the collections
        collection["name"] = collections[i].name;
        // Serial.print("Je teste la collectionArray: ");
        // Serial.println(collections[i].name);
        // Create another degree/level
        JsonArray effectsArray = collection.createNestedArray("elements");

        // Iterate through all the elements up until there is the end
        for (int j = 0; j < sizeof(collections[i].elements) / sizeof(Element); ++j) {
            if (collections[i].elements[j].name == nullptr) break; // Stop at the end marker
            // Then create new Object
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
        // Convert the JSON document to a string
        // Send 200 OK
        String jsonString;
        serializeJson(doc, jsonString);
        request->send(200, "application/json", jsonString);
    });

    // API endpoint to get collection data
    server.on("/api/collection", HTTP_GET, [](AsyncWebServerRequest *request){
        if (request->hasParam("name")) {
            Serial.println("We can get the request name here");
            Serial.println(request->getParam("name")->value());
            DynamicJsonDocument doc(2048);
            JsonArray collectionsArray = doc.createNestedArray("collections");
            // Iterate through all the collections
            for (int i = 0; i < sizeof(collections) / sizeof(collections[0]); ++i) {
                if (request->getParam("name")->value() == collections[i].name) {
                    Serial.println("Comparing string values");
                    Serial.println(request->getParam("name")->value());
                    Serial.println(collections[i].name);
                    // Create a JSON Object for each collection
                    JsonObject collection = collectionsArray.createNestedObject();

                    // Add the name of the collections
                    collection["name"] = collections[i].name;
                    // Serial.print("Je teste la collectionArray: ");
                    // Serial.println(collections[i].name);
                    // Create another degree/level
                    JsonArray effectsArray = collection.createNestedArray("elements");

                    // Iterate through all the elements up until there is the end
                    for (int j = 0; j < sizeof(collections[i].elements) / sizeof(Element); ++j) {
                        if (collections[i].elements[j].name == nullptr) break; // Stop at the end marker
                        // Then create new Object
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
        }
        // Convert the JSON document to a string
        // Send 200 OK
        String jsonString;
        serializeJson(doc, jsonString);
        request->send(200, "application/json", jsonString);
        } else {
        request->send(400, "application/json", "{\"error\":\"No id provided\"}");
        }
    });

    // Start server
    server.begin();
}

void loop() {
    Serial.println("Waiting...");
    delay(5000);
    // No particular goal here
}