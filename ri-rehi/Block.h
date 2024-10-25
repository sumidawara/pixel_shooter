#pragma once
#include "ICollidable.h"

class Block : public ICollidable
{
public:
	Block();
	void init(RectF rectf, AssetName tile_asset_name, int32 id);
	void update();
	void draw() const;

	void onCollision(const ICollidable& other) override;
	std::variant<RectF, Circle> getBoundingShape() const override;
	ICollidableType getType() const override;

	int32 getId() const;

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};

