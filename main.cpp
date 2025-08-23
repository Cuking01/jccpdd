
#include "CuSDK/basis.h"
#include "tool.h"

std::map<std::string,int> jiban_s2i,yizi_s2i;
std::map<int,std::string> jiban_i2s,yizi_i2s;

bool pruning_大宗师;
int 大宗师_id;

#include "jiban.h"
#include "yizi.h"

std::vector<JiBan> jibans;
std::vector<Yizi> yizis;


#include "config.h"
#include "zhenrong.h"
#include "search.h"

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
	search_zhenrong(query_config.n,query_config.wasted_limit,"zhenrong.txt");
}
catch(std::exception&e)
{
	puts("error!");
	File error_log("error_log.txt","a");
	fprintf(error_log,"%s\n",e.what());
}
