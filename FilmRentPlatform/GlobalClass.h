#pragma once

class GlobalClass
{
public:
	mysql::MySQL_Driver *driver;
	Connection *con;
	static GlobalClass *GetInstance();

private:
	GlobalClass();
	~GlobalClass();
	static GlobalClass *m_pInstance;
};

