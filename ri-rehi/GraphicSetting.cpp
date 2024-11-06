#include "stdafx.h"
#include "GraphicSetting.h"

int32 GraphicSetting::SCALE_RATE = 4;
int32 GraphicSetting::EXTENDED_LENGTH = 10;
int32 GraphicSetting::NORMAL_TILE_WIDTH = 128;
int32 GraphicSetting::NORMAL_TILE_HEIGHT = 128;
int32 GraphicSetting::ORIGINAL_TILE_WIDTH = 32;
int32 GraphicSetting::ORIGINAL_TILE_HEIGHT = 32;

ColorF GraphicSetting::PINK = ColorF{0.95, 0.12, 1.0, 1.0};
ColorF GraphicSetting::SKY = ColorF{0.275, 1.0, 1.0, 1.0};
ColorF GraphicSetting::YELLOW = ColorF{0.95, 1.0, 0.15, 1.0}; //243.2, 255, 38.4


int32 GraphicSetting::getScaleRate() {
	return SCALE_RATE;
}

int32 GraphicSetting::getExtendedLength()
{
	return EXTENDED_LENGTH;
}

int32 GraphicSetting::getNormalTileWidth() {
	return NORMAL_TILE_WIDTH;
}

int32 GraphicSetting::getNormalTileHeight() {
	return NORMAL_TILE_HEIGHT;
}

int32 GraphicSetting::getOriginalTileWidth() {
	return ORIGINAL_TILE_WIDTH;
}

int32 GraphicSetting::getOriginalTileHeight() {
	return ORIGINAL_TILE_HEIGHT;
}

int32 GraphicSetting::getExtendedTileWidth()
{
	return NORMAL_TILE_WIDTH + EXTENDED_LENGTH * 2;
}

int32 GraphicSetting::getExtendedTileHeight()
{
	return NORMAL_TILE_HEIGHT + EXTENDED_LENGTH * 2;
}

ColorF GraphicSetting::getPINK()
{
	return PINK;
}

ColorF GraphicSetting::getSKY()
{
	return SKY;
}

ColorF GraphicSetting::getYELLOW()
{
	return  YELLOW;
}
