#pragma once

class GlobalClass
{
	class Collection        // ���������������m_pInstance����Ȼ�����ڴ�й¶
	{
	public:
		~Collection();
	};
public:
	mysql::MySQL_Driver *driver;
	Connection *con;
	static GlobalClass *GetInstance();
	static Collection m_collect;

private:
	GlobalClass();
	~GlobalClass();
	static GlobalClass *m_pInstance;
};

