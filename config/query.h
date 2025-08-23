#pragma once

struct Query_Config
{
	std::string s="";    //赛季
	int n=-1;            //阵容人口数
	int wasted_limit=-1; //最多允许浪费的羁绊个数

	std::string data_path="./data"; //配置数据路径
	std::string output_file="./out.txt"; //搜索结果路径
	std::string yizi_config_file="";
	std::string jiban_config_file="";

	std::vector<std::string> 必选弈子;
	std::map<std::string,int> 弈子加权;
	std::vector<std::string> 不选弈子;
	std::map<std::string,int> 纹章;
	std::map<std::string,int> 额外羁绊;

	void add_海克斯(std::string name)
	{
		
	}

	void read(std::string_view query_path)
	{
		File file(query_path,"r");
		Config_Reader reader(file);

		std::string name=reader.read_string();

		while(name!="")
		{
			if(name=="赛季")
			{
				s=reader.read_string();
			}
			else if(name=="人口")
			{
				n=reader.read_int();
			}
			else if(name=="最大羁绊浪费")
			{
				wasted_limit=reader.read_int();
			}
			else if(name=="数据路径")
			{
				data_path=reader.read_string();
			}
			else if(name=="输出文件")
			{
				output_file=reader.read_string();
			}
			else if(name=="必选弈子")
			{
				必选弈子.push_back(reader.read_string());
			}
			else if(name=="不选弈子")
			{
				不选弈子.push_back(reader.read_string());
			}
			else if(name=="弈子加权")
			{
				auto name=reader.read_string();
				int w=reader.read_int();
				弈子加权.emplace(name,w);
			}
			else if(name=="纹章")
			{
				纹章[reader.read_string()]++;
			}
			else if(name=="额外羁绊")
			{
				额外羁绊[reader.read_string()]++;
			}
			else if(name=="海克斯")
			{
				add_海克斯(reader.read_string());
			}
			else
			{
				cu_error("未知配置项：{}",name);
			}

			name=reader.read_string();
		}
	}

	//检查必填项
	void check_required()
	{
		cu_assert(s!="","\"赛季\" 必须配置");
		cu_assert(n!=-1,"\"人口\" 必须配置");
		cu_assert(wasted_limit!=-1,"\"最大羁绊浪费\" 必须配置");
	}

	//设置一些依赖别的选项的默认值
	void set_default_config()
	{
		if(jiban_config_file=="")
			jiban_config_file=data_path+"/"+s+"_jiban.txt";
		if(yizi_config_file=="")
			yizi_config_file=data_path+"/"+s+"_yizi.txt";
	}
};

Query_Config query_config;

void read_config_query(std::string_view path)
{
	query_config.read(path);
	query_config.check_required();
	query_config.set_default_config();
}
