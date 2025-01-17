
/* CREER PAR SITHIS / TATANOUU */

#include "stdafx.h"
#include "main.h"

using namespace std;

int Split(vector<string>& vecteur, string chaine, char separateur)
{
	vecteur.clear();

	string::size_type stTemp = chaine.find(separateur);

	while (stTemp != string::npos)
	{
		if (chaine.substr(0, stTemp).length() != 0)
			vecteur.push_back(chaine.substr(0, stTemp));
		chaine = chaine.substr(stTemp + 1);
		stTemp = chaine.find(separateur);
	}

	vecteur.push_back(chaine);

	return vecteur.size();
}

BOOL IsUserAdmin(VOID)
{
	BOOL b;
	SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
	PSID AdministratorsGroup;
	b = AllocateAndInitializeSid(
		&NtAuthority,
		2,
		SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS,
		0, 0, 0, 0, 0, 0,
		&AdministratorsGroup);
	if (b)
	{
		if (!CheckTokenMembership(NULL, AdministratorsGroup, &b))
		{
			b = FALSE;
		}
		FreeSid(AdministratorsGroup);
	}

	return(b);
}

bool launchNostale()
{
	printf("Lancement de nostale.");
	string cmd("Nostale.exe");
	system(cmd.c_str());
}

int findEntwellClient()
{
	if (system("\"C:/handle.exe -a EntwellNostaleClient > .data.txt\"") != 0)
	{
		printf("Mauvais chemin d'acces de handle.");
		system("pause");
		return (-1);
	}
}

int GetPidAndHandle()
{

	ifstream infile(".data.txt");
	if (infile)
	{
		string line;
		string lineSave;
		vector<string> VecStr;

		while (getline(infile, line))
			lineSave = line;
		int nbTabl = Split(VecStr, lineSave, ' ');
		bool findPid = false;
		bool findHandle = false;
		string pid = "";
		string handle = "";
		for (int i = 0; i < nbTabl; ++i)
		{
			if (findPid == true)
			{
				pid = VecStr[i];
				findPid = false;
			}
			if (findHandle == true)
			{
				string::size_type stTemp = VecStr[i].find(":");
				handle = VecStr[i].substr(0, stTemp);
				findHandle = false;
			}

			if (VecStr[i] == "pid:")
				findPid = true;
			if (VecStr[i] == "Mutant")
				findHandle = true;
		}
		if (pid == "" || handle == "")
		{
			printf("Handle already closed.\n");
			return (-1);
		}
		else
			printf("Processus trouve !");
		string buildCmd("C:/handle.exe -p " + pid + " -c " + handle + " -y");
		if (system(buildCmd.c_str()) != 0)
			printf("Erreur lors de la suppression du handle");
		else
			printf("");
		infile.close();
		return (0);
	}
	else
		cout << "Je n arrive pas a trouver mon fichier appel lord tatane." << endl;;
	system("pause");

	return 0;
}

int main(int argc, WCHAR **argv)
{
	if (IsUserAdmin() == false)
	{
		printf("Execute le programme en tant qu'administrateur.\n");
		system("pause");
		return (-1);
	}
	else
	{
		cout << "En train de chercher..." << endl;
		if (findEntwellClient() != -1)
		{
			GetPidAndHandle();
			launchNostale();
		}
	}
	return (0);
}
	