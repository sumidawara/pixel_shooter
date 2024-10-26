#pragma once

class Button
{
public:
	Button();
	void init(const RectF& rectf, const String& text, const AssetNameView& font_asset_name);
	void update(double delta_time);
	void draw() const;

	bool getIsClicked() const;
	bool getIsHovered() const;

	void setIsClicked(bool value);

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;

};
