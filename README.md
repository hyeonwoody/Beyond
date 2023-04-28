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
- **File copying**: Saving hard drive space by creating symbolic links in addition to copying the original file.  
- **Video cutting**: Cutting specific sections using the bookmark file of the player.  
- **Strategy pattern**: Adding a proceed() method to the CJob class to change the processing method at runtime.  
- **Command pattern**: Encapsulating the processing method in the CJob class to improve code readability.  
- **Factory method pattern**: Using the CreateOption() and CreateFlag() methods to create objects for optionList and flagList.  


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
