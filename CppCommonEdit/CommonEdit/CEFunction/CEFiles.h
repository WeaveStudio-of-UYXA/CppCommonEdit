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
			// dir.entryInfoList(QDir::Files)返回文件信息
			foreach(QFileInfo fileInfo, dir.entryInfoList(QDir::Files)) {
				size += fileInfo.size();
			}
			// dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)返回所有子目录，并进行过滤
			foreach(QString subDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) { 
				size += sizeOf(path + QDir::separator() + subDir); 
			}
				//若存在子目录，则递归调用sizeOf函数
				
			return size;
		}
	};
}