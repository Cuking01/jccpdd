#pragma once

struct Config_Reader
{
	File&file;

	std::string read_string()
	{
		char tmp[100];
		tmp[0]=0;
		fscanf(file,"%99s",tmp);

		cu_assert(strlen(tmp)<99,"name to long");

		return std::string(tmp);
	}

	int read_int()
	{
		int x;
		int ret=fscanf(file,"%d",&x);
		cu_assert(ret==1,"读取失败！");
		return x;
	}


};

#include "config/query.h"
#include "config/jiban.h"
#include "config/yizi.h"

void read_config(std::string_view query_path)
{
	read_config_query(query_path);
	read_config_jiban();
	read_config_yizi();
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

