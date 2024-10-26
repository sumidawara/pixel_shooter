#pragma once
#include "Block.h"
#include "LayerJsonData.h"

class Layer
{
public:
	Layer();
	void init(const LayerJsonData& layer_json_data, LayerType layer_type);
	void update();
	void draw() const;

	std::shared_ptr<Grid<std::shared_ptr<Block>>> getBlockPtrList();

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};

