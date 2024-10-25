#pragma once
#include "Block.h"
#include "LayerJsonData.h"

class Layer
{
public:
	Layer();
	void init(LayerJsonData layer_json_data);
	void update();
	void draw() const;

	std::vector<std::shared_ptr<Block>>& getBlockPtrList();

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};

