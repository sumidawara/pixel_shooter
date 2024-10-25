#pragma once
#include "ICollidable.h"
#include "CollisionAnalyzer.h"

class Debug
{
public:
	Debug(const Debug&) = delete;
	Debug& operator=(const Debug&) = delete;
	Debug(Debug&&) = delete;
	Debug& operator=(Debug&&) = delete;

	static Debug& getInstance();

    void init();
	void update(double time_delta);
	void draw() const;

	void writeline(int32 index, const String& content);
	void writeline(int32 index);

	int32 getDebugScreenIndex();

private:
    struct Impl;
    std::shared_ptr<Impl> p_impl;

	Debug();
	~Debug() = default;
};

