import cv2
import serial
import struct


##  The Position of The Face ##
xbuy=0
ybuy=0

capture= cv2.VideoCapture(1)
## For Arduino Start Serial Connection ##
ser = serial.Serial('/dev/ttyUSB0', 9600)
## Your Cascade File's Path ##
cascade2 = cv2.CascadeClassifier("/home/ufukguler/opencv4/data/haarcascades/haarcascade_frontalface_alt.xml")

while True:
    ret,frame= capture.read()

    gray= cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    
    faces = cascade2.detectMultiScale(gray, 1.3, 4)
    x2=0
    y2=0
    xbuy=0
    ybuy=0
    for (x,y,w,h) in faces:
	## Rectangles Around the Face ##
        cv2.rectangle(frame,(x,y),(x+w,y+h),(255,0,0),2)
        font = cv2.FONT_HERSHEY_SIMPLEX
        cv2.putText(frame,("(%d, "%(x3)),(x,y), font, 1,(255,255,255),1,cv2.LINE_AA)
        cv2.putText(frame,(" %d)"%(y3)),(x+70,y), font, 1,(255,255,255),1,cv2.LINE_AA)
        ## Check the Nearest ##
        if w>xbuy:
            xbuy=w
            x2=x
        if h>ybuy:
            ybuy=h
            y2=y
       
    ## Mapping for Camera's Pixels ##
    x3=abs(0.3984375*((x2)+xbuy/2))
    if x3>255:
        x3=255
    y3=abs(0.53125*((y2)+ybuy/2))
    if y3>255:
        y3=255
    if x3==0:
        x3=127
    if y3==0:
        y3=127
        
    
    x3=int(x3)
    y3=int(y3)

    ## For Serial Connection Converting to Bits ##
    data = ([(struct.pack('>B',x3)),(struct.pack('>B',y3))])
    ser.write(data)
        
              
    cv2.imshow('camera',frame)
    if cv2.waitKey(25) & 0xFF ==ord('q'):
        break

capture.release()
cv2.destroyAllWindows()
