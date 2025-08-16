
#include"CuSDK/basis.h"

std::map<std::string,int> jiban_s2i,yizi_s2i;
std::map<int,std::string> jiban_i2s,yizi_i2s;

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


std::vector<JiBan> jibans;
std::vector<Yizi> yizis;


void read_config_jiban(const char*s)
{
	File config(std::string("data/s")+s+"_jiban.txt","r");

	int n,cnt=0;
	fscanf(config,"%d",&n);
	printf("%d\n",n);
	while(n--)
	{
		char tmp[100];
		fscanf(config,"%s",tmp);
		std::string name=tmp;
		JiBan jiban;
		if(jiban_s2i.contains(name))throw std::runtime_error("jiban conflict");

		jiban_s2i[name]=cnt;
		jiban_i2s[cnt]=name;
		jiban.id=cnt++;

		int n_sp,n_levels;

		fscanf(config,"%d",&n_levels);

		for(int i=0;i<n_levels;i++)
		{
			int level;
			fscanf(config,"%d",&level);
			jiban.levels|=u3(1)<<level;
		}

		fscanf(config,"%d",&n_sp);

		for(int i=0;i<n_sp;i++)
		{
			fscanf(config,"%s",tmp);
			jiban.add_sp(tmp);
		}
		jibans.push_back(jiban);
	}
}

void read_config_yizi(const char*s)
{
	File config(std::string("data/s")+s+"_yizi.txt","r");

	int n,cnt=0;
	fscanf(config,"%d",&n);

	while(n--)
	{
		char tmp[100];
		fscanf(config,"%s",tmp);
		std::string name=tmp;
		Yizi yizi;
		if(yizi_s2i.contains(name))throw std::runtime_error("yizi conflict");

		yizi_s2i[name]=cnt;
		yizi_i2s[cnt]=name;
		yizi.id=cnt++;

		fscanf(config,"%d",&yizi.level);

		int n_sp,n_jiban;

		fscanf(config,"%d",&n_jiban);

		for(int i=0;i<n_jiban;i++)
		{
			fscanf(config,"%s",tmp);

			if(!jiban_s2i.contains(tmp))throw std::runtime_error(std::format("{} jiban {} undefined",name,tmp));

			int jiban=jiban_s2i[tmp];
			yizi.jibans|=u3(1)<<jiban;
		}

		fscanf(config,"%d",&n_sp);

		for(int i=0;i<n_sp;i++)
		{
			fscanf(config,"%s",tmp);
			yizi.add_sp(tmp);
		}

		yizis.push_back(yizi);
	}
}

void read_config(const char*s)
{
	read_config_jiban(s);
	read_config_yizi(s);
}



void print_config(File& file)
{
	fputs("-------------jiban-------------\n\n",file);
	for(auto& jiban:jibans)
	{
		fprintf(file,"name: %s\n",jiban.name().c_str());
		fprintf(file,"levels: ");
		for(int i=0;i<20;i++)
			if(jiban.levels>>i&1)
				fprintf(file,"%d ",i);
		fprintf(file,"\n");

		if(jiban.p_exactly_equal)
			fprintf(file,"exactly_equal\n");
		fputs("",file);
	}

	fputs("-------------yizi-------------\n\n",file);
	for(auto& yizi:yizis)
	{
		fprintf(file,"name: %s\n",yizi.name().c_str());
		fprintf(file,"jibans: ");
		for(int i=0;i<60;i++)
			if(yizi.jibans>>i&1)
				fprintf(file,"%s ",jibans[i].name().c_str());
		fprintf(file,"\n");

		fputs("",file);
	}

}

void print_config(File&&file)
{
	print_config(file);
}


struct ZhenRong
{
	u4 yizis;
	u2 jiban_cnt[40];

	void add_yizi(int id)
	{
		if(yizis>>id&1)throw std::runtime_error("重复的弈子");

		yizis|=u4(1)<<id;

		for(int i=0;i<jibans.size();i++)
			if(::yizis[id].jibans>>i&1)
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
		for(int i=0;i<::yizis.size();i++)
			if(yizis>>i&1)
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
		for(int i=0;i<::yizis.size();i++)
			if(yizis>>i&1)
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


int main(int argc,char**argv) try
{
	read_config("15.1.2");
	print_config(File("out.txt","w"));
	search_zhenrong(8,0,"zhenrong.txt");
}
catch(std::exception&e)
{
	puts("error!");
	File error_log("error_log.txt","a");
	fprintf(error_log,"%s\n",e.what());
}
