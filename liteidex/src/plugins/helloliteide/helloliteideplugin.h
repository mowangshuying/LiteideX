#ifndef HELLOLITEIDEPLUGIN_H
#define HELLOLITEIDEPLUGIN_H

#include "helloliteide_global.h"
#include "liteapi/liteapi.h"

class HelloLiteIDEPlugin : public LiteApi::IPlugin
{
	Q_OBJECT
public:
	HelloLiteIDEPlugin();
	
	virtual bool load(LiteApi::IApplication* app);
protected:
	LiteApi::IApplication* m_liteApp;
};

class PluginFactory : public LiteApi::PluginFactoryT<HelloLiteIDEPlugin>
{
	Q_OBJECT
	Q_INTERFACES(LiteApi::IPluginFactory)
	Q_PLUGIN_METADATA(IID "liteidex.HelloLiteIDEPlugin")
public:
	PluginFactory() {
		m_info->setId("plugin/HelloLiteIDE");
		m_info->setVer("X38.4");
		m_info->setName("HelloLiteIDE");
		m_info->setAuthor("mowangshuying");
		m_info->setInfo("simple plugin test");
	}
};
#endif // HELLOLITEIDEPLUGIN_H