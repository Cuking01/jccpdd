#pragma once


struct ZhenRong
{
	u4 yizis;
	u0 jiban_cnt[40];

	void add_yizi(int id)
	{
		if(yizis>>id&1)throw std::runtime_error("重复的弈子");

		yizis|=u4(1)<<id;

		for(int i: Bits(::yizis[id].jibans))
			jiban_cnt[i]++;
	}

	int wasted() const
	{
		int sum=0;
		for(int i=0;i<jibans.size();i++)
			sum+=jibans[i].wasted(jiban_cnt[i]);
		return sum;
	}

	static inline int print_cnt;

	ZhenRong()
	{
		yizis=0;
		memset(jiban_cnt,0,sizeof jiban_cnt);
	}
	void print(File&out) const
	{
		fprintf(out,"阵容%d:\n弈子: ",++print_cnt);
		for(int i:Bits(yizis))
			fprintf(out,"%s ",::yizis[i].name().c_str());
		fputs("\n",out);

		for(int i=0;i<::jibans.size();i++)
			if(jiban_cnt[i])
				fprintf(out,"%d%s ",jiban_cnt[i],jibans[i].name().c_str());
		fputs("\n\n",out);
	}

	int num_of_level(int level) const
	{
		int cnt=0;
		for(int i:Bits(yizis))
			cnt+=::yizis[i].level==level;
		return cnt;
	}

	bool filter(int n) const
	{
		if(n==8)
		{
			if(num_of_level(5)>1)return false;
			if(num_of_level(4)<1)return false;
		}
		return true;
	}
};


