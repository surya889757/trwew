import time
#import digitalio
#import board
import RPi.GPIO as GPIO
import Adafruit_DHT
import time
#import sys
#import numpy as np 
import cv2 
import smtplib
import os.path
from email.mime.text import MIMEText#email.mime.text.MIMEText(_text[, _subtype[, _charset]])
from email.mime.multipart import MIMEMultipart
from email.mime.base import MIMEBase#email.mime.base.MIMEBase(_maintype(e.g. text or image), _subtype(e.g. plain or gif), **_params(e.g.key/value dictionary))
from email import encoders
from Adafruit_IO import Client, Feed, RequestError
# This will return video from the first webcam on your computer. 
##cap = cv2.VideoCapture(0)   
##i=0 
### Define the codec and create VideoWriter object 
##fourcc = cv2.VideoWriter_fourcc(*'XVID') 
##out = cv2.VideoWriter('output.avi', fourcc, 20.0, (640, 480)) 
from mcp3208 import MCP3208
adc = MCP3208()
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM) 
DHT_PIN = 26
Motor1A = 21
Motor1B = 20
#irsensor=5
servo_pin=6
moisture = 16
temp_flag=0
DHT_SENSOR = Adafruit_DHT.DHT11
#GPIO.setup(irsensor,GPIO.IN)
GPIO.setup(servo_pin, GPIO.OUT)
GPIO.setup(Motor1A,GPIO.OUT)  # All pins as Outputs
GPIO.setup(Motor1B,GPIO.OUT)
GPIO.setup(moisture, GPIO.IN)
p = GPIO.PWM(servo_pin, 50)
i=0


key = cv2. waitKey(1)
webcam = cv2.VideoCapture(0)
frame_width = int(webcam.get(3)) 
frame_height = int(webcam.get(4))
size = (frame_width, frame_height) 
result = cv2.VideoWriter('filename.avi',  
                         cv2.VideoWriter_fourcc(*'MJPG'), 
                         10, size) 
email = 'gmahi7013@gmail.com'
password = '7013521093'
send_to_email = 'gorantlagarimaheswari7013@gmail.com'
subject = 'This is the subject'
message = 'This is my message from home'
file_location = '///home/pi/Desktop/LED_BLINK_ADAFRUIT//filename.avi'
msg = MIMEMultipart()#Create the container (outer) email message.
msg['From'] = email
msg['To'] = send_to_email
msg['Subject'] = subject
'''as.string()  
 |
 +------------MIMEMultipart  
              |                                                |---content-type  
              |                                   +---header---+---content disposition  
              +----.attach()-----+----MIMEBase----|  
                                 |                +---payload (to be encoded in Base64)
                                 +----MIMEText'''
msg.attach(MIMEText(message, 'plain'))#attach new  message by using the Message.attach



#p.start(7.5)
ADAFRUIT_IO_KEY = 'aio_vIGH46ksRHtjeW9g5OCZNa3AHgrI' # Set your APIO Key
 # Set to your Adafruit IO username.
ADAFRUIT_IO_USERNAME = 'Mahi_7013'
aio = Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)
try: 
    digital = aio.feeds('led')
except RequestError: 
    feed = Feed(name="led")
    LED = aio.create_feed(feed)
# led set up
#led = digitalio.DigitalInOut(board.D6)
#led.direction = digitalio.Direction.OUTPUT
while True:
    humidity, temperature = Adafruit_DHT.read(DHT_SENSOR, DHT_PIN)
    obstacle = adc.read(1)
    data = aio.receive(digital.key)
    water=GPIO.input(moisture)
    print("sound value");
    print(obstacle)
    print("moisture value")
    print(water)
    if humidity is not None and temperature is not None:
      print("Temp={0:0.1f}C Humidity={1:0.1f}%".format(temperature, humidity))
      if ((temperature>=30) or (water==0)):
            print("temp")
            temp_flag=1
            GPIO.output(Motor1A,GPIO.HIGH)
            GPIO.output(Motor1B,GPIO.LOW)
    else:
            GPIO.output(Motor1A,GPIO.LOW)
            GPIO.output(Motor1B,GPIO.LOW)
   
        
    if(obstacle==0):
        print('SOUND<- ON\n')
        if int(data.value) == 1:
            print('received <- ON\n')
            p.start(7.5)
            p.ChangeDutyCycle(7.5) # turn towards 90 degree
            #time.sleep(1) # sleep 1 second
            p.ChangeDutyCycle(2.5) # turn towards 0 degree
            #time.sleep(1) # sleep 1 second
       # p.ChangeDutyCycle(12.5) # turn towards 180 degree
            print("servo rotate")
            #time.sleep(1) # sleep 1 second
    elif (obstacle >0):
        print('SOUND<- OFF\n')
    if int(data.value) == 0:
             print('received <- OFF\n')
             p.stop()
             print("servo off")
             #p.ChangeDutyCycle(2.5) # turn towards 0 degree
             #time.sleep(1) # sleep 1 second
    #break
    if ((temp_flag==1) | (obstacle==0)|(water==0)):
                 print("with in cemara")
                 check, frame = webcam.read()
                 print(check) #prints true as long as the webcam is running
                 print(frame) #prints matrix values of each framecd
                 #result.write(frame)
                 cv2.imshow("Capturing", frame)
                 for i in range(0, 25):
                     print('frame #:', i)

                     check, frame = webcam.read()
                     #frame = cv2.QueryFrame(capture)
                     #cv2.ShowImage("w1", frame)

                     result.write(frame)

                     cv2.imshow("Capturing", frame)

                 if (i==25):
                     webcam.release()
                     webcam.release()
                     break
                 print ('released capture')
                 
                 filename = os.path.basename(file_location)#function returns the tail of the path
                 attachment = open(file_location, "rb") #“rb” (read binary)
                 part = MIMEBase('application', 'octet-stream')#Content-Type: application/octet-stream , image/png, application/pdf
                 part.set_payload((attachment).read())
                 encoders.encode_base64(part)
                 part.add_header('Content-Disposition', "attachment; filename= %s" % filename)#Content-Disposition: attachment; filename="takeoff.png"
                 msg.attach(part)
                 server = smtplib.SMTP('smtp.gmail.com', 587)# Send the message via local SMTP server.
                 print("with in msg")
                 server.starttls()# sendmail function takes 3 arguments: sender's address, recipient's address and message to send 
                 server.login(email, password)
                 text = msg.as_string()
                 server.sendmail(email, send_to_email, text)
                 print("mail sended")
                 server.quit()
                 
    #break 
                     
                 
     
##    print("with in camera")                 
##    ret, frame = cap.read()  
##  
##    # Converts to HSV color space, OCV reads colors as BGR 
##    # frame is converted to hsv 
##    #hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV) 
##      
##    # output the frame 
##    #out.write(hsv)  
##      
##    # The original input frame is shown in the window  
##    cv2.imshow('Original', frame) 
##  
##    # The window showing the operated video stream  
##    #cv2.imshow('frame', hsv) 
##  
##      
##    # Wait for 'a' key to stop the program  
##    if cv2.waitKey(1) & 0xFF == ord('a'): 
##        break
  
### Close the window / Release webcam 
##    cap.release() 
##      
##    # After we release our webcam, we also release the output 
##    out.release()  
##      
##    # De-allocate any associated memory usage  
##    cv2.destroyAllWindows() 
GPIO.cleanup()
