#include "record.h"
int insertRecord(QString user,QString DBname,QString TBname,vector<map<QString,QString>> records)//�����¼
{
    return 1;
}

int updateRecord(QString user,QString DBname,QString TBname,vector<map<QString,QString>> colnames)//���¼�¼
{
    return 1;
}

int selectRecord(QString user,QString DBname,vector<QString> TBnames,vector<QString> colname,vector<int> rdno)//��ѯ��¼���������Ϊ�����ͼ�¼�����
{
    return 1;
}

int deleteRecord(QString user,QString DBname,QString TBname,int rdno)//ɾ����¼���������Ϊ��¼�����
{
    return 1;
}

vector<int> analyzeWhere(QString condition)//�������Ϊwhereɸѡ����������ֵΪ��¼��ŵļ���
{

}

vector<int> analyzeGroupby(QString condition)//�������Ϊgroupbyɸѡ����������ֵΪ��¼��ŵļ���
{

}
