struct structProtocol
{
	char DataHead[6];         //����ͷ��Ĭ��ΪDaHeng
	unsigned char DataCommand;    //���0x01 Ϊ����ͼƬ��0x02Ϊ����ͼƬ
	int Length;                   //�����ݳ���
	int TotalPack;                //�����ܰ���
	int CurrentPack;              //��ǰ��
	unsigned char *Data;          //����
};

