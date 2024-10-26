#pragma once
#include "Layer.h"

class World
{
public:
	World();
	void init(Vec2 pos, const String& file_path);
	void update(double delta_time);
	void draw() const;

	bool isBlockAtWorldPos(Vec2 worldPos);
	bool isBlockAtIndexPos(Point index_pos);
	Point worldPos2indexPos(Vec2 worldpos);

	Vec2 getPos() const;
	Point getSize() const;
	Layer getLayer(LayerType layer_type) const;

	//現状はterrain_object_layerのgetBlockGridを返すだけ
	std::shared_ptr<Grid<std::shared_ptr<Block>>> getCollidableBlockGrid() const;

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};
