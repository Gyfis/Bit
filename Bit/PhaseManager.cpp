#include "PhaseManager.h"

PhaseManager::PhaseManager(void) { }

PhaseManager::~PhaseManager(void) { }


//SelectLocationPhase PhaseManager::slp;


void PhaseManager::Initialize()
{

	// nacti stav hry ze souboru

	// nech nacist vsechny phases

	SelectLocationPhase::Initialize();

	SelectLocationPhase::SetActivated();

	// nastav aktivni phase

}