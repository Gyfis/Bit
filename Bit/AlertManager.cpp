#include "AlertManager.h"


AlertManager::AlertManager(void) { AlertManager::isToBeDeleted = false; }


AlertManager::~AlertManager(void) {	

	AlertManager::isToBeDeleted = true; 

	for (map<size_t, AlertStruct>::iterator it = AlertManager::currentAlerts.begin(); it != AlertManager::currentAlerts.end(); ++it)
	{
		AlertStruct alert = it->second;

		if (AlertManager::IsThereAlert(ScreenManager::GetCharsAtRect(alert.position), alert)) ScreenManager::ReplaceCharsAtRect(alert.characterData, alert.position);

		delete alert.alert;
		alert.alert = NULL;

		AlertManager::numberOfAlerts--;

		if (AlertManager::numberOfAlerts == 0) break;
	}
}


	
// kdyz chci vytvotit nejaky alert, tak to delam tak, ze mam pozici, character (nebo char combo) na ktery ceka, a funkci ktera se ma volat, tz. Callback
//  takze si ulozim co je na tom rect., vytvorim novy alert na te pozici s tim characterem, a zapnu ho

// po stisknuti klavesy ho chci ale zrusit == na pozici, na ktere byl vratit znaky, ktere tam byly predtim, a znicit ho z pameti

// kdyz jich mam vic, tak si je musim nejak zapamatovat, ktery je ktery = treba mapka, jelikoz Reader mi vraci unikatni identifikatory, tak je to celkem fajn
// s tim ze, kdyz pridavam tu funkci jako callback, tak potom taky pridam callback s id toho mojeho shitu, ten se podiva na strukturu na pozici, ktera bude mit Rect, chars predtim a ukazatel na alert
// na pozici vrati data ktere tam byly predtim, a to co je na ukazateli (vcetne toho ukazatele) znici, at je pamet v klidu

// co s Readerem? chci mazat funkce, ktere si vola reader, hned? Protoze ty se nebudou pouzivat jen na alerty, takze bych asi nechal rozhrani Create/Remove


void AlertManager::CreateAndShowAlert(const int c, SMALL_RECT sr, WORD color, size_t waitingSpeed, function<void()> f)
{

	AlertStruct alert;

	SMALL_RECT srGet;
	srGet.Top = sr.Top;
	srGet.Left = sr.Left;
	srGet.Bottom = alertHeightC;
	srGet.Right = alertWidthC;

	alert.characterData = ScreenManager::GetCharsAtRect(srGet);
	alert.position = srGet;
	alert.alert = new Alert(c, srGet, color, waitingSpeed);

	// get some id

	size_t alertID = Reader::InsertPair(c, f, true);

	AlertManager::currentAlerts.insert(make_pair(alertID, alert));

	Reader::InsertPair(c, bind(&AlertManager::StopAlert, this, alertID, false, false), true);

}

void AlertManager::CreateAndShowComboAlert(const int c1, const int c2, SMALL_RECT sr, WORD color, size_t waitingSpeed, function<void()> f)
{
	
	AlertStruct alert;

	SMALL_RECT srGet;
	srGet.Top = sr.Top;
	srGet.Left = sr.Left;
	srGet.Bottom = alertHeightC;
	srGet.Right = alertWidthC;

	alert.characterData = ScreenManager::GetCharsAtRect(srGet);
	alert.position = srGet;
	alert.alert = new Alert(c1, c2, srGet, color, waitingSpeed);

	// get some id

	size_t alertID = Reader::InsertCombo(c1, c2, f, true);

	AlertManager::currentAlerts.insert(make_pair(alertID, alert));

	Reader::InsertCombo(c1, c2, bind(&AlertManager::StopAlert, this, alertID, false, false), true);

}


