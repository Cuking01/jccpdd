#pragma once

struct 打分类
{
	ZhenRong 阵容;

	std::vector<int> 弈子;
	std::vector<u3> 纹章配置;
	int 主C=-1,主T=-1,副C=-1,副T=-1;
	u2 定位标记=0;


	std::vector<u3> 最大得分纹章配置;
	int 最大得分主C,最大得分主T,最大得分副C,最大得分副T;
	double 最大得分=-1;

	bool 有羁绊(int 弈子id,int 羁绊id) const
	{
		return (弈子配置[弈子[弈子id]].羁绊|纹章配置[弈子id])>>羁绊id&1;
	}

	double 计算分数() const
	{
		int 装备[3];

		装备[坦]=6;
		装备[物]=3;
		装备[法]=3;

		auto 计算弈子分数=[&,this](int id)
		{
			const auto 弈子=this->弈子[id];
			const auto& 配置=弈子配置[弈子];

			

			auto 基本分=[&]()->double
			{
				return 100;
			};

			auto 弈子强度分=[&]()->double
			{
				return 1+0.01*配置.战力权重;
			};

			auto 装备适配分=[&]()->double
			{
				int 纹章数=Bits(纹章配置[id]).size();
				int&装备数=装备[配置.定位];
				int 携带装备数=std::min(装备数,3-纹章数);

				装备数-=携带装备数;

				static constexpr double 分数_主[]={1.0,1.6,2.4,3.4};
				static constexpr double 分数_副[]={1.0,1.5,2.1,2.8};
				
				if(is(id).one_of(主C,主T))return 分数_主[携带装备数];
				if(is(id).one_of(副C,副T))return 分数_副[携带装备数];
				return 1.0;
			};

			auto 羁绊分=[&]()->double
			{
				return 1;
			};

			auto 阶位等级适配分=[&]()->double
			{
				static constexpr double 阶位等级适配表[5][10]=
				{
					{0,0,0,1.2 ,1.1 ,1.0 ,0.7 ,0.65,0.6 ,0.2 },
					{0,0,0,0.8 ,1.0 ,1.1 ,0.95,0.8 ,0.67,0.4 },
					{0,0,0,0.5 ,0.65,0.8 ,1.1 ,1.0 ,0.9 ,0.7 },
					{0,0,0,0.4 ,0.5 ,0.6 ,0.75,1.1 ,1.2 ,1.1 },
					{0,0,0,0.3 ,0.3 ,0.3 ,0.4 ,0.7 ,1.1 ,1.4 }
				};

				return 阶位等级适配表[配置.阶位-1][等级-1];
			};

			return 基本分()*弈子强度分()*装备适配分()*羁绊分()*阶位等级适配分();
		};
		return 0;
	}

	void 更新()
	{
		double 分数=计算分数();
		if(分数>最大得分)
		{
			最大得分纹章配置=纹章配置;
			最大得分主C=主C;
			最大得分副C=副C;
			最大得分主T=主T;
			最大得分副T=副T;
			最大得分=分数;
		}
	}

	void 枚举纹章(int dep)
	{
		if(dep==纹章表.size())
		{
			更新();
			return;
		}
		for(int i=0;i<弈子.size();i++)
		{
			if(!有羁绊(i,纹章表[dep]))
			{
				if(Bits(纹章配置[i]).size()>=3)continue;
				纹章配置[i]|=u3(1)<<纹章表[dep];
				枚举纹章(dep+1);
				纹章配置[i]^=u3(1)<<纹章表[dep];
			}
		}
	}

	void 枚举主C()
	{
		for(int i=0;i<弈子.size();i++)
		{
			if(~定位标记>>i&1)
			{
				if(!is(弈子配置[弈子[i]].定位).one_of(物,法))
					continue;

				定位标记|=u2(1)<<i;
				主C=i;
				枚举副C();
				定位标记^=u2(1)<<i;
			}
		}
	}

	void 枚举副C()
	{
		for(int i=0;i<弈子.size();i++)
		{
			if(~定位标记>>i&1)
			{
				if(!is(弈子配置[弈子[i]].定位).one_of(物,法))
					continue;

				定位标记|=u2(1)<<i;
				副C=i;
				枚举主T();
				定位标记^=u2(1)<<i;
			}
		}
	}

	void 枚举主T()
	{
		for(int i=0;i<弈子.size();i++)
		{
			if(~定位标记>>i&1)
			{
				if(!is(弈子配置[弈子[i]].定位).one_of(坦))
					continue;

				定位标记|=u2(1)<<i;
				主T=i;
				枚举副T();
				定位标记^=u2(1)<<i;
			}
		}
	}

	void 枚举副T()
	{
		for(int i=0;i<弈子.size();i++)
		{
			if(~定位标记>>i&1)
			{
				if(!is(弈子配置[弈子[i]].定位).one_of(坦))
					continue;

				定位标记|=u2(1)<<i;
				副T=i;
				枚举纹章(0);
				定位标记^=u2(1)<<i;
			}
		}
	}

	void 打分()
	{
		枚举主C();
		return;
	}
};

double 打分(ZhenRong 阵容)
{
	打分类 打分工具(阵容);
	打分工具.打分();
	return 打分工具.最大得分;
}

