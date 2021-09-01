How To install

1. Replace resources/js/core.js file with the core.js file in this Repo
2. Open the new core.js File 
3. Now replace IP Addresse in every single "request.open"  
   "request.open("GET","http://192.168.1.224/TWO");" >  "request.open("GET","http://<YOUR IP ADDRESS>/TWO");"
   IP ADDRESS: your LED Controller IP ADDRESS
4. Go to the Photobooth Admin Panel and Change "Collage-countdown timer:" to 2 Sec.

Note:
- LED Controller needs to be in the same WIFI as the photobooth. 
- Depends on the amount of LED, you need to rewrite the countdown funtions. 

have fun
