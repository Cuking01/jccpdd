#pragma once

static constexpr int 坦=0;
static constexpr int 物=1;
static constexpr int 法=2;

struct Yizi
{
	int id;
	int level;
	u3 羁绊=0;

	int 定位;
	int 战力权重;
	int 团队权重;

	std::string name() const
	{
		return yizi_i2s[id];
	}

	void add_sp(std::string sp)
	{
		throw std::runtime_error("unknowk sp");
	}
};

