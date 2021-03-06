# Debug tips

_just for part2_

## Prepare

* install gdb and tmux in docker container
* divide start.sh into two parts

```shell
#!/usr/bin/env bash
# start-1.sh

ulimit -c unlimited

YFSDIR1=$PWD/yfs1

rm -rf $YFSDIR1
mkdir $YFSDIR1 || exit 1
sleep 1
```

```shell
#!/usr/bin/env bash
# start-2.sh

# make sure FUSE is mounted where we expect
pwd=`pwd -P`
if [ `mount | grep "$pwd/yfs1" | grep -v grep | wc -l` -ne 1 ]; then
    sh stop.sh
    echo "Failed to mount YFS properly at ./yfs1"
    exit -1
fi
```
## Debug

* Start tmux, split the window into two parts

| | |
|:--|:--|
| `./start-1.sh` | `gdb yfs_client` |
| | `run ./yfs_client yfs1   > yfs_client1.log 2>&1 &` |
| `./start-2.sh` | |
| `./<your_test_file>` | |
| | gdb actions ... |

_If your program encountered segment fault, you will find this method 
really pleasant._

-------------------------------------------------

## At last, wish you pass this lab smoothly.

![come_on](https://i.pinimg.com/originals/51/ab/55/51ab557eb0fc9c63a96a88f50efb36a9.jpg)