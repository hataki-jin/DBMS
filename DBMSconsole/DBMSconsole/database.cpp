#include "convert.h"
void showdatabases(QString user)//����Ļ�ϴ�ӡ��ǰ�û����������ݿ�
{

}

int createDBEntity(QString user,QString DBname)//�������ݿ�ʵ��
{

    return 1;
}

int renameDBEntity(QString user,QString newName,QString oldName)//���������ݿ�ʵ��
{

    return 1;
}

int dropDBEntity(QString user,QString DBname)//ɾ�����ݿ�ʵ��
{

    return 1;
}

int useDBEntity(QString user,QString DBname)//�򿪲�ʹ�����ݿ�
{

    return 1;
}

int initDBEntity(QString user,QString DBname)//��ʼ�����ݿ�
{
    if(dropDBEntity(user,DBname)!=1) return -1;//ɾ��ʧ��
    if(createDBEntity(user,DBname)!=1) return -2;//����ʧ��
    return 1;
}

int backupDBEntity(QString user,QString DBname)//�������ݿ�
{
    return 1;
}
