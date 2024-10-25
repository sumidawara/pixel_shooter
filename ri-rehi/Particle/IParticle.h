#pragma once
class IParticle
{
public:
	virtual ~IParticle() = default;

	/// @brief エフェクトの更新と描画を記述します。
	/// @param delta_time デルタタイム
	/// @param accumulated_time エフェクトの発生からの時間
	/// @return エフェクトを継続する場合は true を、破棄する場合は false を返します。
	virtual bool update(double delta_time, double accumulated_time) = 0;
	virtual void draw() const = 0;
	virtual double getAccumulatedTime() const = 0;
};

