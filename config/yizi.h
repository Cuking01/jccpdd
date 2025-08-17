#pragma once

void read_config_yizi()
{
	File config(query_config.yizi_config_file,"r");

	int n,cnt=0;
	fscanf(config,"%d",&n);

	while(n--)
	{
		char tmp[100];
		fscanf(config,"%s",tmp);
		std::string name=tmp;
		Yizi yizi;
		cu_assert(!yizi_s2i.contains(name),"yizi conflict");

		yizi_s2i[name]=cnt;
		yizi_i2s[cnt]=name;
		yizi.id=cnt++;

		fscanf(config,"%d",&yizi.level);

		int n_sp,n_jiban;

		fscanf(config,"%d",&n_jiban);

		for(int i=0;i<n_jiban;i++)
		{
			fscanf(config,"%s",tmp);

			cu_assert(jiban_s2i.contains(tmp),"{} jiban {} undefined",name,tmp);

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

