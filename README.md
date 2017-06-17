
<!-- README.md is generated from README.Rmd. Please edit that file -->
Rtins: Tools for Reading and Parsing Network Packet Capture (PCAP) Files
========================================================================

The **Rtins** package provides tools for analysing network captures on top of [`libtins`](http://libtins.github.io), a high-level, multiplatform C++ network packet decoding and crafting library.

Installation
------------

You need to install the [`libtins`](http://libtins.github.io) library first. And as a minimum requirement, `libtins` needs the development package of `libpcap` (or `WinPcap` for Windows). On Linux,

``` bash
# install libpcap-devel, openssl-devel is also recommended
git clone https://github.com/mfontanini/libtins.git
mkdir libtins/build
cd libtins/build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr
make
sudo make install
```

Please, refer to the `libtins` documentation for the installation in other platforms. Then, `Rtins` can be installed using `devtools`:

``` r
devtools::install_github("Enchufa2/Rtins")
```

Usage
-----

``` r
library(Rtins)

fname <- system.file("pcaps/http.cap", package="Rtins")
pcap <- read_pcap(fname)
head(pcap)
#>       tv_sec tv_usec layer_1_size  layer_1_id       layer_1_src
#> 1 1084443427  311224           62 ETHERNET_II 00:00:01:00:00:00
#> 2 1084443428  222534           62 ETHERNET_II fe:ff:20:00:01:00
#> 3 1084443428  222534           60 ETHERNET_II 00:00:01:00:00:00
#> 4 1084443428  222534          533 ETHERNET_II 00:00:01:00:00:00
#> 5 1084443428  783340           60 ETHERNET_II fe:ff:20:00:01:00
#> 6 1084443428  993643         1434 ETHERNET_II fe:ff:20:00:01:00
#>         layer_1_dst layer_2_size layer_2_id     layer_2_src
#> 1 fe:ff:20:00:01:00           48         IP 145.254.160.237
#> 2 00:00:01:00:00:00           48         IP  65.208.228.223
#> 3 fe:ff:20:00:01:00           40         IP 145.254.160.237
#> 4 fe:ff:20:00:01:00          519         IP 145.254.160.237
#> 5 00:00:01:00:00:00           40         IP  65.208.228.223
#> 6 00:00:01:00:00:00         1420         IP  65.208.228.223
#>       layer_2_dst layer_3_size layer_3_id layer_3_src layer_3_dst
#> 1  65.208.228.223           28        TCP       49374       25728
#> 2 145.254.160.237           28        TCP       20504       49790
#> 3  65.208.228.223           20        TCP           0           0
#> 4  65.208.228.223          499        TCP           0           0
#> 5 145.254.160.237           20        TCP           0           0
#> 6 145.254.160.237         1400        TCP           0           0
#>   payload_size
#> 1            0
#> 2            0
#> 3            0
#> 4          479
#> 5            0
#> 6         1380
summary(pcap)
#> File info
#>   Capture file   : /home/xxx/R/x86_64-redhat-linux-gnu-library/3.3/Rtins/pcaps/http.cap
#>   Filter applied : 
#>   Layers decoded : 3
#>   Length (bytes) : 25803
#> 
#> Time info
#>   First packet   : 2004-05-13 10:17:07
#>   Last packet    : 2004-05-13 10:17:37
#> 
#> Statistics
#>   Packets        : 43
#>   Time span (s)  : 30.3937
#>   Average pps    : 1.414767
#>   Average Mbps   : 0.006635848
head(read_pcap(fname, "udp port 53"))
#>       tv_sec tv_usec layer_1_size  layer_1_id       layer_1_src
#> 1 1084443429  864896           89 ETHERNET_II 00:00:01:00:00:00
#> 2 1084443430  225414          188 ETHERNET_II fe:ff:20:00:01:00
#>         layer_1_dst layer_2_size layer_2_id     layer_2_src
#> 1 fe:ff:20:00:01:00           75         IP 145.254.160.237
#> 2 00:00:01:00:00:00          174         IP   145.253.2.203
#>       layer_2_dst layer_3_size layer_3_id layer_3_src layer_3_dst
#> 1   145.253.2.203           55        UDP        3009          53
#> 2 145.254.160.237          154        UDP          53        3009
#>   payload_size
#> 1           47
#> 2          146
```
