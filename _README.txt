FOOD SERVING ROBOT
@programmer mahaamesha

Rule:
- Robot standby di dapur
- Koki meletakkan makanan ke rak pada robot
- Input keypad (nomor meja)
	Urutan nomor meja disimpan di array
	Input ditampilkan di LCD
	Ada tombol nomor, reset, submit
	Setelah SUBMIT, robot mulai jalan
- Robot menuju ke nomor meja
	Cara agar robot hanya menuju ke nomor meja tertentu saja?
- Setelah robot berhenti di meja X, 
	LED pada rak makan tertentu nyala
 	LCD memberi tahu nama menu makanan untuk meja X
- Setelah makanan diambil,
	Notifikasi LCD muncul
	Klik button lanjut
	Ubah array yang menunjukkan tujuan robot
- Setelah selesai mengantarkan semua,
	Artinya, reset struct
	Segera kembali ke posisi standby di dapur
	

Alur Customer:
- Masuk resto
- Menuju ke bagian pemesanan
- Tunggu robot datang ke meja nomor X
- Keluar resto

