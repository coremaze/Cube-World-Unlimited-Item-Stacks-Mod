#include <windows.h>

unsigned int base;
bool __thiscall cube__Creature__CanCarryMoreItems(unsigned int creature_ptr, unsigned int item_ptr){
    return true;
}


void WriteJMP(BYTE* location, BYTE* newFunction){
    DWORD dwOldProtection;
    VirtualProtect(location, 5, PAGE_EXECUTE_READWRITE, &dwOldProtection);
    location[0] = 0xE9; //jmp
    *((DWORD*)(location + 1)) = (DWORD)(( (unsigned INT32)newFunction - (unsigned INT32)location ) - 5);
    VirtualProtect(location, 5, dwOldProtection, &dwOldProtection);
}

extern "C" __declspec(dllexport) bool APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            base = (unsigned int)GetModuleHandle(NULL);

            //Overwrite the original function.
            WriteJMP((BYTE*)(base + 0x3E4A0), (BYTE*)&cube__Creature__CanCarryMoreItems);

            break;

    }
    return true;
}
