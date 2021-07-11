Easy and shitty way to detect HLBot cheat to Metin2


takich metod jak ta jest 1000 w tym syf cheacie xD


ENG:
How to install: copy all files to your Extern (Include / Lib) folder then:


in WinMain add:
```
	auto oNtOpenFile = fNtOpenFile(LI_FN(GetProcAddress)(LI_FN(LoadLibraryA)(XorString("ntdll.dll")), XorString("NtOpenFile")));

#ifdef DEBUG
	std::cout << "NtOpenFile offset: " << oNtOpenFile << "\n";
#endif // DEBUG

	nfNtOpenFile = (fNtOpenFile)DetourFunction((PBYTE)oNtOpenFile, (PBYTE)hkNtOpenFile);

#ifdef DEBUG
	std::cout << "NtOpenFile hooked! \n ";
#endif // DEBUG
```
and above WinMain in Userinterface.cpp add rest of the code :)


PL:

Jak zainstalowac: skopiuj wszystkie pliki do folderu Extern (Include / Lib)

w WinMain dodaj:
```

	auto oNtOpenFile = fNtOpenFile(LI_FN(GetProcAddress)(LI_FN(LoadLibraryA)(XorString("ntdll.dll")), XorString("NtOpenFile")));

#ifdef DEBUG
	std::cout << "NtOpenFile offset: " << oNtOpenFile << "\n";
#endif // DEBUG

	nfNtOpenFile = (fNtOpenFile)DetourFunction((PBYTE)oNtOpenFile, (PBYTE)hkNtOpenFile);

#ifdef DEBUG
	std::cout << "NtOpenFile hooked! \n ";
#endif // DEBUG
```

Nad WinMain Dodaj cala reszte kodu :)
 

//Credits:
xp123 
Unc3nZureD
