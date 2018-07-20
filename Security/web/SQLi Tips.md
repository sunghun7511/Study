# SQL Injection Tips

## Filtering a?

MySQL 에서는 a랑 그리스 문자 à를 똑같이 인식한다..

필터링을 바이패스할 때 유용할듯..

## md5($value, true) 형식을 사용할 때의 SQLi 벡터

출처는 [여기](http://cvk.posthaven.com/sql-injection-with-raw-md5-hashes)

이 값을 넣으면

> 129581926211651571912466741651878684928

이 값이 나오는데,

> 06da5430449f8f6f23dfc1276f722738

이는 아스키로 다음과 같다.

> ÚT0Dﾟﾏo#ßÁ'or'8

쿼리가 다음과 비슷한 형태를 띌 때 사용할 수 있다.

"~~~ password='".md5($password, true)."'";