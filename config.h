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

int 纹章[100];
int 额外羁绊[100];
u4 必选弈子;
u4 不选弈子;
int n;

#include "config/query.h"
#include "config/jiban.h"
#include "config/yizi.h"

void after_read()
{
	for(const auto&[羁绊,num]:query_config.纹章)
	{
		if(!jiban_s2i.contains(羁绊))
			cu_error("不存在的羁绊{}",羁绊);
		纹章[jiban_s2i[羁绊]]+=num;
	}

	for(const auto&[羁绊,num]:query_config.额外羁绊)
	{
		if(!jiban_s2i.contains(羁绊))
			cu_error("不存在的羁绊{}",羁绊);
		额外羁绊[jiban_s2i[羁绊]]+=num;
	}

	n=query_config.n;

	for(auto 弈子:query_config.必选弈子)
	{
		if(!yizi_s2i.contains(弈子))
			cu_error("不存在的弈子{}",弈子);
		必选弈子|=u4(1)<<yizi_s2i[弈子];
	}

	for(auto 弈子:query_config.不选弈子)
	{
		if(!yizi_s2i.contains(弈子))
			cu_error("不存在的弈子{}",弈子);
		不选弈子|=u4(1)<<yizi_s2i[弈子];
	}


	if(必选弈子&不选弈子)
	{
		std::string 冲突弈子;
		for(auto id:Bits(必选弈子&不选弈子))
			冲突弈子+=yizi_i2s[id]+" ";
		cu_error("不选和必选设置冲突: {}",冲突弈子);
	}
}

void read_config(std::string_view query_path)
{
	read_config_query(query_path);
	read_config_jiban();
	read_config_yizi();

	after_read();
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

