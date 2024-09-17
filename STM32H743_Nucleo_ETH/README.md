# wolfSSL/wolfTPM Demo for STM32H743ZI/STM32H753ZI and the ST33KTPM2X

Development Board: https://www.st.com/en/evaluation-tools/nucleo-h753zi.html

Example based on https://github.com/stm32-hotspot/STM32H7-LwIP-Examples/tree/main/STM32H743_Nucleo_ETH

Hardware:
* STM32H753ZI
* USART3 -> STLink USB UART
* Ethernet (DHCP)
* ST33KTPM2X - SPI
* SPI2 for TPM
  - PC2_C   ------> SPI2_MISO
  - PC3_C   ------> SPI2_MOSI
  - PD3     ------> SPI2_SCK
  - PB9     ------> SPI2_NSS

Software:
* FreeRTOS
* LWIP
* wolfSSL
* wolfTPM


## Example Output

```
Starting HTTPS w/TPM Demo
netif: added interface st IP addr 0.0.0.0 netmask 0.0.0.0 gw 0.0.0.0
netif: setting default interface st
TPM2: Caps 0x30000415, Did 0x0003, Vid 0x104a, Rid 0x 1
TPM2_Startup pass
Setting up TLS key/certificate to use TPM based IDevID
TPM2_ReadPublic Handle 0x81020000: pub 120, name 50, qualifiedName 50
TPM Serial Number (7 bytes)
.5a 9a c0 b8 dc 07 17                            | Z......
Handle 0x81020000, Auth 16
.b2 0e fd 61 ac 6c 1b 29 f0 54 9a 5b 38 4e ec 48 | ...a.l.).T.[8N.H
TPM2_NV_ReadPublic: Sz 14, Idx 0x1c90200, nameAlg 11, Attr 0x62042c04, authPol 0, dataSz 815, name 34
TPM2_NV_ReadPublic: Sz 14, Idx 0x1c90200, nameAlg 11, Attr 0x62042c04, authPol 0, dataSz 815, name 34
TPM2_NV_Read: Auth 0x1c90200, Idx 0x1c90200, Offset 0, Size 768
TPM2_NV_Read: Auth 0x1c90200, Idx 0x1c90200, Offset 768, Size 47
NV public read certificate 0x1c90200 (815 bytes)
Waiting for TLS client on port 443

....MENU

.t. wolfCrypt Test
.b. wolfCrypt Benchmark
.i. Get TPM information
Please select one of the above options:
netif: netmask of interface st set to 255.255.255.0
netif: GW address of interface st set to 10.0.4.1
netif_set_ipaddr: netif address being changed
IP: 10.0.4.181

Got client, starting TLS handshake
TPM2_Sign: ECDSA 96
Cipher Suite: TLS_AES_128_GCM_SHA256
Got msg:
    GET / HTTP/1.1
    Host: 10.0.4.181
    Sec-Fetch-Site: none
    Connection: keep-alive
    Sec-Fetch-Mode: navigate
    Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
    User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/17.6 Safari/605.1.15
    Accept-Language: en-US,en;q=0.9
    Sec-Fetch-Dest: document
    Accept-Encoding: gzip, deflate, br

Got client, starting TLS handshake
TPM2_Sign: ECDSA 96
Cipher Suite: TLS_AES_128_GCM_SHA256
Got msg:
    GET /STM32H7xx_files/ST.gif HTTP/1.1
    Host: 10.0.4.181
    Sec-Fetch-Site: same-origin
    Accept-Encoding: gzip, deflate, br
    Connection: keep-alive
    Sec-Fetch-Mode: no-cors
    Accept: image/webp,image/avif,image/jxl,image/heic,image/heic-sequence,video/*;q=0.8,image/png,image/svg+xml,image/*;q=0.8,*/*;q=0.5
    User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/17.6 Safari/605.1.15
    Referer: https://10.0.4.181/
    Sec-Fetch-Dest: image
    Accept-Language: en-US,en;q=0.9

Got client, starting TLS handshake
TPM2_Sign: ECDSA 96
Cipher Suite: TLS_AES_128_GCM_SHA256
Got msg:
    GET /STM32H7xx_files/stm32.jpg HTTP/1.1
    Host: 10.0.4.181
    Sec-Fetch-Site: same-origin
    Accept-Encoding: gzip, deflate, br
    Connection: keep-alive
    Sec-Fetch-Mode: no-cors
    Accept: image/webp,image/avif,image/jxl,image/heic,image/heic-sequence,video/*;q=0.8,image/png,image/svg+xml,image/*;q=0.8,*/*;q=0.5
    User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/17.6 Safari/605.1.15
    Referer: https://10.0.4.181/
    Sec-Fetch-Dest: image
    Accept-Language: en-US,en;q=0.9

Got client, starting TLS handshake
TPM2_Sign: ECDSA 96
Cipher Suite: TLS_AES_128_GCM_SHA256
Got msg:
    GET /inchtml-pages-stm32_connectivity_files/pixel.gif HTTP/1.1
    Host: 10.0.4.181
    Sec-Fetch-Site: same-origin
    Accept-Encoding: gzip, deflate, br
    Connection: keep-alive
    Sec-Fetch-Mode: no-cors
    Accept: image/webp,image/avif,image/jxl,image/heic,image/heic-sequence,video/*;q=0.8,image/png,image/svg+xml,image/*;q=0.8,*/*;q=0.5
    User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/17.6 Safari/605.1.15
    Referer: https://10.0.4.181/
    Sec-Fetch-Dest: image
    Accept-Language: en-US,en;q=0.9
```

## HTTPS Webpage:

Use the IP address shown to access the HTTPS server:

https://10.0.4.181
