copy "D:\Source Code\Data Struct\Design\B����������������\Release\B����������������.exe" produce_data.exe
copy Release\B_Tree.exe B_Tree.exe
produce_data.exe
B_Tree.exe input.txt out.txt
python compare.py
pause
