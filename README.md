# AutoCAD-Script-Generator

Simple command line tool for Windows writen in C++ that gets all dwg files in current folder and creates a script in AutoCAD format for each file.

Script line is in format:
_.open "ABSOLUTE FILE PATH" AUTOCAD_MACRO_NAME _.qsave _.close

AUTOCAD_MACRO_NAME is inserted as argument in command line.

Script is saved to current folder in format "Script001.scr" and if script already exists number is incremented until no file with that name exists.
