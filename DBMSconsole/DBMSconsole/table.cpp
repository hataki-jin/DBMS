#include "table.h"
void showtables(QString user,QString DBname)//����Ļ�ϴ�ӡ��ǰ�û���ǰ���ݿ��µ����б���
{

}

int createTable(QString user,QString DBname,QString TBname,vector<Field> fields,vector<Constraint> constraints)//������
{
    return 1;
}

int dropTable(QString user,QString DBname,QString TBname)//ɾ����
{
    return 1;
}

int deleteField(QString user,QString DBname,QString TBname,QString col)//ɾ������һ��
{
    return 1;
}

int addField(QString user,QString DBname,QString TBname,Field col,Constraint constraint)//����һ�У�ֻ���������һ��Լ������
{
    return 1;
}

int modifyCol(QString user,QString DBname,QString oldname,QString newname,QString type,Constraint constraint)//�޸�һ�е����Ƽ����ͣ�ֻ���������һ��Լ������
{
    return 1;
}

int renameTable(QString user,QString DBname,QString oldname,QString newname)//��������
{
    return 1;
}

int removePri(QString user,QString DBname,QString TBname)//ɾ������
{
    return 1;
}

int addPri(QString user,QString DBname,QString TBname,Constraint primarykey)//Ϊһ�������������
{
    return 1;
}
