# cryptus [in progress]
A simple encoder in C

Cryptus is a simple encoder written in C. It has several tools for working with texts.

Available tools:

**URL/URI**: Url(%XX); Hex(%XX); Unicode(%uUUUU)

**HTML-ENTITY**: Named(&lt); Decimal(&#DD); Hex(&#xXX); Hex long(&#x00XX)

**SPECIAL ENCODING**: JavaScript escaped; XML escaped

**Straight Encoding**: Decimal(DD); Hex(XX)

**IE Specific**: (\\xXX); (\\x0XX); (\\x00XX); (\\x000XX); (\\x0000XX); (\\x00000XX); (\\uUUUU)

**IP Specific**: Hex Address (IPv4); (Octal (IPv4); Dword Address (IPv4)

**Hash**: Base64; MD5; SHA-256; RIPEMD160

**Others**: Split (delimiter); Split (Space); Reverse string; Join; International Morse; 13375p34k - Simple; 
13375p34k - Advanced; Binary; BCD (int); Replace; Up Case; Low Case; String length

**Special**
Password generator

# How to build on Linux

1. install dependencies: pkg-config gtk+-2.0 gdk-pixbuf-2.0 openssl

2. compile: make
