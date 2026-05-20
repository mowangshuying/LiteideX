#ifndef GOLANGPLS_PLUGIN_H
#define GOLANGPLS_PLUGIN_H

#include "golangpls_global.h"
#include "liteapi/liteapi.h"
#include <QtPlugin>
#include "golangpls.h"

class GolangPlsPlugin  : public LiteApi::IPlugin
{
	Q_OBJECT
public:
	GolangPlsPlugin();
	~GolangPlsPlugin();

	virtual bool load(LiteApi::IApplication* app);
	virtual QStringList dependPluginList() const;
protected:
	LiteApi::IApplication* m_liteApp;
	GolangPls* m_golangPLS;
	
};


class PluginFactory : public LiteApi::PluginFactoryT<GolangPlsPlugin>
{
	Q_OBJECT
	Q_INTERFACES(LiteApi::IPluginFactory)
	Q_PLUGIN_METADATA(IID "liteidex.GolangPlsPlugin")
public:
	PluginFactory() {
		m_info->setId("plugin/golangpls");
		m_info->setVer("X38.7");
		m_info->setName("GolangPls");
		m_info->setAuthor("mowangshuying");
		m_info->setInfo("Golang GoPls Support");
		m_info->appendDepend("plugin/golangast");
		m_info->appendDepend("plugin/liteenv");
	}
};

#endif

