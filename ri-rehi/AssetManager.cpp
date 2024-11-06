#include "stdafx.h"
#include "AssetManager.h"

#include "AssetKey.h"
#include "GraphicSetting.h"

int32 AssetManager::_tilemap_g_width = 5;

AssetName AssetManager::tilemapX_Y(int32 x, int32 y)
{
	return U"tilemap" + ToString(x) + U"_" + ToString(y);
}

AssetName AssetManager::tilemapX_Y(int32 index_where_empty_cell_is_minus_one)
{
	if(index_where_empty_cell_is_minus_one == -1)
	{
		return U"empty32x32";
	}

	return tilemapX_Y(
		index_where_empty_cell_is_minus_one % _tilemap_g_width,
		index_where_empty_cell_is_minus_one / _tilemap_g_width);
}


void AssetManager::registerAsset()
{
	registerImage();
	registerFont();
	registerPixelShader();
}

void AssetManager::registerImage()
{
	int32 SCALE_RATE = GraphicSetting::getScaleRate();

	//タイルマップ
	Image original_tilemap_image{ U"resources/img/tilemap.png" };
	Image scaled_tilemap_image = original_tilemap_image.scale(SCALE_RATE, InterpolationAlgorithm::Nearest);
	Image extended_tilemap = tileMapExtend(scaled_tilemap_image);
	registerTileFromTileMap(extended_tilemap);

	//プレイヤー
	Image original_liebesrechner_stand_image{ U"resources/img/liebesrechner32x32_stand.png" };
	Image scaled_liebesrechner_stand_image = original_liebesrechner_stand_image.scale(SCALE_RATE, InterpolationAlgorithm::Nearest);
	TextureAsset::Register(AssetKey::liebesrechner_stand, image2TextureAssetData(scaled_liebesrechner_stand_image));

	Image original_liebesrechner_run_image{ U"resources/img/liebesrechner32x32_run.png" };
	Image scaled_liebesrechner_run_image = original_liebesrechner_run_image.scale(SCALE_RATE, InterpolationAlgorithm::Nearest);
	TextureAsset::Register(AssetKey::liebesrechner_run, image2TextureAssetData(scaled_liebesrechner_run_image));

	//出口
	Image original_exit_image{U"resources/img/exit.png"};
	TextureAsset::Register(AssetKey::exit, image2TextureAssetData(original_exit_image.scale(SCALE_RATE, InterpolationAlgorithm::Nearest)));

	//鍵のかかった出口
	Image original_locked_exit_image{U"resources/img/locked_exit.png"};
	TextureAsset::Register(AssetKey::locked_exit, image2TextureAssetData(original_locked_exit_image.scale(SCALE_RATE, InterpolationAlgorithm::Nearest)));


	//スライム
	Image original_slime_image{ U"resources/img/slime.png" };
	TextureAsset::Register(AssetKey::slime, image2TextureAssetData(original_slime_image.scale(SCALE_RATE, InterpolationAlgorithm::Nearest)));

	//Abilityのアイコン
	Image original_blankicon_image{U"resources/img/blankicon.png"};
	TextureAsset::Register(U"blankicon_small", image2TextureAssetData(original_blankicon_image));
	TextureAsset::Register(U"blankicon_large", image2TextureAssetData(original_blankicon_image.scale(8, InterpolationAlgorithm::Nearest)));

	//きらめきエフェクト
	Image original_sparkle_image{ U"resources/img/sparkle.png" };
	TextureAsset::Register(AssetKey::sparkle, image2TextureAssetData(original_sparkle_image.scale(SCALE_RATE, InterpolationAlgorithm::Nearest)));
}

void AssetManager::registerFont()
{
	String pixel_m_plus_12_url = U"resources/font/PixelMplus12-Regular.ttf";
	String pixel_m_plus_12_bold_url = U"resources/font/PixelMplus12-Bold.ttf";

	// FontAsset::Register(U"pixel_12", 12, pixel_m_plus_12_url);
	// FontAsset::Register(U"pixel_24", 24, pixel_m_plus_12_url);
	// FontAsset::Register(U"pixel_36", 36, pixel_m_plus_12_url);
	// FontAsset::Register(U"pixel_48", 48, pixel_m_plus_12_url);
	// FontAsset::Register(U"pixel_60", 60, pixel_m_plus_12_url);

	FontAsset::Register(AssetKey::pixel_b12, 12, pixel_m_plus_12_bold_url);
	FontAsset::Register(AssetKey::pixel_b18, 18, pixel_m_plus_12_bold_url);
	FontAsset::Register(AssetKey::pixel_b24, 24, pixel_m_plus_12_bold_url);
	FontAsset::Register(AssetKey::pixel_b30, 30, pixel_m_plus_12_bold_url);
	FontAsset::Register(AssetKey::pixel_b36, 36, pixel_m_plus_12_bold_url);
	FontAsset::Register(AssetKey::pixel_b48, 48, pixel_m_plus_12_bold_url);
	FontAsset::Register(AssetKey::pixel_b60, 60, pixel_m_plus_12_bold_url);
	FontAsset::Register(AssetKey::pixel_b80, 80, pixel_m_plus_12_bold_url);
}

