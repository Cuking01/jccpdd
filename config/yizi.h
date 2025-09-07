#pragma once

void read_config_yizi()
{
	File config(查询参数.yizi_config_file,"r");

	Config_Reader reader(config);

	int n,cnt=0;
	n=reader.read_int();

	auto 设置定位=[](std::string 定位) -> int
	{
		if(定位=="坦")return 坦;
		if(定位=="物")return 物;
		if(定位=="法")return 法;
		cu_error("错误的定位： {}",定位);
	};

	while(n--)
	{
		std::string name=reader.read_string();
		Yizi yizi;
		cu_assert(!yizi_s2i.contains(name),"yizi conflict");

		yizi_s2i[name]=cnt;
		yizi_i2s[cnt]=name;
		yizi.id=cnt++;

		yizi.阶位=reader.read_int();
		yizi.定位=设置定位(reader.read_string());
		yizi.战力权重=reader.read_int();
		yizi.团队权重=reader.read_int();

		int n_sp,n_jiban;

		n_jiban=reader.read_int();

		for(int i=0;i<n_jiban;i++)
		{
			std::string 羁绊=reader.read_string();

			cu_assert(jiban_s2i.contains(羁绊),"{} 羁绊 {} 未定义",name,羁绊);

			int jiban=jiban_s2i[羁绊];
			yizi.羁绊|=u3(1)<<jiban;
		}

		n_sp=reader.read_int();

		for(int i=0;i<n_sp;i++)
			yizi.add_sp(reader.read_string());

		弈子配置.push_back(yizi);
	}
}

