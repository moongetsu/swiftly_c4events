#include <swiftly/swiftly.h>
#include <swiftly/server.h>
#include <swiftly/configuration.h>
#include <swiftly/timers.h>

Configuration *config = nullptr;
Server *server = nullptr;
PlayerManager *g_playerManager = nullptr;
Timers *timers = nullptr;

unsigned long long timerid; // credits to blu
int elapsedTime = 10; // credits to blu

void OnProgramLoad(const char *pluginName, const char *mainFilePath)
{
    Swiftly_Setup(pluginName, mainFilePath);
    g_playerManager = new PlayerManager();
    server = new Server();
    config = new Configuration();
    timers = new Timers();
}
 
void OnPluginStart()
{
}

void TimerCallback() { // credits to blu
    g_playerManager->SendMsg(HUD_PRINTCENTER, "Remaining time: %d seconds\n", elapsedTime);
    elapsedTime--;  // decrement elapsedTime.
    if (elapsedTime == 0) {
        timers->DestroyTimer(timerid);
    }
} //

void OnBombPlanted(Player *player, unsigned short site)
{
    g_playerManager->SendMsg(HUD_PRINTTALK, FetchTranslation("c4events.plant.message"), config->Fetch<const char*>("c4events.prefix"), player->GetName());
    elapsedTime = server->cvars->GetConvarInt("mp_c4timer");
    timerid = timers->RegisterTimer(1000, TimerCallback);  
}

void OnBombDefused(Player *player, unsigned short site)
{
    g_playerManager->SendMsg(HUD_PRINTTALK, FetchTranslation("c4events.defuse.message"), config->Fetch<const char*>("c4events.prefix"), player->GetName());
}

void Timer() // credits to blu
{
    print("There are %02d players on the server.\n", g_playerManager->GetPlayers());
}

const char *GetPluginName()
{
    return "C4 Events Messages";
}

void OnPluginStop()
{

}

const char *GetPluginAuthor()
{
    return "Moongetsu, blu";
}

const char *GetPluginVersion()
{
    return "1.0.0";
}

const char *GetPluginWebsite()
{
    return "https://discord.gg/ESKNDx2CNB";
}