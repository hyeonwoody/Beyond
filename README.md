# Beyond
A CLI-based program to enhance video editing convenience.

</br>

## 🧑‍💻: Intro
❓ Problem : Needs to cut in time for editing video 😮

‼ Idea : Organizing video footages in right order and right place consumes a lot of time 🤔

💯 Solution : AUTOMATION 😁

 I develop it for my own good.  
 
</br>

 ## ✅: Implementation 
- **파일 복사** : 원본 복사뿐만 아니라 심볼릭링크 생성을 통해 하드 드라이브 절약.

- **영상 자르기** : 플레이어의 책갈피 파일을 활용한 특정 구간 자르기.  

- **전략 패턴** : 런타임에 작업 처리 방법을 변경할 수 있도록 CJob 클래스에 proceed() 메서드 추가.

- **명령 패턴** : 코드의 가독성을 높이기 위해 CJob 클래스에서 작업을 처리하는 메서드 캡슐화.

- **팩토리 메서드 패턴** :  optionList와 flagList에 대한 객체 생성을 위해 CreateOption()과 CreateFlag() 메서드 사용.  

  Options :  
    -w Set current path.  
    -c Set destination path.  
    -f File name alignment.  
    -~~s Select the file (Not Implemented).~~ 
  
  Flag :  
    -cp Copy the file to destination path(-c).  
    -sb Sync the subtitle file name with the video file name.  
    -sy Create Symbolic link to destination path(-c).  
    -ca Cut the video on certain duration.  
    
   
    
 </br>

## 📞: Contact
- Email: hyeonwoody@gmail.com
- Blog: https://velog.io/@hyeonwoody
- Github: https://github.com/hyeonwoody

</br>

## 🧱: Technologies Used
>C++

## 📖: Libraries Used
>FFmpeg 4.2 (AVStream, AVPacket)  
>MariaDB
