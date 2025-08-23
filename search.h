
#pragma once

struct Dfs
{

	std::vector<ZhenRong> result;
	int wasted_limit;
	u4 yizi_mask;



	void dfs(ZhenRong&zhenrong,int dep,int m)
	{
		if(zhenrong.wasted_pruning()-3*(n-m)>wasted_limit)return;

		if(m==n)
		{
			if(zhenrong.filter(n)&&zhenrong.wasted()<=wasted_limit)
				result.push_back(zhenrong);
			return;	
		}

		if(dep==yizis.size())return;

		dfs(zhenrong,dep+1,m);

		if(yizi_mask>>dep&1)
			return;

		ZhenRong tmp=zhenrong;
		tmp.add_yizi(dep);
		dfs(tmp,dep+1,m+1);
	}
};



void search_zhenrong(int n,int wasted_limit,std::string_view path)
{
	Dfs dfs;
	dfs.wasted_limit=wasted_limit;
	dfs.yizi_mask=必选弈子|不选弈子;

	ZhenRong zhenrong;

	int m=0;
	for(auto id:Bits(必选弈子))
	{
		zhenrong.add_yizi(id);
		m++;
	}

	dfs.dfs(zhenrong,0,m);

	File file(path,"w");
	int 阵容id=0;
	for(auto&阵容:dfs.result)
	{
		阵容.print(++阵容id,file);
	}
}
