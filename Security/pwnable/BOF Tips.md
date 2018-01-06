# Buffer Overflow Tips

## libc DB 가 필요할 때

http://libcdb.com/

이 사이트에서 libc 데이터를 찾을 수 있다.

또는,

https://github.com/niklasb/libc-database

이 레포지토리를 사용해도 된다.

## mprotect 함수

NX Bit 가 걸려있을 때 `mprotect` 함수를 사용하면 메모리 페이지의 실행 권한을 바꿀 수 있다.

함수의 프로토타입은 다음과 같다.

`int mprotect(void *addr, size_t len, int prot);`

[출처](http://man7.org/linux/man-pages/man2/mprotect.2.html)

`void * addr` 에는 메모리 주소를 넣으면 된다.

`size_t len` 권한을 변경할 메모리의 크기다. `[addr, addr + len - 1]` 까지의 영역이 변경된다.

`int prot` 는 다음의 리눅스에서의 `rwx` 계산식을 사용하여 넣으면 된다. (ex 7 : `rwx`, 5 : `r-x`)

단, 제약 사항이 있다면, C 언어에서 `sys/mman.h` 헤더파일을 포함해서 작성하면 상관이 없지만, 시스템 콜로 직접 호출할 때에는 `addr` 의 들어가는 주소값이 `0x1000(4096)` 으로 나누어져야 한다.