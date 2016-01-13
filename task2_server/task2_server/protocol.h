struct structProtocol
{
	char DataHead[6];         //数据头，默认为DaHeng
	unsigned char DataCommand;    //命令，0x01 为发送图片，0x02为接收图片
	int Length;                   //包数据长度
	int TotalPack;                //数据总包数
	int CurrentPack;              //当前包
	unsigned char *Data;          //数据
};

