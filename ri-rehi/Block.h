﻿#pragma once
#include "ICollidable.h"

class Block : public ICollidable
{
public:
	Block();
	void init(const RectF& rectf, const AssetName& tile_asset_name, int32 id, bool is_collidable);
	void update();
	void draw() const;

	void onCollision(const ICollidable& other) override;
	RectF getBoundingShape() const override;
	ICollidableType getType() const override;

	int32 getId() const;

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};

