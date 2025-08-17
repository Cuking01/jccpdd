#pragma once

struct JiBan
{
	int id;
	u3 levels=1;
	bool p_exactly_equal=false;

	int wasted(int level) const
	{
		if(p_exactly_equal)
		{
			if(levels>>level&1)
				return 0;
			return level;
		}
		int cnt=0;
		while((levels&u3(1)<<level)==0)
		{
			level--;
			cnt++;
		}
		return cnt;
	}

	std::string name() const
	{
		return jiban_i2s[id];
	}

	void add_sp(std::string sp)
	{
		if(sp=="exactly_equal")
			p_exactly_equal=true;
		else
			throw std::runtime_error("unknowk sp");
	}
};

