::==========================================
::contoh perintah file splitter (fsplit.exe)
::==========================================

fsplit bp=148576 msdos.vhd msdosvh
::angka setelah "bp" adalah ukuran file dalam satuan byte(s)
::echo "total 99 file(s)"

fsplit cs msdosvhd.cs msdos2.vhd
::echo "file (msdosvhd.part1) done"
::echo "file (msdosvhd.part2) done"
::echo "file (msdosvhd.part3) done"
::echo "..."
::echo "file (msdosvhd.part99) done"