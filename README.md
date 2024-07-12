# From C to JSON to HTML

## Overview

During the development of Lesk ([www.lesklights.com](http://www.lesklights.com)), I encountered the challenge of fetching and displaying various effects and collections of effects on an HTML page. This repository provides a standalone solution to this problem.

## Purpose

This project demonstrates how to manage unique elements organized into collections and display them on a web page. By navigating to `/index.html`, you can view all the collections, each with their respective elements and settings.

## Features

- **Element and Collection Management:** Define unique elements and group them into collections in C.
- **Dynamic Web Page Generation:** Automatically generate and display collections and their elements on a web page (for now, only collections but we can imagine to add more features later).
- **JSON Data Handling:** Use JSON for efficient data transfer between the server and the client.

## How It Works

1. **Data Definition:**
   - Define elements and collections in C.
   - Store essential information about elements and collections in a structured format.

2. **Data Conversion:**
   - Convert C structures into JSON format.
   - Serve the JSON data to the web client.

3. **Web Page Display:**
   - Fetch JSON data using JavaScript.
   - Dynamically create and populate HTML elements to display collections and their settings.

## Getting Started

### Prerequisites

- An ESP32 development board.
- SPIFFS (SPI Flash File System) setup for serving HTML, CSS, and JSON files.
- Basic knowledge of C/C++, HTML, and JavaScript.
- Librairies : WiFi.h, AsyncTCP.h, ESPAsyncWebServer.h, SPIFFS.h, ArduinoJson.h

### Use

Run using platformio

### Variables

You can modify your SSID and SSID_PASSWORD in the file "putvariables.h"
