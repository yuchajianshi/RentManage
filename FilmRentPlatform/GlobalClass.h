#pragma once

class GlobalClass
{
	class Collection        // 此类的作用是销毁m_pInstance，不然会有内存泄露
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

