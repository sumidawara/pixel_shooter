#pragma once
#include "Layer.h"

class World
{
public:
	World();
	void init(Vec2 pos, const String& file_path);
	void update(double delta_time);
	void draw() const;

	Point worldPos2indexPos(Vec2 worldpos);

	Vec2 getPos() const;
	Point getSize() const;
	Layer getLayer(LayerType layer_type) const;



private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};
