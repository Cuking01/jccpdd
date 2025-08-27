#pragma once

struct 打分类
{
	ZhenRong 阵容;

	std::vector<int> 弈子;
	std::vector<u3> 纹章配置;

	std::vector<int> 最大得分纹章配置;
	double 最大得分=-1;

	bool 有羁绊(int 弈子id,int 羁绊id) const
	{
		return (弈子配置[弈子[弈子id]].羁绊|纹章配置[弈子id])>>羁绊id&1;
	}

	double 计算分数() const
	{
		return 0;
	}

	void 枚举纹章(int dep)
	{
		if(dep==纹章表.size())
		{
			double 分数=计算分数();
			return;
		}
		for(int i=0;i<弈子.size();i++)
		{
			if(!有羁绊(i,纹章表[dep]))
			{
				纹章配置[i]|=u3(1)<<纹章表[dep];
				枚举纹章(dep+1);
				纹章配置[i]^=u3(1)<<纹章表[dep];
			}
		}
	}

	void 枚举主C()
	{

	}

	void 枚举副C()
	{

	}

	void 枚举主T()
	{

	}

	void 枚举副T()
	{

	}

	double 打分()
	{

		return 0;
	}
};

double 打分(ZhenRong 阵容)
{
	打分类 打分工具(阵容);
	return 打分工具.打分();
}

