#pragma once

#include "Lamp.h"
#include <OneWire.h>
#include <DallasTemperature.h>

class DS18B20 {
    public:
        DS18B20(uint8_t pin) {
            _oneWire = new OneWire(pin);
            // discoverOneWireDevices(_oneWire);
            _sensor = new DallasTemperature(_oneWire);
            _sensor->begin();
            logger.log("Found %d OneWire devices.", _sensor->getDeviceCount());
            logger.log("Found %d DS18 devices.", _sensor->getDS18Count());
        }

        int8_t getTemperature() {
            _oneWire->reset_search();
            DeviceAddress deviceAddress;
            uint8_t depth = 0;
            uint8_t index = 0;

            logger.log("Starging search.");

            while (_oneWire->search(deviceAddress)) {
                logger.log("Found a device...");
                if (_sensor->validAddress(deviceAddress)) {
                    logger.log("Address is valid.");
                } else {
                    logger.log("Address is NOT valid.");
                }
            }

            logger.log("Done.");

            _sensor->requestTemperatures();
            delay(1000);
            return _sensor->getTempCByIndex(0);
        }

        void discoverOneWireDevices(OneWire ow) {
            byte i;
            byte addr[8];

            logger.log("Looking for 1-Wire devices...");
            while(ow.search(addr)) {
                logger.log("Found '1-Wire' device with address:");
                logger.log("%02X, %02X, %02X, %02X, %02X, %02X, %02X, %02X", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5], addr[6], addr[7]);
                if ( OneWire::crc8( addr, 7) != addr[7]) {
                    logger.log("CRC is not valid!\n");
                }
            }
            logger.log("That's it.");
            ow.reset_search();
            return;
        }

    private:
        DallasTemperature* _sensor;
        OneWire* _oneWire;
};