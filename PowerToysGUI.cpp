#include "pch.h"
#include "PowerToys.h"

void PowerToys::SetImGuiContext(uintptr_t ctx)
{
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

std::string PowerToys::GetPluginName()
{
	return "PowerToys!";
}

void PowerToys::RenderSettings() {

	// Enable plugin

	ImGui::TextUnformatted("A really cool plugin");

	CVarWrapper pluginenableCvar = cvarManager->getCvar("plugin_enabled");

	if (!pluginenableCvar) {
		return;
	}

	bool pluginenabled = pluginenableCvar.getBoolValue();

	if (ImGui::Checkbox("Enable plugin", &pluginenabled)) {
		pluginenableCvar.setValue(pluginenabled);
		if (pluginEnabled == true) {
			this->log("PowerToys plugin enabled");
		}
		else if (pluginEnabled == false) {
			this->log("PowerToys plugin disabled");
		}
	}
	if (ImGui::IsItemHovered()) {
		if (pluginEnabled == true) {
			ImGui::SetTooltip("Disable this plugin (don't click this) :/");
		}
		else if (pluginEnabled == false) {
			ImGui::SetTooltip("Enable this so cool plugin!");
		}
	}

	// Settings

	if (pluginEnabled == true) {

		ImGui::NewLine();

		ImGui::TextUnformatted("Settings");

		CVarWrapper losefreeplayenableCvar = cvarManager->getCvar("loseallways_enabled");

		if (!losefreeplayenableCvar) {
			return;
		}

		bool losefreeplayenabled = losefreeplayenableCvar.getBoolValue();

		if (ImGui::Checkbox("Enable load freeplay after lose", &losefreeplayenabled)) {
			losefreeplayenableCvar.setValue(losefreeplayenabled);
			this->log("Allways load Freeplay after lose Toogled");
		}
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("Toggle allways load Freeplay after lose");
		}

		//

		CVarWrapper winfreeplayenableCvar = cvarManager->getCvar("winallways_enabled");

		if (!winfreeplayenableCvar) {
			return;
		}

		bool winfreeplayenabled = winfreeplayenableCvar.getBoolValue();

		if (ImGui::Checkbox("Enable load freeplay after win", &winfreeplayenabled)) {
			winfreeplayenableCvar.setValue(winfreeplayenabled);
			this->log("Allways load Freeplay after win Toogled");
		}
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("Toggle allways load Freeplay after win");
		}

		//

		CVarWrapper queueenableCvar = cvarManager->getCvar("queue_enabled");

		if (!queueenableCvar) {
			return;
		}

		bool queueenabled = queueenableCvar.getBoolValue();

		if (ImGui::Checkbox("Enable instant queue after game", &queueenabled)) {
			queueenableCvar.setValue(queueenabled);
			this->log("Instant queue after game Toogled");
		}
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("Toggle instant queue after game");
		}

		// End settings



		ImGui::NewLine();
								
		ImGui::TextUnformatted("You can bind a button to the \"FAQ\" command (Freeplay_And_Queue).\nFor example, when you are in the main menu, you can binded button, \nand it will take you to freeplay and turn on the queue for the last played game.");

		ImGui::NewLine();

	}



	ImGui::Separator();

	ImGui::NewLine();

	ImGui::TextUnformatted("Plugin made by Skidam");

	ImGui::TextUnformatted("Version " stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH));

}
