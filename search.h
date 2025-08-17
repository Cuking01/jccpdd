
#pragma once

void dfs(ZhenRong zhenrong,int dep,int id_st,int n,int wasted_limit,File&file)
{
	if(zhenrong.wasted()-3*(n-dep)>wasted_limit)return;

	if(dep==n)
	{
		if(zhenrong.filter(n))
			zhenrong.print(file);
		return;	
	}

	for(int i=id_st;i<yizis.size();i++)
	{
		ZhenRong tmp=zhenrong;
		tmp.add_yizi(i);
		dfs(tmp,dep+1,i+1,n,wasted_limit,file);
	}
}

void search_zhenrong(int n,int wasted_limit,std::string_view path)
{
	File out(path,"w");
	ZhenRong zhenrong;
	ZhenRong::print_cnt=0;
	fputs("------------zhenrong------------\n\n",out);
	dfs(zhenrong,0,0,n,wasted_limit,out);
}
