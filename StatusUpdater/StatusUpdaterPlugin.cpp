#include "StatusUpdaterPlugin.h"
#include <cstring>

StatusUpdaterPlugin::StatusUpdaterPlugin() : EuroScopePlugIn::CPlugIn(
	EuroScopePlugIn::COMPATIBILITY_CODE,
	"Status Updater",
	"1.0",
	"Bence Takacs",
	"N/A")
{

}

StatusUpdaterPlugin::~StatusUpdaterPlugin()
{
	
}

const char** tags = new const char* [4]{ "ST-UP", "PUSH", "TAXI", "DEPA" };

void StatusUpdaterPlugin::Update()
{
	int num = 0;
	EuroScopePlugIn::CFlightPlan fp = FlightPlanSelectFirst();

	// Loop through every flight plan
	while (fp.IsValid())
	{
		// Check if the ground state is in the tags array
		for (int i = 0; i < 4; i++)
		{
			// It is
			if (strcmp(fp.GetGroundState(), tags[i]) == 0)
			{
				// Update it
				fp.GetControllerAssignedData().SetScratchPadString(tags[i]);
				num++;
				break;
			}
		}

		// Clearance flag
		if (fp.GetClearenceFlag())
		{
			fp.GetControllerAssignedData().SetScratchPadString("CLEA");
		}
		
		fp = FlightPlanSelectNext(fp);
	}
}

bool StatusUpdaterPlugin::OnCompileCommand(const char* cmd)
{
	if (strcmp(cmd, ".updatetags") == 0)
	{
		Update();
		return true;
	}
	return false;
}

#if 0
void StatusUpdaterPlugin::PluginMessage(const char* message)
{
	DisplayUserMessage("StatusUpdaterPlugin", "", message, true, true, false, false, false);
}
#endif

void __declspec(dllexport) EuroScopePlugInInit(EuroScopePlugIn::CPlugIn** plugin)
{
	*plugin = new StatusUpdaterPlugin();
}

void __declspec(dllexport) EuroScopePlugInExit()
{

}