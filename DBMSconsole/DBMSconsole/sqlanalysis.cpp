#include "sqlanalysis.h"
int sqlAnalysis(QString sql,vector<QString> &sqlkey)
{
    vector<QString> regVector;          //���������ʽ
    vector<int> regSize;                //��Ӧ��������ʽҪ��ȡ����ֵ����create��Ҫ��ȡdatabase��

    regVector.push_back(QString("create(?:\\s*)database(?:\\s*)(\\b[a-z0-9_]+\\b)(?:\\s*);"));      //ƥ�䴴�����ݿ������
    regSize.push_back(1);
    regVector.push_back(QString("rename(?:\\s*)database(?:\\s*)(\\b[a-z0-9_]+\\b)(?:\\s*)to(?:\\s*)(\\b[a-z0-9_]+\\b)(?:\\s*);"));     //ƥ�����������ݿ������
    regSize.push_back(2);
    regVector.push_back(QString("drop(?:\\s*)database(?:\\s*)(\\b[a-z0-9_]+\\b)(?:\\s*);"));        //ƥ��ɾ�����ݿ������
    regSize.push_back(1);
    regVector.push_back(QString("use(?:\\s*)database(?:\\s*)(\\b[a-z0-9_]+\\b)(?:\\s*);"));         //ƥ��ʹ�����ݿ������
    regSize.push_back(1);

    //��ʼ����sql���
    for (unsigned int i = 0; i < regVector.size(); i++)
    {
        QRegExp reg(regVector[i]);
        int pos = reg.indexIn(sql);       //ƥ��ĵ�һ���ַ���λ�ã���0��ʼ����Ϊ-1��ƥ��

        if (pos >= 0)                      //��ƥ��
        {
            for (int j = 0; j < regSize[i]; j++)
            {
                sqlkey.push_back(reg.cap(j + 1));   //����Ӧ��ֵ����sqlkey
            }
            return i;                    //�������ݿ������Ӧ�ı�ţ���0��ʼ
        }
    }

    return -1;                              //û�ж�Ӧ�Ĳ���������-1����ʾ�����Ͳ�����δ֧�֣�����sql������
}