void AssetManager::registerPixelShader()
{
	PixelShaderAsset::Register(AssetKey::ps_default, HLSL{U"resources/shader/shader.hlsl", U"PS_Texture"});
}

std::unique_ptr<TextureAssetData> AssetManager::image2TextureAssetData(Image image)
{
	std::unique_ptr<TextureAssetData> ptr_texture_asset_data = std::make_unique<TextureAssetData>();
	ptr_texture_asset_data->onLoad = [image](TextureAssetData& data, const String&)
		{
			//Image tmpImage{ 256, 256, Palette::Skyblue };
			data.texture = Texture{ image, TextureDesc::Unmipped };
			data.desc = TextureDesc::Unmipped;
			return static_cast<bool>(data.texture);
		};

	return ptr_texture_asset_data;
}

//上下左右にextend_length分だけ拡張
Image AssetManager::tileMapExtend(Image old_image)
{
	int32 old_tile_width = GraphicSetting::getNormalTileWidth();
	int32 old_tile_height = GraphicSetting::getNormalTileHeight();
	int32 extend_length = GraphicSetting::getExtendedLength();

	if (not (old_image.width() % old_tile_width == 0)) throw Error(U"not divisible");
	if (not (old_image.height() % old_tile_height == 0)) throw Error(U"not divisible");
	Point g_size{ old_image.width() / old_tile_width , old_image.height() / old_tile_height };

	int32 new_tile_width = old_tile_width + extend_length * 2;
	int32 new_tile_height = old_tile_height + extend_length * 2;

	size_t new_image_width = new_tile_width * g_size.x;
	size_t new_image_height = new_tile_height * g_size.y;
	Image new_image{ new_image_width, new_image_height, Palette::Deeppink };

	//Image test_image{ 32, 32, Palette::Blue };

	for (int32 gy = 0; gy < g_size.y; gy++)
	{
		for (int32 gx = 0; gx < g_size.x; gx++)
		{
			Point old_left_top_pos{ gx * old_tile_width, gy * old_tile_height };
			Image old_clipped_image = old_image.clipped(old_left_top_pos, old_tile_width, old_tile_height);

			Point new_outer_left_top_pos{ gx * new_tile_width, gy * new_tile_height };
			Point new_inner_left_top_pos = new_outer_left_top_pos + Point{ extend_length, extend_length };

			Color old_left_top_color = old_image[old_left_top_pos.y][old_left_top_pos.x];
			Image planeImage{ new_image_width, new_image_height, old_left_top_color };

			planeImage.overwrite(new_image, new_outer_left_top_pos);
			old_clipped_image.overwrite(new_image, new_inner_left_top_pos);
		}
	}
	return new_image;
}

void AssetManager::registerTileFromTileMap(const Image& extended_image)
{
	int32 extended_tile_width = GraphicSetting::getExtendedTileWidth();
	int32 extended_tile_height = GraphicSetting::getExtendedTileHeight();
	if (not (extended_image.width() % extended_tile_width == 0)) throw Error(U"not divisible");
	if (not (extended_image.height() % extended_tile_height == 0)) throw Error(U"not divisible");
	Point g_size{ extended_image.width() / extended_tile_width , extended_image.height() / extended_tile_height };

	for (int32 gy = 0; gy < g_size.y; gy++)
	{
		for (int32 gx = 0; gx < g_size.x; gx++)
		{
			Point left_top_pos{ gx * extended_tile_width, gy * extended_tile_height };
			Image tileImage = extended_image.clipped(
				left_top_pos,
				extended_tile_width,
				extended_tile_height);
			AssetName tileAssetName = tilemapX_Y(gx, gy);
			TextureAsset::Register(tileAssetName, image2TextureAssetData(tileImage));
			tileImage.save(U"resources/output/" + tileAssetName + U".png");
		}
	}
}
