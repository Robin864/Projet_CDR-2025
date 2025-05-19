#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#include "UniBoardV4Def.h"

#include "Strategy.h"

struct {
    bool tir = false;
    char team = 'b';
} message;

void fullstop();

Timer timer(&fullstop, DEFAULT_GAME_DURATION, seconds, false);
Strategy strategy;

void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&message, incomingData, sizeof(message));
}

void setPinsStates()
{
    pinMode(TEAM_PIN, INPUT_PULLUP);
    pinMode(INIT_PIN, INPUT_PULLUP);
    pinMode(TIR_PIN, INPUT_PULLUP);

    pinMode(PIN::Steppers::EN, OUTPUT);
    digitalWrite(PIN::Steppers::EN, LOW);
}

void setupESPNow()
{
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK)
    {
        ERROR("ESP-NOW initialization failed");
    }

    esp_now_register_recv_cb(onDataRecv);
}

void waitStart()
{
    while(message.tir)
        delay(1);

    while(!message.tir)
        delay(1);
}

void setup()
{
    Serial.begin(115200);

    setPinsStates();
    setupESPNow();

    strategy.setup();
}

void loop()
{
    // strategy.init();
    waitStart();
    timer.start();
    strategy.game();
}

void fullstop()
{
    strategy.fullstop();
}
