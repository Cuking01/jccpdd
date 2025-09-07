#pragma once


struct ZhenRong
{
	u4 弈子;
	u0 jiban_cnt[40];

	void add_yizi(int id)
	{
		if(弈子>>id&1)throw std::runtime_error("重复的弈子");

		弈子|=u4(1)<<id;

		for(int i: Bits(弈子配置[id].羁绊))
			jiban_cnt[i]++;
	}

	int jiban_num(int id) const
	{
		return std::min(jiban_cnt[id]+纹章[id],人口)+额外羁绊[id];
	}

	int wasted() const
	{
		int sum=0;
		for(int i=0;i<羁绊配置.size();i++)
			sum+=羁绊配置[i].wasted(jiban_num(i));
		return sum;
	}

	int wasted_pruning() const
	{
		int wasted_num=wasted();
		if(pruning_s15大宗师)
			wasted_num-=jiban_num(s15大宗师_id)>1;
		return wasted_num;
	}

	ZhenRong()
	{
		弈子=0;
		memset(jiban_cnt,0,sizeof jiban_cnt);
	}
	void print(int id,File&out) const
	{
		fprintf(out,"阵容%d:\n弈子: ",id);
		for(int i:Bits(弈子))
			fprintf(out,"%s ",弈子配置[i].name().c_str());
		fputs("\n",out);

		for(int i=0;i<羁绊配置.size();i++)
			if(jiban_num(i))
				fprintf(out,"%d%s ",jiban_num(i),羁绊配置[i].name().c_str());
		fputs("\n\n",out);
	}

	int num_of_level(int 阶位) const
	{
		int cnt=0;
		for(int i:Bits(弈子))
			cnt+=::弈子配置[i].阶位==阶位;
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


