# Food Serving Robot

## Table of Contents

- [About](#about)
- [Flowchart](#flowchart)
- [Usage](#usage)



## About <a name = "about"></a>
Berikut ini adalah diagram rangkaian robot:

<img width="50%" src="./media/diagram_rangkaian.jpg">


Robot ini dibuat berdasarkan beberapa ketentuan:
- Denah seperti yang ditentukan programmer
- Meja dapat ditambahkan sepanjang jalur yang diberi tanda hijau
- Robot selalu melewati meja 1

<img width="70%" src="./media/denah_jalur_anotated.jpg">

Berikut ini adalah dasar anggota gerak robot:

<img width="40%" src="./media/anggota_gerak_dasar.jpg">



## Flowchart <a name = "flowchart"></a>

<img src="./media/flowchart1.png">

<img src="./media/flowchart2.png">



## Usage <a name = "usage"></a>
Terdapat 3 input tombol, yaitu:
- nomor meja (kiri user)
- reset nomor meja (tengah)
- submit (kanan)
Asumsi user berhadapan dengan robot. User hanya perlu mengikuti apa yang ditampilkan pada layar LCD.

Tahapan:
1. Robot dalam kondisi standby
2. Sensor HCSR04 mendeteksi orang yang mendekat
3. Koki memberi input meja tujuan, lalu klik submit
4. Robot menuju meja tujuan
5. Pelanggan mengambil makanan, lalu klik submit
6. Robot menuju ke base
7. Robot dalam mode stanby
