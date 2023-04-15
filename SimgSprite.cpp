#include "SimgSprite.h"

SimgSprite::SimgSprite(TFT_eSPI *obj)
{
    tft = obj;
    if (!SPIFFS.begin())
    {
        Serial.println("LittleFS initialisation failed!");
        while (1)
            yield();
    }
    
}

SimgSprite::~SimgSprite()
{
    // Destructor implementation
}

TFT_eSprite *SimgSprite::load(const char * fileName)
{
    File file = SPIFFS.open(fileName, "r");
    if (!file)
    {
        Serial.println("Failed to open file");
        return nullptr;
    }
    uint16_t mwidth;
    uint16_t mheight;
    uint8_t format;
    uint32_t total_len;
    uint16_t pixel;
    uint8_t count;
    uint16_t x;
    uint16_t y;
    x = 0;
    y = 0;

    file.readBytes((char *)&mwidth, sizeof(mwidth));
    file.readBytes((char *)&mheight, sizeof(mheight));
    file.readBytes((char *)&format, sizeof(format));
    total_len = static_cast<uint32_t>(mwidth) * static_cast<uint32_t>(mheight);
    Serial.printf("mwidth: %u, mheight: %u, Format: %u len: %u\n", mwidth, mheight, format, total_len);

    TFT_eSprite *sprite = new TFT_eSprite(tft);
    sprite->createSprite(mwidth, mheight);


    if (format == 1)
    {
        while (total_len > 0)
        {
            file.readBytes((char *)&pixel, sizeof(pixel));
            // Serial.printf("x: %u, y: %u, color: 0x%04X\n", x, y, pixel);
            sprite->drawPixel(x, y, pixel);
            incrementCoordinates(x, y, mwidth, total_len);
        }
    }
    else
    {
        while (total_len > 0)
        {
            file.readBytes((char *)&pixel, sizeof(pixel));
            file.readBytes((char *)&count, sizeof(count));
            // Serial.printf("x: %u, y: %u, color: 0x%04X\n", x, y, pixel);
            sprite->drawPixel(x, y, pixel);
            incrementCoordinates(x, y, mwidth, total_len);
            while (count > 0)
            {
                count--;
                // Serial.printf("x: %u, y: %u, color: 0x%04X\n", x, y, pixel);
                sprite->drawPixel(x, y, pixel);
                incrementCoordinates(x, y, mwidth, total_len);
            }
        }
    }
    file.close();

    return sprite;
}

void SimgSprite::incrementCoordinates(uint16_t &x, uint16_t &y, const uint16_t width, uint32_t &total_len)
{
    total_len--;
    x++;
    if (x >= width)
    {
        x = 0;
        y++;
    }
}
/*
TFT_eSprite *SimgSprite::load(String fileName)
{
    File file = SPIFFS.open(fileName, "r");
    if (!file)
    {
        Serial.println("Failed to open file");
        return nullptr;
    }
    uint16_t data;
    uint16_t width;
    uint16_t height;
    file.readBytes((char *)&width, sizeof(width));
    file.readBytes((char *)&height, sizeof(height));
    // Implementation of mkSprite function
    TFT_eSprite *sprite = new TFT_eSprite(tft);
    sprite->createSprite(width, height);

    for (uint16_t i = 0; i < height; i++)
    {
        for (uint16_t j = 0; j < width; j++)
        {
            file.readBytes((char *)&data, sizeof(data));
            sprite->drawPixel(j, i, data);
        }
    }

    file.close();
    return sprite;
}
*/