#include "stdafx.h"
#include "GlobalClass.h"

GlobalClass::Collection::~Collection()
{
	if (GlobalClass::m_pInstance)
	{
		delete GlobalClass::m_pInstance;
	}
}

GlobalClass::GlobalClass()
{
	driver = nullptr;
	con = nullptr;
	driver = mysql::get_mysql_driver_instance();
	con = driver->connect(_T("tcp://127.0.0.1:3306"), _T("root"), _T("123456"));
	if (con != nullptr)
	{
		Statement *stmt = nullptr;
		stmt = con->createStatement();
		stmt->execute(_T("USE sakila"));
		delete stmt;
	}
}

GlobalClass::~GlobalClass()
{
	if (con != nullptr)
	{
		delete con;
	}
}

GlobalClass *GlobalClass::m_pInstance = nullptr;
GlobalClass::Collection GlobalClass::m_collect;

GlobalClass *GlobalClass::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new GlobalClass();
	}
	return m_pInstance;
}