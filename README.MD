# A Way Out Language switcher

Simple that allows you switch between localization without reinstalling the game and even if this localization is unavailable in your region (Polish localization works only with Polish EA/Origin Account)

### Usage

1. Download latest release
2. Run as administrator

### Build

MinGW
```sh
gcc change_locale.c -o change_locale.exe
```

### How it works?

Program just change registry value `Computer\HKEY_LOCAL_MACHINE\SOFTWARE\Hazelight\AWayOut\Locale` to one of the following:

| Language                                     | Code  |
| -------------------------------------------- | ----- |
| English                                      | en_US |
| French                                       | fr_FR |
| Italian                                      | it_IT |
| German                                       | de_DE |
| Spanish - Spain                              | es_ES |
| Portuguese - Brazil                          | pt_BR |
| Russian                                      | ru_RU |
| Polish (WORKS ONLY WITH POLISH EA ACCOUNT!!) | pl_PL |

To change registry you can 

Just press `Win + R` and type `regedit` OR type `regedit` in Windows Search (Start Menu search), go to `Computer\HKEY_LOCAL_MACHINE\SOFTWARE\Hazelight\AWayOut`, double click to `Locale` and change it to one of the table value.
