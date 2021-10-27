insmod sample.ko
lsmod | grep sample
// major 番号の確認
cat /proc/devices | grep devone
// device fileの作成
// 最初の番号は、major番号に合わせる
mknod /dev/devone c 255 0
or
mknod --mode=666 /dev/devone0 c `grep devone /proc/devices | awk '{print $1;}'` 0
mknod --mode=666 /dev/devone1 c `grep devone /proc/devices | awk '{print $1;}'` 1
mknod --mode=666 /dev/devone2 c `grep devone /proc/devices | awk '{print $1;}'` 2
mknod --mode=666 /dev/devone3 c `grep devone /proc/devices | awk '{print $1;}'` 3

// できたか確認
ls -l /dev/devone


### memo

```
test@test:~/PRACTICE/16_practice_race_cond/src/5-47$ sudo mknod --mode=666 /dev/devone0 c `grep devone /proc/devices | awk '{print $1;}'` 0
test@test:~/PRACTICE/16_practice_race_cond/src/5-47$ sudo mknod --mode=666 /dev/devone0 c `grep devone /proc/devices | awk '{print $1;}'` 0^C
test@test:~/PRACTICE/16_practice_race_cond/src/5-47$ sudo mknod --mode=666 /dev/devone1 c `grep devone /proc/devices | awk '{print $1;}'` 1
test@test:~/PRACTICE/16_practice_race_cond/src/5-47$ sudo mknod --mode=666 /dev/devone2 c `grep devone /proc/devices | awk '{print $1;}'` 2
test@test:~/PRACTICE/16_practice_race_cond/src/5-47$ sudo mknod --mode=666 /dev/devone3 c `grep devone /proc/devices | awk '{print $1;}'` 3
test@test:~/PRACTICE/16_practice_race_cond/src/5-47$ ls -l /dev/devone*
crw-rw-rw- 1 root root 238, 0  8月  6 12:25 /dev/devone0
crw-rw-rw- 1 root root 238, 1  8月  6 12:25 /dev/devone1
crw-rw-rw- 1 root root 238, 2  8月  6 12:25 /dev/devone2
crw-rw-rw- 1 root root 238, 3  8月  6 12:25 /dev/devone3
```