# Smart Irrigation System

An Arduino Uno R4 WiFi–based automated irrigation system for orchards.

## Features

- Moisture sensors (4 zones)
- ESP32-CAM live feed
- Manual and automatic irrigation
- Solar powered (optional)
- Firebase / Dropbox / ThingSpeak cloud upload
- Telegram alerts

## Folder Guide

- `arduino/`: Core controller code + integrations
- `esp32-cam/`: ESP32-CAM snapshot uploader
- `dashboard/`: Hosted UI (Netlify, Firebase)
- `diagrams/`: Wiring, solar, layout (PDF, PNG)
