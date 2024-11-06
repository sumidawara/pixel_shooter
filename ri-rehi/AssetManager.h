#pragma once
class AssetManager
{
public:
	static AssetName tilemapX_Y(int32 x, int32 y);
	static AssetName tilemapX_Y(int32 index_where_empty_cell_is_minus_one);
	static void registerAsset();
	static void registerImage();
	static void registerFont();
	static void registerPixelShader();

private:
	static int32 _tilemap_g_width;
	static std::unique_ptr<TextureAssetData> image2TextureAssetData(Image image);
	static Image tileMapExtend(Image old_image);
	static void registerTileFromTileMap(const Image& extended_image);

	static void registerAbilityIconFromKey(StringView key);
	// static String append_large_suffix(StringView str);
	// static String append_small_suffix(StringView str);
};

