# Git 자주 사용하는 명령어 정리

> 자주 사용하는 기본적인 명령어들을 정리했습니다.

## License

This project's license is WTFPL

## 저장소 생성(초기화) 하기

```
bash git init
```

## 커밋할 파일 추가

```
bash git add README.md
```

## 현재 스테이지 상태를 확인

```
git status
```

## 인라인 커밋 메시지 작성

```
git commit -m "init: README.md"
```

## 커밋 로그 확인

```
git log --decorate=full --oneline --graph
```


## 브랜치 생성하기

```
bash git checkout -b readme
```

> readme 라는 이름의 브랜치를 생성한 후, 생성된 브랜치로 체크아웃

## 참고하면 좋은 사이트들

```
https://guides.github.com/features/mastering-markdown/
http://www.haruair.com/blog/2738
```