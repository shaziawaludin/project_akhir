###################################################################
			Untuk User
###################################################################
> untuk pertama kali membuka aplikasi, silahkan gunakan :
	username : admin
	password : theworldinmyhand
  setelah itu kamu bisa menambahkan akun di bagian user management

> Program memiliki 2 sisi interface. sebagai admin dan sebagai
  kasir. Untuk pertama kali masuk dalam program (berhasil login)
  kamu berada di sisi admin. untuk membuka fitur di sisi kasir,
  silahkan buatlah sebuah account yang akan digunakan oleh kasir
  untuk login. user management yang terdapat pada admin side
  merupakan seluruh crud untuk account kasir, sedangkan account
  milik admin adalah permanen dan tidak dapat diubah atau dihapus.

> setiap program ini terintegrasi ke beberapa file yang ada 
  bersama dengan lokasi penyimpanan aplikasi ini dan akan
  dibuat otomatis oleh program ketika berjalan.

> Untuk pertama kali, kamu harus input manual seluruh informasi
  terkait barang yang kamu perlukan untuk mengadakan transaksi.

> untuk user experience yang lebih baik, silahkan atur lebar
  window aplikasi ini hingga 120 px atau 120character.
  jika tidak, kamu akan menemui beberapa kondisi tidak normal.

> sebagai acuan bahwa lebar window sudah pada ukuran yang tepat,
  terdapat sebuah garis '===========' pada hampir setiap menu
  sebagai alat bantu.

> aku tahu program masih sangat banyak kekurangan.
  silahkan contact shaziawaludin23@gmail.com jika kamu punya masukan.















####################################################################
			Untuk Developer
####################################################################
SEMUA SUDAH SELESAI sampai sini saja dulu.
memang masih banyak kekurangan, tapi aku rasa ini sudah cukup.

searching o
> fungsi caribarang_barcode
> fungsi caribarang_nama

sorting o
> fungsi sortbarcode

file o
> hampir di tiap fungsi ada

array o
> sturct
> fungsi logo

rekursif o
> fungsi penjumlahanpenjualan

pointer - belum ada pointer dalam pointer
tapi sebenernya banyak dari fungsi yang dipakai itu minta pointer
misalnya substr.

Untuk pertama, coba diperhatikan setiap bugnya. kemungkinan masih ada.
Aku belum cek sebegitunya. silahkan ya dicek, nanti laporin aja
kesalahannya di mana. kalau mungkin di-fix, nanti coba aku
selesaikan bugnya.

bug : 
>> ketika input harga mengalami kesalahan input berupa char.
program akan error.

perhatikan juga setiap fungsi yang dipakai, ini memang cukup
membingungkan. Maaf kalau code nya masih berantakan. semoga
selanjutnya bisa lebih baik. 


[hal kecil tapi sulit dibuat]
beberapa hal yang terlihat biasa aja tapi perlu kamu tahu :

program ini memiliki kode invoice dan kode barcode yang digenerate
secara otomatis. caranya adalah dengan mencari data dari
barcode atau no.invoice terakhir dalam file.
oleh karenanya, di setiap perubahan pada file selalu diakhiri dengan 
sorting agar data selalu terjaga urutannya.

pada bagian yang sama juga, kode invoce dan barcode merupakan string.
Sedangkan cara kerja membuat barcode baru atau kode invoice baru adalah
dengan menambahkan barcode atau kode invoice terakhir dengan bilangan 1.

hal tersebut dapat dilakukan dengan cara melempar isi variable, memotongnya,
lalu merubah stream dari data tersebut lalu diproses untuk dilakukan
penambahan.

[hal lucu yang ga lucu]
program input barang akan memerintahkan pengguna untuk
tidak menggunakan spasi. jika pengguna menginputkan spasi, maka proses
input data akan gagal. 

terlihat normal, tapi... sebenarnya pada fungsi yang sama,
dengan parameter yang sama, program seharusnya diproram saja untuk
mengubah spasi menjadi underscore '_', namun developer sedang ngawur
jadi begitu. 
jangan ditiru.

[hal terlama yang dikerjakan]
CRUD data barang. MENYEBALKAN, salah mulu. konyolnya salahnya
sering karena salah menaruh indeks.