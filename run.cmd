REM copy Release\B_Tree.exe .
produce_data.exe
B_Tree.exe input.txt out.txt
python compare.py
pause