#ifndef _SIMGSPRITE_H
#define _SIMGSPRITE_H
#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>
#include <TFT_eSPI.h>

class SimgSprite{
    public:
        uint16_t TRANS = 65503; //0b1111111111011111
        TFT_eSPI* tft;
        SimgSprite(TFT_eSPI *tft);
        ~SimgSprite();
        TFT_eSprite* load(const char * fileName);
        void incrementCoordinates(uint16_t &x, uint16_t &y, const uint16_t width,uint32_t &total_len);
};


#endif //_SIMGSPRITE_H