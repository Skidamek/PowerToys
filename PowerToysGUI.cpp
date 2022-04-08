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
			this->log("Plugin enabled");
		}
		else if (pluginEnabled == false) {
			this->log("Plugin disabled");
		}
	}
	if (ImGui::IsItemHovered()) {
		if (pluginEnabled == true) {
			ImGui::SetTooltip("Disable this plugin (don't click it) :/");
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
			this->log("Allways load Freeplay after LOSE Toogled");
		}
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("Toggle allways load Freeplay after LOSE");
		}

		// Koniec

		CVarWrapper winfreeplayenableCvar = cvarManager->getCvar("winallways_enabled");

		if (!winfreeplayenableCvar) {
			return;
		}

		bool winfreeplayenabled = winfreeplayenableCvar.getBoolValue();

		if (ImGui::Checkbox("Enable load freeplay after win", &winfreeplayenabled)) {
			winfreeplayenableCvar.setValue(winfreeplayenabled);
			this->log("Allways load Freeplay after WIN Toogled");
		}
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("Toggle allways load Freeplay after WIN");
		}

		// Koniec

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

		// Koniec Settingsow



		ImGui::NewLine();

		ImGui::TextUnformatted("Mozesz przybindowac jakis przycisk do komendy \"freeplay_and_queue\".\nWtedy kiedy bedziesz np. w menu glownym mozesz kliknac ten przycisk,\na on cie przeniesie na freeplay i wlaczy kolejke do ostatnio granej gry.");

		ImGui::NewLine();


	}



	ImGui::Separator();

	ImGui::NewLine();

	ImGui::TextUnformatted("Plugin made by Skidam");

	ImGui::TextUnformatted("Version " stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH));

}