void AlertManager::CreateAndShowComboAlerts(const vector<int> c1, const vector<int> c2, SMALL_RECT sr, WORD color, size_t waitingSpeed, vector<function<void()>> f, bool horizontal)
{	
	for (int i = 0; i < c1.size(); i++)
	{
		
		SMALL_RECT srGet;
		AlertStruct alert;

		srGet.Top = sr.Top + (!horizontal ? i * (alertHeightC + 1) : 0);
		srGet.Left = sr.Left + (horizontal ? i * (alertWidthC + 1) : 0);
		srGet.Bottom = alertHeightC;
		srGet.Right = alertWidthC;

		//AlertManager::CreateAndShowComboAlert(c1[i], c2[i], srGet, color, waitingSpeed, f[i]);
		
		
		alert.characterData = ScreenManager::GetCharsAtRect(srGet);
		alert.position = srGet;
		alert.alert = new Alert(c1[i], c2[i], srGet, color, waitingSpeed);
		
		size_t alertID = Reader::InsertCombo(c1[i], c2[i], f[i], true);

		AlertManager::currentAlerts.insert(make_pair(alertID, alert));

		//Reader::InsertCombo(c1[i], c2[i], bind(&AlertManager::StopAlert, this, alertID, false), true);
		
		
		for (int j = 0; j < c1.size(); j++)
		{
			Reader::InsertCombo(c1[j], c2[j], bind(&AlertManager::StopAlert, this, alertID, i != j, false), true);
		}
	}
}

void AlertManager::CreateAndShowAlerts(const vector<Key *> keys, SMALL_RECT sr, WORD color, size_t waitingSpeed, vector<function<void()>> f, bool horizontal)
{
	for (int i = 0; i < keys.size(); i++)
	{
		
		SMALL_RECT srGet;
		AlertStruct alert;

		srGet.Top = sr.Top + (!horizontal ? i * (alertHeightC + 1) : 0);
		srGet.Left = sr.Left + (horizontal ? i * (alertWidthC + 1) : 0);
		srGet.Bottom = alertHeightC;
		srGet.Right = alertWidthC;

		//AlertManager::CreateAndShowComboAlert(c1[i], c2[i], srGet, color, waitingSpeed, f[i]);
		
		
		alert.characterData = ScreenManager::GetCharsAtRect(srGet);
		alert.position = srGet;

		alert.alert = (keys[i]->getCombo() ? new Alert(keys[i]->getPrekey(), keys[i]->getKey(), srGet, color, waitingSpeed) : new Alert(keys[i]->getKey(), srGet, color, waitingSpeed));
		//alert.alert = new Alert(c1[i], c2[i], srGet, color, waitingSpeed);
		
		size_t alertID = keys[i]->getCombo() ? Reader::InsertCombo(keys[i]->getPrekey(), keys[i]->getKey(), f[i], true) : Reader::InsertPair(keys[i]->getKey(), f[i], true); 

		AlertManager::currentAlerts.insert(make_pair(alertID, alert));

		//Reader::InsertCombo(c1[i], c2[i], bind(&AlertManager::StopAlert, this, alertID, false), true);
		
		
		for (int j = 0; j < keys.size(); j++)
		{
			keys[j]->getCombo() ? 
				(Reader::InsertCombo(keys[j]->getPrekey(), keys[j]->getKey(), bind(&AlertManager::StopAlert, this, alertID, i != j, false), true, i != j)) : 
				(Reader::InsertPair(keys[j]->getKey(), bind(&AlertManager::StopAlert, this, alertID, i != j, keys[i]->getCombo()), true, i != j));
		}

	}
}

void AlertManager::StopAlert(size_t id, bool removePair, bool combo) 
{
	if (AlertManager::isToBeDeleted) return;

	AlertStruct alert = AlertManager::currentAlerts.at(id);
	
	if (removePair) 
	{
		Reader::RemoveKey(alert.alert->GetChar()); //GetChar() kvuli tomu, ze kdyz uz se vola tahle metoda tak se vsechny ty 224-funkce rozbalily
		if (combo) Reader::RemoveKey(alert.alert->GetAltChar());
	}

	AlertManager::currentAlerts.erase(id);

	
	if (AlertManager::IsThereAlert(ScreenManager::GetCharsAtRect(alert.position), alert)) ScreenManager::ReplaceCharsAtRect(alert.characterData, alert.position);

	delete alert.alert;
	alert.alert = NULL;
}

bool AlertManager::IsThereAlert(vector<vector<CHAR_INFO>> vector, AlertStruct alert)
{
	for (size_t i = 0; i < alertHeightC; i++)
	{
		for (size_t j = 0; j < alertWidthC; j++)
		{
			if (vector[i][j].Char.AsciiChar != alert.characterData[i][j].Char.AsciiChar) return false;
		}
	}
	return true;
}