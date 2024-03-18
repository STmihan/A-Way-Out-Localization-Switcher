#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

typedef struct
{
    char *locale_name;
    char *code;
} Locale;

Locale locales[] = {
    {.code = "en_US", .locale_name = "English"},
    {.code = "fr_FR", .locale_name = "French"},
    {.code = "it_IT", .locale_name = "Italian"},
    {.code = "de_DE", .locale_name = "German"},
    {.code = "es_ES", .locale_name = "Spanish - Spain"},
    {.code = "pt_BR", .locale_name = "Portuguese - Brazil"},
    {.code = "ru_RU", .locale_name = "Russian"},
    {.code = "pl_PL", .locale_name = "Polish (WORKS ONLY WITH POLISH EA ACCOUNT!!)"}, // Doesn't work for some reason
};

#define LOCALES_COUNT (sizeof(locales) / sizeof(locales[0]))

#define HKEY_PATH "SOFTWARE\\Hazelight\\AWayOut"
#define HKEY_NAME "Locale"
#define HKEY_FULL_PATH "SOFTWARE\\Hazelight\\AWayOut\\Locale"

void show_help(void)
{
    printf("%s", "This is a program to change localization of A Way Out game, even if it's unavailable in your region.\n");
    printf("%s", "Choose language:\n");
    for (size_t i = 0; i < LOCALES_COUNT; i++)
    {
        printf("%zu) %s (%s)\n", i + 1, locales[i].locale_name, locales[i].code);
    }
}

int choose_locale(Locale *out)
{
    int input;
    printf("Input: ");
    if (scanf("%d", &input) == 0 || input > LOCALES_COUNT || input <= 0)
    {
        return FALSE;
    }

    *out = locales[input - 1];
    return TRUE;
}

int get_current_locale(Locale *out)
{
    char buffer[256];
    DWORD data_size = sizeof(buffer);
    int result = RegGetValueA(HKEY_LOCAL_MACHINE, HKEY_PATH, HKEY_NAME, RRF_RT_REG_SZ, NULL, buffer, &data_size);
    if (result == ERROR_SUCCESS)
    {
        for (size_t i = 0; i < LOCALES_COUNT; i++)
        {
            if (strcmp(locales[i].code, buffer) == 0)
            {
                *out = locales[i];
                return TRUE;
            }
        }
    }

    return FALSE;
}

int set_code(const char *code)
{
    HKEY hkey;
    int result = RegOpenKeyEx(
        HKEY_LOCAL_MACHINE,
        HKEY_PATH,
        0,
        KEY_ALL_ACCESS,
        &hkey);

    if (result == ERROR_SUCCESS)
    {
        size_t data_len = sizeof(code) + 1;
        result = RegSetValueEx(
            hkey,
            HKEY_NAME,
            0,
            REG_SZ,
            (LPBYTE)code,
            data_len);
        if (result == ERROR_SUCCESS)
        {
            return TRUE;
        }
    }

    return FALSE;
}

int main(void)
{
    show_help();

    Locale current;
    if (!get_current_locale(&current))
    {
        printf("ERROR: Error, while getting current locale. Try run and close the game.\n");
        system("pause");
        return -1;
    }
    printf("Current localization: %s (%s)\n", current.locale_name, current.code);

    Locale chosen;
    if (!choose_locale(&chosen))
    {
        printf("ERROR: Input error. Make sure you choose correct language!\n");
        exit(-1);
    }
    printf("You choose %s (%s)\n", chosen.locale_name, chosen.code);

    if (!set_code(chosen.code))
    {
        printf("ERROR: Error, while getting current locale. Try run as administrator or run and close the game.\n");
        system("pause");
        return -1;
    }
    printf("Done!\n");

    system("pause");
    return 0;
}
