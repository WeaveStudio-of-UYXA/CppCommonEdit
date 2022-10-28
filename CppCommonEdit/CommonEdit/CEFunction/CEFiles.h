#pragma once
#pragma once
#include <QtCore>

namespace CE {
	class CEFiles
	{
	public:
		//return size of the path
		static qint64 sizeOf(QString path)
		{
			QDir dir(path);
			qint64 size = 0;
			// dir.entryInfoList(QDir::Files)�����ļ���Ϣ
			foreach(QFileInfo fileInfo, dir.entryInfoList(QDir::Files)) {
				size += fileInfo.size();
			}
			// dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)����������Ŀ¼�������й���
			foreach(QString subDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) { 
				size += sizeOf(path + QDir::separator() + subDir); 
			}
				//��������Ŀ¼����ݹ����sizeOf����
				
			return size;
		}
	};
}