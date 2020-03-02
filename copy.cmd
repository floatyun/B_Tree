copy "D:\Source Code\Data Struct\Design\B树测试数据生成器\Release\B树测试数据生成器.exe" produce_data.exe
copy Release\B_Tree.exe B_Tree.exe
produce_data.exe
B_Tree.exe input.txt out.txt
python compare.py
pause
