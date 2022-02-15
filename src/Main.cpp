#include "Spider.h"
#include <iostream>

int main(int argc, char* argv[])
{
    Spider spider("/home/shorty/Repos/spider/resources/Modules.xml");
    spider.Init();
    spider.Run();
    spider.Deinit();


    return 0;
}