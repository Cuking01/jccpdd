#pragma once

struct Yizi
{
	int id;
	int level;
	u3 jibans=0;

	std::string name() const
	{
		return yizi_i2s[id];
	}

	void add_sp(std::string sp)
	{
		throw std::runtime_error("unknowk sp");
	}
};

