
#include "CuSDK/basis.h"
#include "tool.h"

std::map<std::string,int> jiban_s2i,yizi_s2i;
std::map<int,std::string> jiban_i2s,yizi_i2s;

bool pruning_s15大宗师;
int s15大宗师_id;

#include "jiban.h"
#include "yizi.h"

std::vector<JiBan> 羁绊配置;
std::vector<Yizi> 弈子配置;


#include "config.h"
#include "zhenrong.h"
#include "search.h"
#include "score.h"

void print(__uint128_t x)
{
	for(int i=0;i<128;i++)
	{
		putchar('0'+(x>>i&1));
	}
	puts("");
}

int main(int argc,char**argv) try
{
	read_config("./query_config.txt");
	print_config(File("out.txt","w"));
	search_zhenrong(查询参数.等级,查询参数.最大羁绊浪费,"zhenrong.txt");
}
catch(std::exception&e)
{
	puts("error!");
	File error_log("error_log.txt","a");
	fprintf(error_log,"%s\n",e.what());
}
