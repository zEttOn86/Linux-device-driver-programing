### ドライバの登録
insmod hoge.ko

### ドライバの一覧表示
lsmod

### ドライバの削除
rmmod hoge

### デバイスファイルの作り方
sudo mknod --mode=666 /dev/devone0 c `grep devone /proc/devices | awk '{print $1;}'` 0

### read関数
sudo hexdump -C -v -n 32 /dev/devone0