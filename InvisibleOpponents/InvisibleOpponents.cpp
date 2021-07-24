#include "pch.h"
#include "InvisibleOpponents.h"


BAKKESMOD_PLUGIN(InvisibleOpponents, "Invisible Opponents", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

bool blueInvisible = false;
bool orangeInvisible = false;
bool opposingInvisible = false;

void InvisibleOpponents::onLoad()
{
	_globalCvarManager = cvarManager;
	

	cvarManager->registerCvar("invisible_opponents_enabled", "0", "Enable the invisible opponents plugin", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string, CVarWrapper cvar) {
		if (cvar.getBoolValue()) {
			hookEvents();
		}
		else {
			unhookEvents();
		}
			});

	cvarManager->registerCvar("invisible_opponents_enable_opponents", "0", "Makes opposing team invisible", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string, CVarWrapper cvar) {
			opposingInvisible = cvar.getBoolValue();
			});

	cvarManager->registerCvar("invisible_opponents_enable_blue", "0", "Makes blue team invisible", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string, CVarWrapper cvar) {
			blueInvisible = cvar.getBoolValue();
			});

	cvarManager->registerCvar("invisible_opponents_enable_orange", "0", "Makes orange team invisible", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string, CVarWrapper cvar) {
			orangeInvisible = cvar.getBoolValue();
			});
}

void InvisibleOpponents::onUnload()
{
}

// hooks events to allow the plugin to work
void InvisibleOpponents::hookEvents() {
	gameWrapper->HookEventPost("Function TAGame.Car_TA.SetVehicleInput",
		[this](...) { onTick(); });
}

// hooks events to allow the plugin to work
void InvisibleOpponents::unhookEvents() {
	gameWrapper->UnhookEventPost("Function TAGame.Car_TA.SetVehicleInput");
}

ServerWrapper InvisibleOpponents::getSW() {
	if (gameWrapper->IsInOnlineGame()) {
		auto server = gameWrapper->GetOnlineGame();

		if (server.IsNull()) {
			cvarManager->log("null server");
			return NULL;
		}

		auto playlist = server.GetPlaylist();

		if (!playlist) {
			return NULL;
		}

		// playlist 24 is a LAN match for a client
		if (playlist.GetPlaylistId() != 24) {
			return NULL;
		}

		return server;
	} else if (gameWrapper->IsInGame()) {
		auto server = gameWrapper->GetGameEventAsServer();

		if (server.IsNull()) {
			cvarManager->log("null server");
			return NULL;
		}

		return server;
	}
	//cvarManager->log("no server");
	return NULL;
}

void InvisibleOpponents::onTick() {
	auto sw = getSW();

	if (sw.IsNull()) return;

	auto cars = sw.GetCars();

	if (cars.IsNull()) return;

	PlayerControllerWrapper playerControl = gameWrapper->GetPlayerController();

	if (!playerControl) return;

	unsigned char teamNum = playerControl.GetTeamNum2();

	for (CarWrapper car : cars) {
		if (!car) {
			continue;
		}

		cvarManager->log("Usr Team = " + std::to_string(teamNum));
		cvarManager->log("Car Team = " + std::to_string(car.GetTeamNum2()));

		PriWrapper pri = car.GetPRI();
		if (pri) {
			cvarManager->log("Car Num  = " + std::to_string(car.GetPRI().GetSpectatorShortcut()));
		}

		if (teamNum != 0 && teamNum != 1) {
			if (car.GetTeamNum2() == 0) {
				if (blueInvisible) {
					car.SetHidden2(1);
				} else {
					car.SetHidden2(0);
				}
			}
			if (car.GetTeamNum2() == 1) {
				if (orangeInvisible) {
					car.SetHidden2(1);
				}
				else {
					car.SetHidden2(0);
				}
			}
			continue;
		}

		if (car.GetTeamNum2() != teamNum) {
			if (opposingInvisible) {
				car.SetHidden2(1);
			} else {
				car.SetHidden2(0);
			}
		} else {
			car.SetHidden2(0);
		}
	}

}