#pragma once

struct Query_Config
{
	std::string s="";    //赛季
	int 赛季;
	int 等级=-1;          
	int 额外人口数=0;
	int 人口;
	int 最大羁绊浪费=-1; //最多允许浪费的羁绊个数

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
				cu_assert(s.size()>=3&&s[0]=='s',"赛季格式错误");
				赛季=0;
				for(int i=1;is(s[i]).in('0','9');i++)
					赛季=赛季*10+s[i]-'0';
				cu_assert(is(赛季).in(1,15),"赛季错误");
			}
			else if(name=="等级")
			{
				等级=reader.read_int();
			}
			else if(name=="最大羁绊浪费")
			{
				最大羁绊浪费=reader.read_int();
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
			else if(name=="冠冕")
			{
				额外人口数++;
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
		cu_assert(等级!=-1,"\"等级\" 必须配置");
		cu_assert(最大羁绊浪费!=-1,"\"最大羁绊浪费\" 必须配置");
	}

	//设置一些依赖别的选项的默认值
	void set_default_config()
	{
		if(jiban_config_file=="")
			jiban_config_file=data_path+"/"+s+"_jiban.txt";
		if(yizi_config_file=="")
			yizi_config_file=data_path+"/"+s+"_yizi.txt";
		人口=等级+额外人口数;
	}
};

Query_Config 查询参数;

void read_config_query(std::string_view path)
{
	查询参数.read(path);
	查询参数.check_required();
	查询参数.set_default_config();
}
