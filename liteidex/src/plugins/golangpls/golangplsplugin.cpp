#include "golangplsplugin.h"

GolangPlsPlugin::GolangPlsPlugin()
{
}

GolangPlsPlugin::~GolangPlsPlugin()
{
}

bool GolangPlsPlugin::load(LiteApi::IApplication* app)
{
	m_liteApp = app;
	m_golangPLS = new GolangPls(app);
	m_golangPLS->__start();
	return true;
}

QStringList GolangPlsPlugin::dependPluginList() const
{
	return QStringList() << "plugin/liteenv" << "plugin/golangast";
}