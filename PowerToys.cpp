#include "pch.h"
#include "PowerToys.h"

#define NEW_METHOD

BAKKESMOD_PLUGIN(PowerToys, "PowerToys.", plugin_version, PLUGINTYPE_FREEPLAY);

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void PowerToys::onLoad()
{
	_globalCvarManager = cvarManager;
	int teamNumber = -1;
	int pl = 0;
	freeplayAndQueue = true;
	winnerset = false; //winner set false
	this->LoadHooks();
	this->log("Hello!");

	cvarManager->registerCvar("plugin_enabled", "0", "Enable Cool Plugin!", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
		pluginEnabled = cvar.getBoolValue();
	});

	cvarManager->registerCvar("loseallways_enabled", "0", "Enable load freeplay after lose!", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
		losefreeplayEnabled = cvar.getBoolValue();
	});

	cvarManager->registerCvar("winallways_enabled", "0", "Enable load freeplay after win!", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
		winfreeplayEnabled = cvar.getBoolValue();
	});

	cvarManager->registerCvar("queue_enabled", "0", "Enable queue after game!", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
		queueEnabled = cvar.getBoolValue();
	});

	cvarManager->registerNotifier("freeplay_and_queue", [this](std::vector<std::string> args) {
		freeplay_and_queue();
	}, "", PERMISSION_ALL);
};

void PowerToys::LoadHooks()
{
	gameWrapper->HookEvent("Function GameEvent_TA.Countdown.BeginState", std::bind(&PowerToys::StartGame, this, std::placeholders::_1));
	gameWrapper->HookEvent("Function TAGame.GameEvent_Soccar_TA.OnMatchWinnerSet", std::bind(&PowerToys::EndGame, this, std::placeholders::_1));
	gameWrapper->HookEventPost("Function TAGame.OnlineGame_TA.OnMainMenuOpened", std::bind(&PowerToys::Reset, this, std::placeholders::_1));

};

void PowerToys::StartGame(std::string name)
{
	if (!gameWrapper->IsInOnlineGame() || gameWrapper->IsInReplay())
		return;

	ServerWrapper sw = gameWrapper->GetOnlineGame();

	if (!sw.IsNull() && sw.IsOnlineMultiplayer()) {
		CarWrapper me = gameWrapper->GetLocalCar();

		GameSettingPlaylistWrapper playlist = sw.GetPlaylist();
		int playlistID = playlist.GetPlaylistId();
		if (playlistID == 24 || playlistID == 19 || playlistID == 6) {
			pl = 1;
		}

		if (!me.IsNull()) {
			teamNumber = me.GetTeamNum2();
			freeplayAndQueue = false;
			if (teamNumber == 0)
				this->log("Gracz jest w druzynie niebieskiej!");
			else this->log("Gracz jest w druzynie pomaranczowej!");
		}
		else {
			teamNumber = -1;
			this->log("Numer druzyny jeszcze nie znaleziony!");
		}
	}
};

void PowerToys::EndGame(std::string name)
{
#ifdef NEW_METHOD
	if (pluginEnabled == true) {
		winnerset = true; // winner set
		if (teamNumber == -1) { // we couldn't find the team number, try one last time, though localcar seems to always be null at this point.
			CarWrapper me = gameWrapper->GetLocalCar();
			if (!me.IsNull())
				teamNumber = me.GetTeamNum2();
		}

		ServerWrapper sw = gameWrapper->GetOnlineGame();
		GameSettingPlaylistWrapper playlist = sw.GetPlaylist();
		int playlistID = playlist.GetPlaylistId();
		if (playlistID == 24 || playlistID == 19 || playlistID == 6) {
			pl = 1;
		}
		if (pl == 0) {
			if (!sw.IsNull()) {
				ArrayWrapper<TeamWrapper> teams = sw.GetTeams();
				if (teams.Count() == 2) {
					ArrayWrapper<PriWrapper> players0 = teams.Get(0).GetMembers();
					ArrayWrapper<PriWrapper> players1 = teams.Get(1).GetMembers();
					int score0 = teams.Get(0).GetScore();
					int score1 = teams.Get(1).GetScore();
					// sprawdzanie czy wygrales
					if ((score0 > score1 && teamNumber == 0) || (score1 > score0 && teamNumber == 1)) {
						// log win
						this->log("Wygrales!");
						winnerset = false; //winner set false
						if (winfreeplayEnabled == true) {
							if (playlistID != 22 && playlistID != 34) {
								cvarManager->executeCommand("load_freeplay");
								this->log("Masz wlaczone allways load freeplay after WIN!");
							}
						}
						if (queueEnabled == true) {
							cvarManager->executeCommand("queue");
						}
					}
					else {
						// log loss
						this->log("Przegrales!");
						winnerset = false; //winner set false
						if (losefreeplayEnabled == true) {
							cvarManager->executeCommand("load_freeplay");
							this->log("Masz wlaczone allways load freeplay after LOSE!");
						}
						if (queueEnabled == true) {
							if (playlistID != 22 && playlistID != 34) {
								cvarManager->executeCommand("queue");
							}
						}
					}
				}
			}
			else {
				this->log("Server is null?");
			}
#endif
			freeplayAndQueue = true;
			teamNumber = -1;
			pl = 0;
		}
	}
	else {
		this->log("Plugin jest wylaczony!");
	}
};

void PowerToys::Reset(std::string name)
{
	freeplayAndQueue = true;
	teamNumber = -1;
	pl = 0;
	winnerset = false; //winner set false
};

void PowerToys::freeplay_and_queue()
{
	if (pluginEnabled == true) {
		if (freeplayAndQueue == true && !gameWrapper->IsInFreeplay()) {
			cvarManager->executeCommand("load_freeplay");
			cvarManager->executeCommand("queue");
			freeplayAndQueue = false;
		}
		else if (!gameWrapper->IsInOnlineGame()) {
			cvarManager->executeCommand("queue");
		}
	}
	else {
		this->log("You are have disabled plugin \"PowerToys\".");
	}
};

void PowerToys::log(std::string msg)
{
	cvarManager->log(msg);
};

void PowerToys::onUnload()
{
	freeplayAndQueue = false;
	teamNumber = -1;
	pl = 0;
	winnerset = false; //winner set false

	gameWrapper->UnhookEvent("Function GameEvent_TA.Countdown.BeginState");
	gameWrapper->UnhookEvent("Function TAGame.GameEvent_Soccar_TA.OnMatchWinnerSet");
	gameWrapper->UnhookEvent("Function TAGame.OnlineGame_TA.OnMainMenuOpened");

	this->log("Bye!");
};