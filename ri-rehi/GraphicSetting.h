#pragma once
class GraphicSetting
{
public:
	static int32 getScaleRate();
	static int32 getNormalTileWidth();
	static int32 getNormalTileHeight();
	static int32 getOriginalTileWidth();
	static int32 getOriginalTileHeight();

	//タイルマップの生成ぐらいにしか使わないのでは？
	static int32 getExtendedLength();
	static int32 getExtendedTileWidth();
	static int32 getExtendedTileHeight();

	static ColorF getPINK();
	static ColorF getSKY();
	static ColorF getYELLOW();
	static ColorF getLIME();

	static ColorF rarity2ColorF(int32 rarity);

private:
	static int32 SCALE_RATE;
	static int32 EXTENDED_LENGTH;
	static int32 NORMAL_TILE_WIDTH;
	static int32 NORMAL_TILE_HEIGHT;
	static int32 ORIGINAL_TILE_WIDTH;
	static int32 ORIGINAL_TILE_HEIGHT;

	static ColorF PINK;
	static ColorF SKY;
	static ColorF YELLOW;
	static ColorF LIME;
};

