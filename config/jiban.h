#pragma once

void read_config_jiban()
{
	File config(查询参数.jiban_config_file,"r");

	int n,cnt=0;
	fscanf(config,"%d",&n);

	while(n--)
	{
		char tmp[100];
		fscanf(config,"%s",tmp);
		std::string name=tmp;
		JiBan jiban;
		cu_assert(!jiban_s2i.contains(name),"jiban conflict");

		jiban_s2i[name]=cnt;
		jiban_i2s[cnt]=name;
		jiban.id=cnt++;

		if(name=="大宗师")
		{
			pruning_s15大宗师=true;
			s15大宗师_id=cnt-1;
		}


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
		羁绊配置.push_back(jiban);
	}
}
