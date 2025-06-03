@echo off
cd /d "%~dp0"
setlocal

REM === Nome del tuo eseguibile ===
set EXE=Little_game.exe

REM === Percorso completo dell'eseguibile ===
set FULL="%~dp0%EXE%"

REM === Verifica che l'eseguibile esista ===
if not exist %FULL% (
    echo Errore: %EXE% non trovato nella cartella corrente.
    pause
    exit /b 1
)

REM === Percorso tipico di Windows Terminal ===
set WT=%LocalAppData%\Microsoft\WindowsApps\wt.exe

REM === Se Windows Terminal esiste, usalo ===
if exist "%WT%" (
    echo Avvio in Windows Terminal...
    start "" "%WT%" cmd /c %FULL%
) else (
    echo Avvio con prompt classico...
    start "" cmd /c %FULL%
)

endlocal