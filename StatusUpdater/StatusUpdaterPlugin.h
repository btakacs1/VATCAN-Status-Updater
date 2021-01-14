#pragma once
#include <Windows.h>
#include <EuroScopePlugIn.h>

class StatusUpdaterPlugin : public EuroScopePlugIn::CPlugIn
{
public:
	StatusUpdaterPlugin();
	virtual ~StatusUpdaterPlugin();

	void Update();
	bool OnCompileCommand(const char* cmd);
#if 0
	void PluginMessage(const char* message);
#endif
};